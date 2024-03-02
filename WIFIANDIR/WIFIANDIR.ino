#include <WiFi.h>

#define IR_SENSOR_PIN 2

const char* ssid = "MARTIN ROUTER"; // WiFi network SSID
const char* password = "qwerty123"; // WiFi network password

void setup() {
  Serial.begin(9600);
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
  
  delay(1000);
}
