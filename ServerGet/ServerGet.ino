#include <WiFi.h>
#include <WiFiClientSecure.h> // Changed library include
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "michaelmungai";
const char* password = "qwerty123";

// Your Domain name with URL path or IP address with path
const char* serverName = "https://projectserver-mbht.onrender.com/homeOwners";

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

String serverRes;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      serverRes = httpsGETRequest(serverName); 
      Serial.println("Response from server:");
      Serial.println(serverRes);

      JSONVar myObject = JSON.parse(serverRes);
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }

      // Serial.print("JSON object = ");
      // Serial.println(myObject);

      // JSONVar keys = myObject.keys();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpsGETRequest(const char* serverName) { // Changed function name
  WiFiClientSecure client; // Changed client type
  HTTPClient http;

  http.begin(serverName);

  String payload = "";

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  return payload;
}
