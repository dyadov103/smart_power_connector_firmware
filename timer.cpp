#include "timer.h"

unsigned long last_status = 0;

uint8_t check_timer() {
  uint8_t flag_return = 0;
  unsigned long current_time = millis();

  if((current_time - last_status) > status_interval) {
    flag_return = flag_return + STATUS_PACKET;
    last_status = current_time;
  }

  return flag_return;
}