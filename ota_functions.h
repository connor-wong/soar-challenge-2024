#include <ota_functions.cpp>
#include <Arduino.h>

/* Local Network Config */
#define SSID ""
#define PASSWORD ""

void OTA_SETUP(void) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);  // Connect to local network


  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(500);
    ESP.restart();
  }

  ArduinoOTA.begin();
}