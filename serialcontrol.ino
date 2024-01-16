#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const int numPins = 11;  // Number of GPIO pins available on ESP8266
int pins[numPins] = {0, 2, 4, 5, 12, 13, 14, 15, 16};  // GPIO pins to control

ESP8266WebServer server(80);

const int EEPROM_SIZE = 512;  // EEPROM size on ESP8266

struct WiFiCredentials {
  char ssid[32];
  char password[64];
};

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectToWiFi();

  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  // Setup web server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void connectToWiFi() {
  Serial.println("\nScanning for available Wi-Fi networks...");

  int numNetworks = WiFi.scanNetworks();
  if (numNetworks == 0) {
    Serial.println("No Wi-Fi networks found. Please check your Wi-Fi configuration.");
    while (1) {
      delay(1000);
    }
  }

  Serial.println("Available Wi-Fi networks:");
  for (int i = 0; i < numNetworks; i++) {
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(WiFi.SSID(i));
  }

  WiFiCredentials lastCredentials[10];

  // Read the last 10 stored Wi-Fi credentials from EEPROM
  for (int i = 0; i < 10; i++) {
    EEPROM.get(i * sizeof(WiFiCredentials), lastCredentials[i]);
  }

  Serial.println("\nSelect a Wi-Fi network:");

  for (int i = 0; i < numNetworks; i++) {
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(WiFi.SSID(i));
  }

  Serial.println("\nEnter the number corresponding to the desired Wi-Fi network:");

  while (1) {
    if (Serial.available() > 0) {
      int selectedNetwork = Serial.parseInt();
      Serial.print("You selected: ");
      Serial.println(selectedNetwork);  // Add this line for debugging

      if (selectedNetwork >= 1 && selectedNetwork <= numNetworks) {
        WiFiCredentials credentials;

        // Check if the selected Wi-Fi network has stored credentials
        if (selectedNetwork <= 10 && selectedNetwork <= numNetworks) {
          credentials = lastCredentials[selectedNetwork - 1];
          Serial.println("Connecting to the known Wi-Fi network...");
        } else {
          Serial.print("Connecting to ");
          Serial.println(WiFi.SSID(selectedNetwork - 1));

          // Prompt for Wi-Fi password
          Serial.println("Enter the Wi-Fi password:");
          while (!Serial.available()) {
            delay(100);
          }
          String password = Serial.readStringUntil('\n');
          password.trim();

          strncpy(credentials.ssid, WiFi.SSID(selectedNetwork - 1).c_str(), sizeof(credentials.ssid));
          strncpy(credentials.password, password.c_str(), sizeof(credentials.password));

          // Overwrite the oldest stored credentials
          EEPROM.put((selectedNetwork % 10) * sizeof(WiFiCredentials), credentials);
          Serial.println("Credentials saved for the next connection.");
        }

        WiFi.begin(credentials.ssid, credentials.password);
        int attempts = 0;
        while (WiFi.status() != WL_CONNECTED) {
          delay(1000);
          Serial.print(".");
          attempts++;
          if (attempts > 30) {  // Allow a maximum of 30 seconds for connection
            Serial.println("\nFailed to connect to Wi-Fi. Please check your credentials.");
            break;
          }
        }

        if (WiFi.status() == WL_CONNECTED) {
          Serial.println("\nConnected to Wi-Fi!");
        }

        break;
      } else {
        Serial.println("Invalid selection. Enter the number corresponding to the desired Wi-Fi network:");
      }
    }
  }
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP8266 Web Server</h1>";
  html += "<p>Click the buttons to control the ports:</p>";
  
  for (int i = 0; i < numPins; i++) {
    html += "<button onclick=\"window.location.href='/on?pin=" + String(pins[i]) + "'\">Port " + String(pins[i]) + " On</button>";
    html += "<button onclick=\"window.location.href='/off?pin=" + String(pins[i]) + "'\">Port " + String(pins[i]) + " Off</button><br>";
  }

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  String pin = server.arg("pin");
  digitalWrite(pin.toInt(), HIGH);
  server.send(200, "text/plain", "Port " + pin + " turned ON");
}

void handleOff() {
  String pin = server.arg("pin");
  digitalWrite(pin.toInt(), LOW);
  server.send(200, "text/plain", "Port " + pin + " turned OFF");
}
