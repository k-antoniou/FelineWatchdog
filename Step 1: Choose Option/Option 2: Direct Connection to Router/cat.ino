```cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define ssid "YOUR_SSID"            // Replace with your WiFi SSID
#define password "YOUR_PASSWORD"    // Replace with your WiFi password
String serverName = "https://ntfy.sh/cat";  // URL to send notifications to
// #define base64_login ""         // Uncomment and set if you have access control. Use 'echo -n "user:pass" | base64' to generate this.
#define getinterval 10000          // Interval for checking WiFi signal strength (in milliseconds)

// Root certificate for HTTPS
const char root_ca[] PROGMEM = R"rawliteral(
-----BEGIN CERTIFICATE-----
MIIE3TCCA8WgAwIBAgISBFCU2/1Fxw45z6TIm6oH6rTzMA0GCSqGSIb3DQEBCwUA
MDMxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQwwCgYDVQQD
EwNSMTEwHhcNMjQwNzE3MTYxMzM5WhcNMjQxMDE1MTYxMzM4WjASMRAwDgYDVQQD
EwdudGZ5LnNoMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAvN5knHxZ
YnZxU6pscrlAi/srb4Lko19Gp0YXCqH1cteci8Kxx5V2aH0NM1g+hmUViuUVtC16
HxzxLxic+bzlNZzLanvjoTbyxsp8RdrfLsluyKpem4XO8KTKzLew0ohajdX80Opc
4Fxo1HdpYYs2Pj4sTsw9PEUVFH+DQD+V+cG6GiJfcQIJ1Wohb6y0yXxxmMz2ysiu
g+GiJ1smW/5Ys+oO4bDQYnS/em/2JmwUh+RwkIIqBiAEMlsqVLmdUP0sCcepy2EG
boSfCF0qfzMjSCPTBJ0Upe8yIvXNKgdtMX8pup1BFRRRuWSuYh2OBZLT6lVZD0qh
9Rx1OEz452birwIDAQABo4ICCjCCAgYwDgYDVR0PAQH/BAQDAgWgMB0GA1UdJQQW
MBQGCCsGAQUFBwMBBggrBgEFBQcDAjAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBQQ
W2B/qDtGJ1t9sk1NaFTL+o6SNTAfBgNVHSMEGDAWgBTFz0ak6vTDwHpslcQtsF6S
LybjuTBXBggrBgEFBQcBAQRLMEkwIgYIKwYBBQUHMAGGFmh0dHA6Ly9yMTEuby5s
ZW5jci5vcmcwIwYIKwYBBQUHMAKGF2h0dHA6Ly9yMTEuaS5sZW5jci5vcmcvMBIG
A1UdEQQLMAmCB250Znkuc2gwEwYDVR0gBAwwCjAIBgZngQwBAgEwggEDBgorBgEE
AdZ5AgQCBIH0BIHxAO8AdQB2/4g/Crb7lVHCYcz1h7o0tKTNuyncaEIKn+ZnTFo6
dAAAAZDBr3ZXAAAEAwBGMEQCIA9d2Bjk988OHJhM9maYn+ujsvdRqfgWmX3k4Slj
RHz/AiBFOdbYavwOfNpBBgFpzHHw4L3hkxB/TJWcf1Ns+t/PLQB2ABmYEHEJ8NZS
LjCA0p4/ZLuDbijM+Q9Sju7fzko/FrTKAAABkMGvdkgAAAQDAEcwRQIhAPGGXZ1Y
dL7bg8kwqHijlIgcBLyiRUo7P/d75BG16OIuAiBPociCWuS5E6dJrMGVo6FNwER8
Y/fpb/el9t3QWNcqczANBgkqhkiG9w0BAQsFAAOCAQEApygM7Z6B+275+0hhZxQW
/2u9qV2gw1fXChy1ecQ7wqhx/Dasw4N5aC/NwXUQ0+tIhnxSO2CfDOdQTqFNX3ua
6HszgX87WPFNLCHcWzOMWwq+HYNf2QK/QlB396flw6njSqdN0lnDJZC1Ncf494vD
IpQKwZHWhgmBVI2EJQDyXOZ2D0wrTfly0ToCLGmRTVWMEI7KD3/EqCNs3uoUze2s
saL/fxoLv+nm7cpQOtz1pgnwUXNFRXrdr7Lpi57TXXzt4vRdrFDZ/ylReboW7ZDG
7xFSTnG+eZ7JsOSqF1DwedbApG8wA8y8CMiSNNtlW5x5hOa34TmJJ4TVZd1Y5TIF
pw==
-----END CERTIFICATE-----
)rawliteral";

// Global variables
unsigned long gettimestamp = 0;           // Millis timestamp of last HTTPS GET call
unsigned long lastMessageTime = 1666810118; // UNIX time of last message that was processed (prevents processing of the same message multiple times)

// Setup function runs once when the board is powered on or reset
void setup() {
  Serial.begin(115200); // Start serial communication
  WiFi.begin(ssid, password); // Connect to WiFi
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("..Connected");
}

// Main loop
void loop() {
  if ((gettimestamp + getinterval) < millis()) {
    checkWiFiSignalStrength(); // Check WiFi signal strength every interval
    gettimestamp = millis();
  }
}

// Function to check WiFi signal strength
void checkWiFiSignalStrength() {
  int32_t rssi = WiFi.RSSI(); // Get RSSI (Received Signal Strength Indicator)
  int32_t signalStrength = map(rssi, -100, -50, 0, 100); // Map RSSI to percentage (0 to 100)

  Serial.print("WiFi Signal Strength: ");
  Serial.print(signalStrength);
  Serial.println("%");

  // Send notification if signal strength is less than 15%
  if (signalStrength < 15) {
    Serial.println("Signal strength is less than 15%. Sending notification...");
    sendMissingCatNotification(); // Send notification if signal is weak
  }
}

// Function to send a notification when the cat is missing
void sendMissingCatNotification() {
  if (WiFi.status() == WL_CONNECTED) { // Check if WiFi is connected
    HTTPClient https;
    if (https.begin(serverName, root_ca)) { // Start HTTPS connection
      https.addHeader("Content-Type", "text/plain"); // Set content type
      // #ifdef base64_login // Uncomment if using basic authentication
      // https.addHeader("Authorization", "Basic "base64_login);
      // #endif
      https.addHeader("title", "Cat Status"); // Set notification title
      String httpsRequestData = "The cat is missing"; // Notification message
      int httpsResponseCode = https.POST(httpsRequestData); // Send POST request
      Serial.print("[HTTPS] POST... code: ");
      Serial.println(httpsResponseCode); // Print response code
      https.end(); // End HTTPS connection
    } else {
      Serial.println("[HTTPS] Unable to connect"); // Connection failed
    }
  }
}
