#ifndef config_h
#define config_h

#define NUM_OUTLETS 10 // max possible outlets 12

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


#endif