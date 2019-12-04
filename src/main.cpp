// Enable debug prints to serial monitor
#define MY_DEBUG
// Use a bit lower baudrate for serial prints on ESP8266 than default in MyConfig.h
#define MY_BAUD_RATE 115200
// Enables and select radio type (if attached)
#define MY_RADIO_RF24
#define MY_GATEWAY_ESP8266
#define MY_WIFI_SSID "svzt"
#define MY_WIFI_PASSWORD "qazwsxedc"
// Set the hostname for the WiFi Client. This is the hostname
// it will pass to the DHCP server if not static.
#define MY_HOSTNAME "ESP8266_GW"
// The port to keep open on node server mode
#define MY_PORT 1883
// How many clients should be able to connect to this gateway (default 1)
#define MY_GATEWAY_MAX_CLIENTS 2

#define MY_GATEWAY_MQTT_CLIENT
#define MY_GATEWAY_ESP8266
#define MY_CONTROLLER_IP_ADDRESS 192, 168, 100, 2
// Set this node's subscribe and publish topic prefix
#define MY_MQTT_PUBLISH_TOPIC_PREFIX "smartHomeGW-out"
#define MY_MQTT_SUBSCRIBE_TOPIC_PREFIX "smartHomeGW-in"

// Set MQTT client id
#define MY_MQTT_CLIENT_ID "smartHomeGW"

#include <MySensors.h>
// #include "test.h"

int flag;

void setup() 
{
  // function();
  flag=1;
}

void presentation()
{
	// Present locally attached sensors here
}

void loop()
{
  if (!_MQTT_client.connected()) {
    flag=1;
    }

  if (_MQTT_client.connected() && (flag==1))  {
    Serial.println("Connected MQTT");
    request(1, V_VAR1, 1);
    flag=0;
  }
}
void receive(const MyMessage &message) {
  if (message.type ==  V_VAR1) { 
    MyMessage msg_state(1, V_STATUS);
    send(msg_state.set(message.getBool()));
  }
}
