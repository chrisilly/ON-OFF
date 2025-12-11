#include <WiFi.h>
// ========== WiFi Credentials ==========
const char* ssid = "ESP32_WebServer_Chris";
const char* password = "12345678";
// ======================================
WiFiServer server(80);
const int ledPin = 2; 

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Start WiFi in Access Point mode
  WiFi.softAP(ssid, password);

  delay(1000); // Maybe adding a delay will make the following prints acutally show up?

  Serial.println("WiFi AP started!");
  Serial.print("Connect to: ");
  Serial.println(ssid);
  Serial.print("Open browser and go to: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
}

void loop() {
  
  WiFiClient client = server.available();
  
  if (!client) return;
  
  // Wait for request
  while (!client.available()) delay(1);
  
  String req = client.readStringUntil('\r');
  
  client.flush();
  
  // Handle ON/OFF requests
  if (req.indexOf("/ON") != -1) {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED turned on.");
  }
  
  if (req.indexOf("/OFF") != -1) {
    digitalWrite(ledPin, LOW);
    Serial.println("LED turned off.");
  }
  
  // Send HTML page
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
  client.println("<html><body style='text-align:center;'>");
  client.println("<h2>ESP32 LED Control</h2>");
  client.println("<a href='/ON'><button style='font-size:20px;padding:10px 30px;'>ON</button></a>");
  client.println("<br><br>");
  client.println("<a href='/OFF'><button style='font-size:20px;padding:10px 30px;'>OFF</button></a>");
  client.println("</body></html>");
  client.println();
}