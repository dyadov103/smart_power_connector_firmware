#include <PubSubClient.h>
#include <Arduino.h>
#include "mqtt_custom.h"
#include "serial.h"
#include "configuration.h"
#include <WiFi.h>
#include "packet.h"


WiFiClient espClient;
PubSubClient client(espClient);


const char* server = SERVER;
const int port = PORT;
const char* uplink_topic = MQ_UPLINK_TOPIC;
const char* downlink_topic = MQ_DOWNLINK_TOPIC;
const char* mqtt_username = USER;
const char* mqtt_password = MQ_PASS;

String last_packet = "";
int downlink_flag = 0;

void downlink_msg(char* topic, byte* payload, unsigned int length) {
  String str_payload = "";
  for (int i = 0; i < length; i++) { 
    str_payload += (char)payload[i];
  }
  last_packet = str_payload;
  downlink_flag = 8;
}

void connect_mqtt() {
  unsigned long begin_connect_ts = millis();
  client.setBufferSize(512);
  client.setServer(server, port);
  client.setCallback(downlink_msg);
  String client_id = String(serial);
  while (!client.connected() && (millis() - begin_connect_ts) < TIMEOUT * 1000) {
    if (client.connect(client_id.c_str()), mqtt_username, mqtt_password) { // Use a unique client ID
      client.subscribe(downlink_topic);
    } 
    else {
      Serial.println(client.state());
      delay(2000); // Retry after 2 seconds
    }
  }
}

void publish_message(String packet) {
  client.publish(uplink_topic, packet.c_str());
}


void keep_alive() {
  if (!client.connected()) {
        connect_mqtt();
  }
  client.loop();
}