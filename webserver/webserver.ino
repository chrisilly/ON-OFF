#include <WiFi.h>
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it 
#endif
// ========== WiFi Credentials ==========
const char* ssid = "ESP32_WebServer_Chris";
const char* password = "12345678";
// ======================================
WiFiServer server(80);
BluetoothSerial SerialBT;

const int ledPin = 2; 
const char* on = "LED turned ON";
const char* off = "LED turned OFF";

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

  // Start Bluetooth
  SerialBT.begin("ESP32_Chris"); // Bluetooth device name
  delay(200);
  Serial.println("Bluetooth started. You may now pair with another device.");

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
    Serial.println(on);
    SerialBT.println(on);
  }
  
  if (req.indexOf("/OFF") != -1) {
    digitalWrite(ledPin, LOW);
    Serial.println(off);
    SerialBT.println(off);
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