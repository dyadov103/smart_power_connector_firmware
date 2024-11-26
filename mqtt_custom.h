#ifndef mqtt_h
#define mqtt_h

void connect_mqtt();
void publish_message(String packet);
void keep_alive();

#endif