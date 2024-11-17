#include "outlet.h"
#include "packet.h"
#include "serial.h"

#define NUM_OUTLETS 10 // max possible outlets 12

outlet outlets[NUM_OUTLETS];

// Usable GPIO pins based on the ESP32 WROOM dev kit pinout
int usable_toggle_gpios[] = {15, 2, 0, 4, 16, 17, 5, 18, 19, 21, 3, 1, 22};
int usable_adc_gpios[] = {36, 39, 34, 35, 32, 33, 25, 26, 27, 14, 12, 13};

String command = "";

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
    command = Serial.readStringUntil('\n');
    command.trim();

    if(command == "read_status") {
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
    else if(command == "build_packet") {
        Serial.println(build_status_packet(outlets, NUM_OUTLETS));
      }
  }

}