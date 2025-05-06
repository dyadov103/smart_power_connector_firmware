#include "outlet.h"
#include "current_monitor.h"


outlet::outlet() {
  current_mon_pin_num = -1;
  toggle_pin_num = -1;
  identifier = "n/a";
}

outlet::outlet(int current, int toggle, int index) {
  current_mon_pin_num = current;
  toggle_pin_num = toggle;
  identifier = "outlet_" + String(index + 1);
  
  cm.set_pin_num(current);
  pinMode(toggle, OUTPUT);

}

int outlet::get_toggle_pin_num() {
  return toggle_pin_num;
}

int outlet::get_current_pin_num() {
  return current_mon_pin_num;
}

String outlet::get_identifier() {
  return identifier;
}


float outlet::get_power() {
  float power = cm.get_current();

  if (get_status() == 0 ) {
    return 0.0;
  }

  //return random(120, 3600 + 1);
  return power * 120;
}

void outlet::calibrate_outlet() {
  cm.calibrate_zero_current();
}

void outlet::calibrate_error() {
  cm.error_factor_calibration();
}

void outlet::set_status(bool toggle_value) {
  digitalWrite(toggle_pin_num, toggle_value);
}

bool outlet::get_status() {
  return digitalRead(toggle_pin_num);
}
