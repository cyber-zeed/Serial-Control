Description:

This ESP8266-based project creates a simple web server that allows you to control GPIO pins using buttons on a webpage. The web server displays buttons for each GPIO pin, allowing you to turn them ON or OFF. Additionally, you can control the pins via serial commands.

Step-by-Step Guide:

1. Set up Arduino IDE:
Ensure that you have the Arduino IDE installed on your computer.

3. Install ESP8266 Board Support:
Open Arduino IDE.
Go to "File" -> "Preferences."
In the "Additional Boards Manager URLs" field, add the following URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
Click "OK" to close the Preferences window.
Go to "Tools" -> "Board" -> "Boards Manager."
Search for "esp8266" and install the "esp8266" platform by ESP8266 Community.

4. Install Required Libraries:
Go to "Sketch" -> "Include Library" -> "Manage Libraries..."
Install the "ESP8266WiFi" and "ESP8266WebServer" libraries.

5. Connect ESP8266:
Connect your ESP8266 module to your computer using a USB-to-Serial adapter.

6. Configure Wi-Fi:
Open the provided code in the Arduino IDE.
Replace "your_wifi_ssid" and "your_wifi_password" with your actual Wi-Fi credentials.

7. Upload Code:
Select your ESP8266 board from "Tools" -> "Board" menu.
Choose the appropriate COM port from "Tools" -> "Port" menu.
Click the "Upload" button to upload the code to your ESP8266.

8. Open Serial Monitor:
After uploading, open the Serial Monitor from "Tools" -> "Serial Monitor."
Set the baud rate to 115200.

9. Connect to Wi-Fi:
In the Serial Monitor, you will see the ESP8266 attempting to connect to Wi-Fi.
Once connected, it will display "Connected to Wi-Fi!"

10. Access Webpage:
Open a web browser and enter the IP address shown in the Serial Monitor (e.g., http://192.168.1.100).
The webpage displays buttons for each GPIO pin.

11. Control GPIO Pins:
Click the "ON" or "OFF" buttons next to each GPIO pin on the webpage to control the corresponding pin.
The status of each pin is updated on the webpage in real-time.

12. Control via Serial:
In the Serial Monitor, type commands like "on5" or "off5" and press Enter to control GPIO pin 5.
The status will be updated in the Serial Monitor and on the webpage.

Notes:
GPIO pin 0 is excluded from the webpage as it is a special pin on the ESP8266.
The webpage dynamically updates without refreshing when buttons are pressed.
By following these steps, you should be able to set up and use the ESP8266-based web server with serial command control.
