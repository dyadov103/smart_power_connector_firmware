#ifndef mqtt_h
#define mqtt_h

extern String last_packet;
extern int downlink_flag;
void connect_mqtt();
void publish_message(String packet);
void keep_alive();

#endif