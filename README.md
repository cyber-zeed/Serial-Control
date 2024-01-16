# Serial-Control
Simple Arduino File to control pins over serial and Wi-Fi

Step 1: Install the Required Libraries
Make sure you have the necessary libraries installed in your Arduino IDE.

ESP8266 Board Support: Install the ESP8266 board support using the Arduino Board Manager. Go to Tools -> Board -> Boards Manager, search for "esp8266," and install the package.

ESP8266 Libraries: Make sure you have the following libraries installed:

ESP8266WiFi: This is included in the ESP8266 board support package.
ESP8266WebServer: This is included in the ESP8266 board support package.
EEPROM: Included in the Arduino IDE by default.
Step 2: Open the Arduino IDE
Open the Arduino IDE on your computer.

Step 3: Create a New Sketch
Create a new sketch by selecting File -> New.

Step 4: Copy and Paste the Code
Copy the entire code provided in the previous messages and paste it into your new Arduino sketch.

Step 5: Configure GPIO Pins
Adjust the pins array in the code to match the GPIO pins you want to control. Ensure that these pins are suitable for your specific ESP8266 board and connected devices.

Default Pins

int pins[numPins] = {0, 2, 4, 5, 12, 13, 14, 15, 16};  // GPIO pins to control


Step 6: Connect ESP8266 to Computer
Connect your ESP8266 board to your computer using a USB cable.

Step 7: Select Board and Port
In the Arduino IDE, go to Tools -> Board and select your ESP8266 board model. Also, select the appropriate port under Tools -> Port.

Step 8: Upload the Code
Click the "Upload" button (right arrow icon) to upload the code to your ESP8266 board. This may take a few moments.

Step 9: Open Serial Monitor
Once the code is uploaded, open the Serial Monitor in the Arduino IDE (Tools -> Serial Monitor). You should see the serial output from your ESP8266.

Step 10: Interact with the Application
Follow the prompts in the Serial Monitor to interact with the application. The ESP8266 will scan for available Wi-Fi networks, and you can input the number corresponding to your desired network. If needed, provide Wi-Fi passwords and observe the connection process.

Step 11: Control GPIO Pins via Web Server
Once connected, open a web browser and enter the IP address of your ESP8266. You should see a webpage with buttons to control the GPIO pins.

Click the buttons to turn the GPIO pins on and off.

Step 12: Test EEPROM Storage
If you connect to new Wi-Fi networks, observe how the ESP8266 stores and reuses Wi-Fi credentials using EEPROM emulation.

Step 13: Troubleshoot (If Needed)
If you encounter any issues, check the Serial Monitor for error messages. Ensure that your Wi-Fi network details and GPIO pin configurations are correct.

Note:
Remember to replace placeholder values in the code (e.g., Wi-Fi SSID and password) with your actual information.
Be cautious when handling GPIO pins to avoid damage to your ESP8266 or connected devices.
This step-by-step tutorial assumes a basic understanding of using the Arduino IDE and programming ESP8266. 


