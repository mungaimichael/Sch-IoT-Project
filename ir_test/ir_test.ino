#include <WiFi.h> // Include the WiFi library

#define WIFI_SSID "Martin Router King" // Replace with your WiFi SSID
#define WIFI_PASSWORD "Kingsarise" // Replace with your WiFi password

#define IR_SENSOR_PIN 2 // Pin connected to the digital output of the IR sensor
#define LED_PIN 13 // Pin connected to the second LED on the board

bool obstacleDetected = false;
unsigned long obstacleStartTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  connectToWiFi(); // Connect to WiFi
}

void loop() {
  // Read the state of the IR sensor
  int sensorState = digitalRead(IR_SENSOR_PIN);
  
  // Check if an obstacle is detected
  if (sensorState == HIGH) {
    if (!obstacleDetected) {
      // If obstacle detected for the first time, start the timer
      obstacleStartTime = millis();
      obstacleDetected = true;
    } else {
      // Check if the obstacle has been continuously detected for more than 10 seconds
      unsigned long currentTime = millis();
      if (currentTime - obstacleStartTime >= 10000) { // 10 seconds
        // Record the obstacle
        recordObstacle();
        // Reset obstacle detection
        obstacleDetected = false;
      }
    }
  } else {
    // If no obstacle detected, reset obstacle detection
    obstacleDetected = false;
    digitalWrite(LED_PIN, LOW); // Ensure LED is off
  }

  delay(100); // Adjust delay as needed for your testing
}

void recordObstacle() {
  // Code to record the obstacle (e.g., log to the serial monitor, save to memory, etc.)
  Serial.println("Obstacle detected for more than 10 seconds");
  
  // Toggle the LED
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi");
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Connect to WiFi network
  
  while (WiFi.status() != WL_CONNECTED) { // Wait for WiFi connection
    delay(1000);
    Serial.println("Connecting...");
  }
  
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the IP address
}
