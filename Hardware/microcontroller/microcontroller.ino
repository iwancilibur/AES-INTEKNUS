#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

DHT dht(D2,DHT11);

// WiFi Parameters
const char* ssid = "www.interactiverobotics.club";
const char* password = "cilibur2019";
String HOST_NAME      = "192.168.1.13"; // change to your PC's IP address
String PATH_NAME      = "/aes/data-api.php";
String getData;


String inputkey="tuqZQhKP48e8Piuc"; //KEY untuk Encripsi
String inputIV ="zxtZQhMzx8e8Piuc"; //IV untuk Encripsi

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() {
  int suhu       = dht.readTemperature();
  int kelembaban = dht.readHumidity();
  
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  
    http.begin("http://" + String(HOST_NAME)+ String(PATH_NAME) + 
                           "?inputkey="     + String(inputkey) +
                           "&&iv="          + String(inputIV) +
                           "&&suhu="        + String(suhu) +
                           "&&kelembaban="  + String(kelembaban)); 
    int httpCode = http.GET();

    if (httpCode > 0) {
        //AMBIL DATA
        String payload = http.getString();
        payload.trim();
        Serial.println(payload);
      }
      http.end();
      delay(5000);
  }
}
