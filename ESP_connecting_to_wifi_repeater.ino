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
const char* ssid_ap = "XXX"
const char* passwd_ap = "A123456a"
int Wifi_SoftAP_Channel      = 11;
IPAddress local_IP(10,0,1,1);
IPAddress gateway(10,0,1,1);
IPAddress subnet(255,255,255,0);
WiFiServer server(80); // using Server class to Set web server port number to 80

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
  delay(5000);
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

  Serial.print("Setting AP (Access Point)…");
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid_ap, passwd_ap, Wifi_SoftAP_Channel);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
}