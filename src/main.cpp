#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "CLARO726";     // Replace with your Wi-Fi SSID
const char* password = "26090300"; // Replace with your Wi-Fi password

WiFiClient client;
HTTPClient http;

void httpGet();

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  httpGet();
}

void loop() {
  // Nothing to do in the loop
}


void httpGet() {
  if (WiFi.status() == WL_CONNECTED) { // Check Wi-Fi connection

    http.begin(client,"http://jsonplaceholder.typicode.com/posts/1"); // Specify your URL
    int httpCode = http.GET(); // Make the request

    if (httpCode > 0) { // Check for the returning code
      Serial.printf("HTTP GET Response code: %d\n", httpCode);
      String payload = http.getString(); // Get the request response payload
      Serial.println("Response:");
      Serial.println(payload);
    } else {
      Serial.printf("HTTP GET failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end(); // Free resources
  }
}