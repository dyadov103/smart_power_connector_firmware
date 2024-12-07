#include "outlet.h"
#include "packet.h"
#include "serial.h"
#include "wifi_custom.h"
#include "mqtt_custom.h"
#include "configuration.h"
#include <time.h>

outlet outlets[NUM_OUTLETS];

const unsigned long status_interval = STATUS_PACKET_INTERVAL * 1000; //convert s inteval to milliseconds

bool fault = FAULT;

// Usable GPIO pins based on the ESP32 WROOM dev kit pinout
// The indexes of the arrays correspond to eachother. ex. outlet_1 has toggle pin 15 and adc pin 36
int usable_toggle_gpios[] = {23, 22, 1, 3, 21, 19}; //TODO: Implement an 8-to-1 MUX to support up to 8 outlets 
int usable_adc_gpios[] = {36, 39, 34, 35, 32, 33}; // All ADC2 pins are available

// 8-bit flag
uint8_t flag = 0;


void setup() {
  generate_serial();
  
  pinMode(BLUE_LED, OUTPUT);


  Serial.begin(9600);

  for (int i = 0; i < NUM_OUTLETS; i++) {
    outlets[i] = outlet(usable_adc_gpios[i], usable_toggle_gpios[i], i);
  }

  wifi_connect();
  connect_mqtt();

}


void loop() {
  // put your main code here, to run repeatedly:

  keep_alive();
  check_connection();


  if (Serial.available() > 0) {
    char input = Serial.read(); //serial monitor input parsing
    if (input == '\n' || input == '\r') {
      return;  // Skip further processing
    }
      flag = input - '0';
  }



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

    if (flag & STATUS_PACKET) {
      publish_message(build_status_packet(outlets, NUM_OUTLETS));
    }


  flag = 0;

}