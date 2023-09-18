#include <WiFi.h>
#include <HTTPClient.h>

// WiFi Parameters
const char* ssid = "www.interactiverobotics.club";
const char* password = "cilibur2019";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() {
  // Check WiFi Status
  float datax = random(0, 100);
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://192.168.43.211/backend/test1.php?data=" + String(datax));
    int httpCode = http.GET();
    delay(1000);
    http.end();   //Close connection
  }
}
