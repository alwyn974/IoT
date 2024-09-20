/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp8266-web-server-gauges/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include <Adafruit_BME280.h>

// Replace with your network credentials
const char* ssid = "";
const char* password = "";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Create a sensor object
Adafruit_BME280 bme;         // BME280 connect to ESP32 I2C (GPIO 21 = SDA, GPIO 22 = SCL)

// Initialize LittleFS
void initFS() {
    if (!LittleFS.begin()) {
        Serial.println("An error has occurred while mounting LittleFS");
    }
    Serial.println("LittleFS mounted successfully");
}

// Initialize WiFi
void initWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(115200);
    initWiFi();
    initFS();

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", "text/html");
    });

    server.serveStatic("/", LittleFS, "/");

    // Start server
    server.begin();
}

void loop() {
    if ((millis() - lastTime) > timerDelay) {
        // Send Events to the client with the Sensor Readings Every 30 seconds
        lastTime = millis();
    }
}