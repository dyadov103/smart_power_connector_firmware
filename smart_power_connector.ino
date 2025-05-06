#include "outlet.h"
#include "packet.h"
#include "serial.h"
#include "wifi_custom.h"
#include "mqtt_custom.h"
#include "configuration.h"
#include <time.h>
#include "timer.h"

outlet outlets[NUM_OUTLETS];

bool fault = FAULT;

// Usable GPIO pins based on the ESP32 WROOM dev kit pinout
// The indexes of the arrays correspond to eachother. ex. outlet_1 has toggle pin 15 and adc pin 36
int usable_toggle_gpios[] = {23, 22, 21, 19, 18, 5}; //TODO: Implement an 8-to-1 MUX to support up to 8 outlets 
int usable_adc_gpios[] = {36, 39, 34, 35, 32, 33}; // All ADC2 pins are available

// flag is 8 bits but stored in 16 bit due to overflow
uint16_t flag = 16; // set flag to 16 on boot to perform outlet calibration


void setup() {
  generate_serial();
  
  pinMode(BLUE_LED, OUTPUT);
  analogReadResolution(12);


  Serial.begin(9600);

  //init outlet objects
  for (int i = 0; i < NUM_OUTLETS; i++) {
    outlets[i] = outlet(usable_adc_gpios[i], usable_toggle_gpios[i], i);
  }


  wifi_connect();
  connect_mqtt();

  publish_message(build_status_packet(outlets, NUM_OUTLETS));
}


void loop() {
  // put your main code here, to run repeatedly:

  keep_alive();
  check_connection();

  flag += check_timer() + downlink_flag;


if (Serial.available() > 0) {
    int input = Serial.parseInt(); 
    if (input > 0) {              
        flag += input;             
    }
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
    if (Serial.availableForWrite() > 0) Serial.println("Status Packet Uplinked to RabbitMQ");
  }

  if (flag & TOGGLE_OUTLET) {
    String key_value = "";
    for(int i = 0; i < NUM_OUTLETS; i++) {
      key_value = decode_request(last_packet, outlets[i].get_identifier());
      if(key_value != "") {
          outlets[i].set_status(key_value.toInt());
      }
    }
    if (Serial.availableForWrite() > 0) {
      Serial.println("Downlink request handled for: " + last_packet);
    } 
    downlink_flag = 0;
    last_packet = "";
    publish_message(build_status_packet(outlets, NUM_OUTLETS));
    if (Serial.availableForWrite() > 0) Serial.println("Status Packet Uplinked to RabbitMQ, in response to downlink req");
  }

  if (flag & CAILIBRATE_OUTLETS) {
    Serial.println("Calibrating Outlets");

    for(int i = 0; i < NUM_OUTLETS; i++) {
      outlets[i].set_status(0);
      delay(10);
      outlets[i].calibrate_outlet();
      delay(10);
      outlets[i].set_status(1);
      delay(5000); // wait for current to change
      outlets[i].calibrate_error();
      delay(10);
      outlets[i].set_status(0);
    }
    Serial.println("Finished Calibration");
  }

  flag = 0;

}