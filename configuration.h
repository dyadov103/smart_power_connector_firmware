#ifndef config_h
#define config_h

#define NUM_OUTLETS 10 // max possible outlets 12

// Set hearbeat interval here in seconds
#define HEARTBEAT_INTERVAL 300

//WIFI Credentials
#define SSID "" //redacted for security
#define PASSWORD ""


//flag definitions
#define HEARTEBEAT 0b00000100 //flag to trigger uplink heartbeat status packet. Value 4
#define SERIAL_STATUS 0b00000010 //For demonstration purposes. Value: 2
#define SERIAL_HEARTBEAT 0b00000001 //For demonstration purposes. Value 1


#endif