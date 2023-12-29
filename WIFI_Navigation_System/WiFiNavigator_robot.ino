// main.ino
#include <ESP8266WiFi.h>
#include "code.h"

const char *ssid = "WIFI NAME";//change as per wifi name
const char *password = "PASSWARD";//change as per wifi name

const int motorForwardPin = D3;
const int motorBackwardPin = D4;
const int motorLeftPin = D5;
const int motorRightPin = D6;

ESP8266WebServer server(80);

void setup() {
Serial.begin(9600);

  pinMode(motorForwardPin, OUTPUT);
  pinMode(motorBackwardPin, OUTPUT);
  pinMode(motorLeftPin, OUTPUT);
  pinMode(motorRightPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", HTTP_GET, handleRoot);
  server.on("/motor", HTTP_GET, handleMotor);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
   server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", htmlContent);
}

void handleMotor() {
 String direction = server.arg("direction");

  // Motor control logic
  if (direction == "forward") {
    digitalWrite(motorForwardPin, HIGH);
    digitalWrite(motorBackwardPin, LOW);
  } else if (direction == "backward") {
    digitalWrite(motorForwardPin, LOW);
    digitalWrite(motorBackwardPin, HIGH);
  } else if (direction == "left") {
    digitalWrite(motorLeftPin, HIGH);
    digitalWrite(motorRightPin, LOW);
  } else if (direction == "right") {
    digitalWrite(motorLeftPin, LOW);
    digitalWrite(motorRightPin, HIGH);
  } else {
    // Stop all motors if the direction is unknown or not specified
    digitalWrite(motorForwardPin, LOW);
    digitalWrite(motorBackwardPin, LOW);
    digitalWrite(motorLeftPin, LOW);
    digitalWrite(motorRightPin, LOW);
  }

  server.send(200, "text/plain", "OK");
}
