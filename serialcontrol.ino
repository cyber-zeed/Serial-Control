#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "your_wifi_ssid";
const char *password = "your_wifi_password";

const int numPins = 11;  // Number of GPIO pins available on ESP8266
int pins[numPins] = {0, 2, 4, 5, 12, 13, 14, 15, 16};  // GPIO pins to control

ESP8266WebServer server(80);

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

  // Check for serial commands
  checkSerialCommands();

  // Print the status of buttons every second
  printButtonStatus();
}

void connectToWiFi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

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
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP8266 Web Server</h1>";
  html += "<p>Click the buttons to control the ports:</p>";

  for (int i = 0; i < numPins; i++) {
    html += "<button onclick=\"window.location.href='/on?pin=" + String(pins[i]) + "'\">Port " + String(pins[i]) + " On</button>";
    html += "<button onclick=\"window.location.href='/off?pin=" + String(pins[i]) + "'\">Port " + String(pins[i]) + " Off</button>";
    html += "<span id=\"status" + String(pins[i]) + "\">" + (digitalRead(pins[i]) ? " ON" : " OFF") + "</span><br>";
  }

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  String pin = server.arg("pin");
  digitalWrite(pin.toInt(), HIGH);
  updateStatus(pin.toInt(), "ON");
  Serial.println("Port " + pin + " turned ON");
}

void handleOff() {
  String pin = server.arg("pin");
  digitalWrite(pin.toInt(), LOW);
  updateStatus(pin.toInt(), "OFF");
  Serial.println("Port " + pin + " turned OFF");
}

void updateStatus(int pin, const char *status) {
  server.send(200, "text/plain", status);
  server.send(200, "application/javascript",
              "document.getElementById('status" + String(pin) + "').innerHTML = '" + status + "';");
}

void checkSerialCommands() {
  while (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("on")) {
      int pin = command.substring(2).toInt();
      digitalWrite(pin, HIGH);
      updateStatus(pin, "ON");
      Serial.println("Port " + String(pin) + " turned ON");
    } else if (command.startsWith("off")) {
      int pin = command.substring(3).toInt();
      digitalWrite(pin, LOW);
      updateStatus(pin, "OFF");
      Serial.println("Port " + String(pin) + " turned OFF");
    }
  }
}

void printButtonStatus() {
  static unsigned long lastPrintTime = 0;
  if (millis() - lastPrintTime >= 1000) {  // Print every second
    lastPrintTime = millis();
    Serial.println("\nButton Status:");
    for (int i = 0; i < numPins; i++) {
      Serial.print("Port " + String(pins[i]) + ": ");
      Serial.println(digitalRead(pins[i]) ? "ON" : "OFF");
    }
  }
}
