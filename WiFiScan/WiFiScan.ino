#define IR_SENSOR_PIN 2 // Pin connected to the digital output of the IR sensor
#include <WiFi.h> 

void setup() {
  Serial.begin(9600);
  pinMode(IR_SENSOR_PIN, INPUT);
  connectToWiFi(); 
}

void loop() {
  // Read the state of the IR sensor
  int sensorState = digitalRead(IR_SENSOR_PIN);
  
  // Print the state to the serial monitor
  Serial.print("IR Sensor State: ");
  Serial.println(sensorState);
  
  delay(500); // Adjust delay as needed for your testing
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi");
  
  WiFi.begin("Mwanje","20141955"); // Connect to WiFi network
  
  while (WiFi.status() != WL_CONNECTED) { // Wait for WiFi connection
    delay(1000);
    Serial.println("Connecting...");
  }
  
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the IP address
}