#include <WiFi.h>

const char* ssid = "FelineWatchdog-Hotspot";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi hotspot
  WiFi.begin(ssid, password);

  Serial.println("Connecting to Wi-Fi hotspot...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to Wi-Fi hotspot");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Your main code here
}
