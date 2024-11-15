#include "outlet.h"


#define NUM_OUTLETS 8

outlet outlets[NUM_OUTLETS];

// Usable GPIO pins based on the ESP32 WROOM dev kit pinout
int usable_toggle_gpios[] = {15, 2, 0, 4, 16, 17, 5, 18, 19, 21, 3, 1, 22};
int usable_adc_gpios[] = {36, 39, 34, 35, 32, 33, 25, 26, 27, 14, 12, 13};


void setup() {

  for (int i = 0; i < NUM_OUTLETS; i++) {
    
  }


}

void loop() {
  // put your main code here, to run repeatedly:

}
