#include "packet.h"





String build_status_packet(outlet *outlets, int size) {
  String packet = "{";
  for (int i = 0; i < size; i++) {
    packet += "{"; 
    packet += "\""; 
    packet += String(outlets[i].get_identifier()); 
    packet += ":\""; 
    packet += "{";
    packet += "\"power\""; 
    packet += ": \""; 
    packet += String(outlets[i].get_power()); 
    packet += "\"";
    packet += "}";
    if (i < size - 1) {
      packet += "},";
    }
    else {
      packet += "}";
    }
  }
  packet += "}";



  return packet;
}
