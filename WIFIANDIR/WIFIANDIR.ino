#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h> // Include ArduinoJson library

#define IR_SENSOR_PIN 2

const char* ssid = "MARTIN ROUTER"; // WiFi network SSID
const char* password = "qwerty123"; // WiFi network password

const char* serverName = "http://localhost:3000/sensorState";

unsigned long timerDelay = 20000;
unsigned long lastTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(IR_SENSOR_PIN, INPUT);

  // Connect to WiFi
  Serial.println();
  Serial.println("Connecting to WiFi network: " + String(ssid));
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Attempting to connect to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void loop() {
  int sensorState = digitalRead(IR_SENSOR_PIN);

  Serial.print("IR Sensor State: ");
  Serial.println(sensorState);

  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status() == WL_CONNECTED){
      // WiFiClient client;
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(serverName);

      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");

      // Send HTTP GET request
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        
        // Get the response payload
        String payload = http.getString();
        Serial.println("Response:");
        Serial.println(payload);
        
        // Parse JSON
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.f_str());
          return;
        }

        // Access JSON values
        const char* name = doc["name"];
        
        // Print JSON values
        Serial.print("Name: ");
        Serial.println(name);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
