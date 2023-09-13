

# WiFi Connection and Server Initialization

This code is designed to connect your device to a WiFi network and initialize a server. It includes functions for scanning available WiFi networks, connecting to a WiFi network, and initializing a server.

## Functions

- `scanWifi()`: This function scans for available WiFi networks and prints the SSID and RSSI for each network found.
- `initwifi()`: This function initializes the WiFi connection. It prompts the user to enter the SSID and password of the network they wish to connect to. After attempting to connect, it prints whether the connection was successful and the device's IP address.
- `serverinti()`: This function initializes a server on port 80 and sets up an Access Point with the provided SSID and password.

## Usage

Upload this code to your device using an appropriate IDE. Open the serial monitor to interact with the program. When prompted, enter the SSID and password of your WiFi network.

Please note that this code is designed for devices that support the WiFi library, such as ESP32 or ESP8266.

## Dependencies

This code requires the "WiFi.h" library.

## Disclaimer

Please ensure you have permission to connect to the WiFi network you are attempting to connect to. Misuse of this code may violate laws or regulations in your jurisdiction.

Remember, this is just a basic README file. Depending on your project's complexity and requirements, you might want to add more sections like 'Installation', 'Contributing', etc.
## Note
- There is a problem in the NAT function of ESP32 Which can be solved using ROUTING setting in the default gateway(router)
