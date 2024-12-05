#include "wifi_custom.h"
#include "configuration.h"
#include <Arduino.h>
#include <WiFi.h>

//WIFI Credentials
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void wifi_connect() {
  unsigned long begin_connect_ts = millis();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED && (millis() - begin_connect_ts) < TIMEOUT * 1000) {
    digitalWrite(BLUE_LED, HIGH); // Turn LED on
    delay(500);
    digitalWrite(BLUE_LED, LOW); // Turn LED off
    delay(500);
  }
  digitalWrite(BLUE_LED, LOW);
}


void check_connection() {
  if(WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    wifi_connect();
  }


}