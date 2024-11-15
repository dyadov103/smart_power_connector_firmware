#include "outlet.h"
#include "packet.h"


#define NUM_OUTLETS 8

outlet outlets[NUM_OUTLETS];

// Usable GPIO pins based on the ESP32 WROOM dev kit pinout
int usable_toggle_gpios[] = {15, 2, 0, 4, 16, 17, 5, 18, 19, 21, 3, 1, 22};
int usable_adc_gpios[] = {36, 39, 34, 35, 32, 33, 25, 26, 27, 14, 12, 13};

String command = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Port Initialized");
  for (int i = 0; i < NUM_OUTLETS; i++) {
    
  }


}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    command.trim();

    if(command == "read_status") {
      for (int i = 0; i < NUM_OUTLETS; i++) {
        Serial.println(outlets[i].get_pin_num());
        Serial.println(outlets[i].get_power());
      }
    }
    else if(command = "build_packet") {
        Serial.println(build_status_packet(outlets, NUM_OUTLETS));
      }

  }

}
