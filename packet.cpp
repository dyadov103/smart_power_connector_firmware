#include "packet.h"
#include "serial.h"





String build_status_packet(outlet *outlets, int size) {
  String packet = "\"{";
  packet += "\"deviceID\": \"";
  packet += serial;
  packet += "\",";
  for (int i = 0; i < size; i++) {
    packet += "\""; 
    packet += String(outlets[i].get_identifier()); 
    packet += "\":"; 
    packet += "\"{";
    packet += "\"power\""; 
    packet += ": \""; 
    packet += String(outlets[i].get_power()); 
    packet += "\"";
    if (i < size - 1) {
      packet += "}\",";
    }
    else {
      packet += "}\"";
    }
  }
  packet += "}\"";



  return packet;
}
