#ifndef packet_h
#define packet_h

#include <Arduino.h>
#include "outlet.h"

String build_status_packet(outlet *outlets, int size);


#endif