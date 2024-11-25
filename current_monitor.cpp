#include "current_monitor.h"
#include <Arduino.h>

current_monitor::current_monitor(int pin) {
  pin_num = pin;
}


int current_monitor::get_current() {
  return analogRead(pin_num);
}