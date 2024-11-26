#include <PubSubClient.h>
#include <Arduino.h>
#include "mqtt_custom.h"
#include "serial.h"
#include "configuration.h"
#include <WiFi.h>


WiFiClient espClient;
PubSubClient client(espClient);


const char* server = SERVER;
const int port = PORT;
const char* uplink_topic = MQ_UPLINK_TOPIC;
const char* mqtt_username = USER;
const char* mqtt_password = MQ_PASS;


void connect_mqtt() {
  client.setBufferSize(512);
  client.setServer(server, port);
  String client_id = String(serial);
  while (!client.connected()) {
    if (client.connect(client_id.c_str()), mqtt_username, mqtt_password, NULL, 0, false, NULL, false) { // Use a unique client ID
      Serial.println("Connected to server");
    } 
    else {
      Serial.print("failed with state ");
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