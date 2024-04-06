#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <LOLIN_I2C_BUTTON.h>

I2C_BUTTON button; // I2C address 0x31
const char* ssid = "HackBeta";
const char* password = "OleMiss2024!!";
const char* serverAddress = "localhost";
const int serverPort = 8000;

String keyString[] = {"None", "Press", "Long Press", "Double Press", "Hold"};
bool buttonState = false;
bool start = true;

void setup() {
  
}

void loop() {
  if(start==true){
    Serial.begin(115200);
    delay(100);
    Serial.println("Connecting to WiFi");
  // Connect to Wi-Fi
    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    start=false;

  }
  delay(2000); // Wait for 2 seconds

  if (button.get() == 0) {
    if (button.BUTTON_A) {
      Serial.print("BUTTON A: ");
      Serial.println(keyString[button.BUTTON_A]);
    }
    if (button.BUTTON_B) {
      Serial.print("BUTTON B: ");
      Serial.println(keyString[button.BUTTON_B]);
    }
  }

  // Read button state
  buttonState = (button.get() == 0);

  // Make HTTP POST request
  WiFiClient client;
  if (client.connect(serverAddress, serverPort)) {
    Serial.println("Connected to server");
    String postData = "buttonState=" + String(buttonState);
    client.println("POST /sensor-data HTTP/1.1");
    client.println("Host: " + String(serverAddress));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.println(postData);
  } else {
    Serial.println("Connection failed");
  }
}
