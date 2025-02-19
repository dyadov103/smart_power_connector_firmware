#ifndef packet_h
#define packet_h

#include <Arduino.h>
#include "outlet.h"

String build_status_packet(outlet *outlets, int size);
String decode_request(const String &json, const String &key);


#endif