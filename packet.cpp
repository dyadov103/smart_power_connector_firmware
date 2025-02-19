#include "packet.h"
#include "serial.h"



String decode_request(const String &json, const String &key) {

  int start_index = json.indexOf("\"" + key + "\"");
  if (start_index == -1) return "";

  start_index = json.indexOf(":", start_index);
  if (start_index == -1) return "";

  start_index++; // Move past the colon
  while (start_index < json.length() && (json[start_index] == ' ' || json[start_index] == '{' || json[start_index] == '"')) {
      start_index++; // Skip whitespace, opening braces, or quotes
  }

  int end_index = start_index;
  while (end_index < json.length() && json[end_index] != ',' && json[end_index] != '}' && json[end_index] != '"') {
      end_index++; // Stop at comma, closing brace, or quote
  }

  return json.substring(start_index, end_index);
}






String build_status_packet(outlet *outlets, int size) {
  String packet = "{";
  packet += "\"deviceID\": \"";
  packet += serial;
  packet += "\",";
  for (int i = 0; i < size; i++) {
    packet += "\""; 
    packet += String(outlets[i].get_identifier()); 
    packet += "\":"; 
    packet += "{";
    packet += "\"power\""; 
    packet += ": "; 
    packet += String(outlets[i].get_power()); 
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
