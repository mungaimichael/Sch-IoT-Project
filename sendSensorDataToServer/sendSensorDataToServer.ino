#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#define IR_SENSOR_PIN 2

const char* ssid = "HOTBOX";
const char* password = "grandson@2001";
const char* serverName = "https://projectserver-mbht.onrender.com/sensorState";
const int WIFI_RECONNECT_DELAY = 20000;
const int REQUEST_DELAY = 5000;

void setup() {
  Serial.begin(115200);
  connectToWifi();
  pinMode(IR_SENSOR_PIN, INPUT);
}

void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int sensorState = digitalRead(IR_SENSOR_PIN);

  // Try reconnecting to WiFi if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Attempting to reconnect...");
    connectToWifi();
  }

  // Check if sensorState is 0
  if (sensorState == 0) {
    WiFiClientSecure client;
    HTTPClient https;
    client.setInsecure(); // Skip SSL certificate verification

    if (https.begin(client, serverName)) {
      // Set the Content-Type header to application/json
      https.addHeader("Content-Type", "application/json");

      // Create a JSON object with the data to be sent
      JSONVar jsonData;
      jsonData["value"] = sensorState;

      // Serialize the JSON object to a string
      String jsonString = JSON.stringify(jsonData);

      // Send the POST request with the JSON data
      int httpResponseCode = https.POST(jsonString);

      if (httpResponseCode > 0) {
        String response = https.getString();
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        Serial.print("Response: ");
        Serial.println(response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }
      https.end();
    } else {
      Serial.println("Error in connection to server");
    }
  }

  delay(REQUEST_DELAY); // Wait before the next request
}
