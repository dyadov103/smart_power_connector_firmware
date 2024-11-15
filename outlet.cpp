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

}

int outlet::get_pin_num() {
  return toggle_pin_num;
}

String outlet::get_identifier() {
  return identifier;
}

int outlet::get_power() {
  current_monitor cm;
  int power = cm.get_current();
  return power;
}
