#ifndef timer_h
#define timer_h

#include "configuration.h"
#include <Arduino.h>
#include <time.h>

const unsigned long status_interval = STATUS_PACKET_INTERVAL * 1000; //convert s inteval to milliseconds
uint8_t check_timer();

#endif