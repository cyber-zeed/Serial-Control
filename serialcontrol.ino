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

  Serial.println("\nEnter the number corresponding to the desired Wi-Fi network:");

  while (1) {
    if (Serial.available() > 0) {
      int selectedNetwork = Serial.parseInt();
      Serial.print("You selected: ");
      Serial.println(selectedNetwork);

      if (selectedNetwork >= 1 && selectedNetwork <= numNetworks) {
        Serial.print("Connecting to ");
        Serial.println(WiFi.SSID(selectedNetwork - 1));

        // Prompt for Wi-Fi password
        Serial.println("Enter the Wi-Fi password:");
        while (!Serial.available()) {
          delay(100);
        }
        String password = Serial.readStringUntil('\n');
        password.trim();

        WiFi.begin(WiFi.SSID(selectedNetwork - 1).c_str(), password.c_str());

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
          break; // Exit the loop once connected
        }
      } else {
        Serial.println("Invalid selection. Enter the number corresponding to the desired Wi-Fi network:");
      }
    }
  }
}
