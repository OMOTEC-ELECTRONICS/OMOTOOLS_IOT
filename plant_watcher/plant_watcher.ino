#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "code.h"

const char *ssid = "Omo_Backup_2";//Change ID
const char *password = "Omotec#909";//Change password

const int ledPin = D8;   // Connect the LED to D2
const int soilPin = A0;  // Connect the soil sensor to A0

ESP8266WebServer server(80);

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(soilPin, INPUT);
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    int soilValue = analogRead(soilPin);
    Serial.println(soilValue);
    String statusMessage;
    String statusColor;
    String gifURL;

    // Determine soil moisture status
    if (soilValue > 100) {
      digitalWrite(ledPin,HIGH);
      statusMessage = "Need water";
      statusColor = "red";
      gifURL = "https://media2.giphy.com/media/Yoi7H75JB38dHERFVB/giphy.gif?cid=6c09b952mh7a5md0z0zp15tfebnw8szhr5lmwryf8x4j30ss&ep=v1_internal_gif_by_id&rid=giphy.gif&ct=s";
    } else {
      digitalWrite(ledPin,LOW);
      statusMessage = "Happy plant";
      statusColor = "green";
      gifURL = "https://media3.giphy.com/media/OUjA1hqT0LNOQyb4nx/giphy.gif?cid=6c09b952h9xv2ghfm7bvy5q092agsblipf8hell3131k71wj&ep=v1_internal_gif_by_id&rid=giphy.gif&ct=s";
    }

    String html = String(htmlContent);
    html.replace("{statusMessage}", statusMessage);
    html.replace("{statusColor}", statusColor);
    html.replace("{soilValue}", String(soilValue));
    html.replace("{gifURL}", gifURL);

    server.send(200, "text/html", html);
  });
  server.begin();
}

void loop() {

  server.handleClient();
}
