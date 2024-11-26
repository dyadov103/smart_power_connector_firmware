#include <WiFi.h>
#include <Arduino.h>
unsigned long serial = -1;

void generate_serial() {
  uint64_t mac = ESP.getEfuseMac(); 
  serial = (mac & 0xFFFFFF) % 1000000;
}