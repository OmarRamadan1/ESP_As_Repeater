#include "WiFi.h"
char ssid_bu[]="Sedo";
void serverinti();
void accesspoint();
void initwifi();
void scanWifi();
char ssid_buffer[50]="";       // To store user-provided SSID
char password_buffer[50]="";   // To store user-provided password
unsigned long previousMillis = 0;
unsigned long interval = 10000;
WiFiServer server(80); // using Server class to Set web server port number to 80
String header;
String output26State = "off";
String output27State = "off";
const int  output26 = 26; //   o/p variable
const int output27 = 27; //   o/p variable

void setup() {
    Serial.begin(115200);
    scanWifi(); 
    initwifi();
    serverinti();
  
}

void loop() {
 unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
    accesspoint();
    }


//wifi intializtiom function
void initwifi(){
  WiFi.mode(WIFI_AP_STA);
    Serial.println("Enter WiFi SSID:");
  while (!Serial.available()) {
    // Wait for user input
  }
  String ssid = "";
  ssid = Serial.readString();  // Read user input as SSID
  ssid.trim();
  ssid.toCharArray(ssid_buffer, sizeof(ssid_buffer));  // Convert the string to a C-style character array
   ssid[sizeof(ssid) - 1] = '\0';
  //if (WiFi.psk() != ""){
  //}
  
  Serial.println("Enter WiFi Password:");
  while (!Serial.available()) {
    // Wait for user input
  }
   String password = "";
   password = Serial.readString();  // Read user input as SSID
  password.trim();
  password.toCharArray(password_buffer, sizeof(password_buffer));  // Convert the string to a C-style character array
  Serial.println("Connecting to WiFi..."); //null terminator

  /*Serial.print("ssid[] is");
  for (int i=0; i<20; i++){
  Serial.print(ssid_buffer[i]);
  }
  Serial.print("end");

  Serial.print("password[] is ");
  for (int i=0; i<20; i++){
  Serial.print(password_buffer[i]);
  }
  Serial.println("");*/
  WiFi.begin(ssid_buffer, password_buffer);
  delay(10000);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
   delay(1000);
    Serial.println("Connecting...");
 }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

    delay(1000);
}
//wifi scan function

 void scanWifi(){
   int n = WiFi.scanNetworks();
    Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
       }
    }
}
void serverinti()
{
   pinMode(output26,OUTPUT);
  pinMode(output27,OUTPUT);
  digitalWrite(output26,LOW);
  digitalWrite(output27,LOW);

  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid_bu,password_buffer ); // we remover the pass parameter to make the network free
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
}
void accesspoint()
{
  WiFiClient client = server.available(); // waiting for incoming clients
  if (client){
    Serial.println("there is new client");
    String currentLine = "";
    while (client.connected()){
      if(client.available()){
        char c= client.read();     // read bytes form the client
         Serial.write(c);
         header+=c;
         if(c=='\n')
         {
           if (currentLine.length() == 0) {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
           
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            }
            
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}