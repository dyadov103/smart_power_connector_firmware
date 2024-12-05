#ifndef config_h
#define config_h

#define NUM_OUTLETS 6 // max possible outlets 6 until 8-to-1 mux is implemented

// Set status packet interval here in seconds
#define STATUS_PACKET_INTERVAL 300

//WIFI Credentials
#define WIFI_SSID "The crib"
#define WIFI_PASSWORD "twood2024"

//MQTT Credentials
#define SERVER "34.238.120.227"
#define PORT 1883
#define USER "smartpowerconnector"
#define MQ_PASS "seniordesign2024"
#define MQ_UPLINK_TOPIC "outlet/uplink"

//Builtin LED status indicator
#define BLUE_LED 2

//flag definitions
#define STATUS_PACKET 0b00000100 //flag to trigger uplink heartbeat status packet. Value 4
#define SERIAL_STATUS_PRETTY 0b00000010 //For demonstration purposes. Value: 2
#define SERIAL_STATUS 0b00000001 //For demonstration purposes. Value 1

//Fault Conditions
#define TIMEOUT 60
#define FAULT false

//Current Params
#define ADC_RESOLUTION 4096.0 // 12-bit ADC
#define VOLTAGE_REFERENCE 5.0 // Reference voltage in volts
#define CURRENT_SENSITIVITY 0.185 // ACS712 sensitivity in V/A
#define ZERO_CURRENT 2.5


#endif