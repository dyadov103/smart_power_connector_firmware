#include "outlet.h"
#include "packet.h"
#include "serial.h"
#include "configuration.h"
#include <time.h>

outlet outlets[NUM_OUTLETS];

// Usable GPIO pins based on the ESP32 WROOM dev kit pinout
// The indexes of the arrays correspond to eachother. ex. outlet_1 has toggle pin 15 and adc pin 36
int usable_toggle_gpios[] = {15, 2, 0, 4, 16, 17, 5, 18, 19, 21, 3, 1, 22};
int usable_adc_gpios[] = {36, 39, 34, 35, 32, 33, 25, 26, 27, 14, 12, 13};

// 8-bit flag
uint8_t flag = 0;


void setup() {
  generate_serial();
  Serial.begin(9600);
  Serial.println("Serial Port Initialized");

  for (int i = 0; i < NUM_OUTLETS; i++) {
    outlets[i] = outlet(usable_adc_gpios[i], usable_toggle_gpios[i], i);
  }


}


void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    char input = Serial.read(); //serial monitor input parsing
    if (input == '\n' || input == '\r') {
      return;  // Skip further processing
    }
    flag = input - '0';


    if(flag & SERIAL_STATUS_PRETTY) { // command to demo the device
      Serial.println("Device Serial Number: " + String(serial));
      for (int i = 0; i < NUM_OUTLETS; i++) {
        Serial.println("------------------------------");
        Serial.println("Outlet Name: " + outlets[i].get_identifier());
        Serial.println("Toggle Pin Number: " + String(outlets[i].get_toggle_pin_num()));
        Serial.println("Current Monitor Pin Number: " + String(outlets[i].get_current_pin_num()));
        Serial.println("Power Reading (Watts): " + String(outlets[i].get_power()));
        Serial.println("------------------------------");
      }
    }
    
    if(flag & SERIAL_STATUS) {
        Serial.println(build_status_packet(outlets, NUM_OUTLETS));
    }
  }
  flag = 0;


}