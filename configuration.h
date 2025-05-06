#ifndef config_h
#define config_h

#define NUM_OUTLETS 4 // max possible outlets 6 until 8-to-1 mux is implemented

// Set status packet interval here in seconds
#define STATUS_PACKET_INTERVAL 300

//WIFI Credentials
#define WIFI_SSID "Daniel"
#define WIFI_PASSWORD "12345678"

//MQTT Credentials
#define SERVER "44.212.28.132"
#define PORT 1883
#define USER "smartpowerconnector"
#define MQ_PASS "seniordesign2024"
#define MQ_UPLINK_TOPIC "outlet/uplink"
#define MQ_DOWNLINK_TOPIC "outlet/downlink"

//Builtin LED status indicator
#define BLUE_LED 2

//flag definitions
#define STATUS_PACKET 0b00000100 //flag to trigger uplink heartbeat status packet. Value 4
#define SERIAL_STATUS_PRETTY 0b00000010 //For demonstration purposes. Value: 2
#define SERIAL_STATUS 0b00000001 //For demonstration purposes. Value 1
#define TOGGLE_OUTLET 0b00001000 //Flag to trigger uplink cycle, current buffer size is 1 message. Value 8
#define CAILIBRATE_OUTLETS 0b00010000 //Calibrates the ACS712 Current Sensors. Value 16

//Fault Conditions
#define TIMEOUT 60
#define FAULT false

//Current Params
#define ADC_RESOLUTION 1023.0 // 
#define VOLTAGE_REFERENCE 3.3 // Reference voltage in volts
#define CURRENT_SENSITIVITY 0.185// ACS712 sensitivity in V/A. 0.066 for the 30A module. 0.185 for the 5A module
#define ZERO_CURRENT 1.65
#define NUM_SAMPLES 1000 //Defines the number of samples that will be taken to determine AC current values
#define EXPECTED_CURRENT 0.035 // Defines the expected current for led 3.5W lamp


#endif