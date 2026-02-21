#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "WiFiS3.h"
#include <ArduinoJson.h>

// --- CONFIGURATION ---
const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";
const char* serverIP = "169.197.141.196"; // IP for api.OpenWeatherMap.org
String apiKey = "Enter_API_key"; //Make a Free api key on OpenWeatherMap.org. Remember only 1,000,000 free monthly limit. This code ensures that you will not be charged
String city ="CITY:Name,Country initials"; //EX: "London,uk" 

ArduinoLEDMatrix matrix;
WiFiClient client; 

void setup() {
  Serial.begin(115200);
  matrix.begin();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  Serial.println("WiFi Connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    getWeather();
  } else {
    WiFi.begin(ssid, pass);
  }
  // Update every 2 minutes
  delay(120000); 
}

void getWeather() {
  // Using Port 80 for Direct IP
  if (client.connect(serverIP, 80)) {
    client.print("GET /data/2.5/weather?q=" + city + "&units=metric&appid=" + apiKey + " HTTP/1.1\r\n");
    client.print("Host: api.openweathermap.org\r\n");
    client.print("Connection: close\r\n\r\n");

    unsigned long start = millis();
    while (client.available() == 0 && millis() - start < 5000) delay(1);
    delay(1000); 

    if (client.find("\r\n\r\n")) {
      StaticJsonDocument<1024> doc;
      if (!deserializeJson(doc, client)) {
        if (doc["cod"] == 200) {
          int temp = doc["main"]["temp"];
          String msg = String(temp) + "C"; 
          
          Serial.println("Updating Matrix: " + msg);

          
          matrix.beginDraw();
          matrix.stroke(0xFFFFFFFF);
          matrix.textFont(Font_4x6); // Essential to fit 3 chars on 12 pixels
          matrix.beginText(0, 1, 0xFFFFFF); // (x, y) start position
          matrix.print(msg);
          matrix.endText();
          matrix.endDraw();
        }
      }
    }
  }
  client.stop();
}

