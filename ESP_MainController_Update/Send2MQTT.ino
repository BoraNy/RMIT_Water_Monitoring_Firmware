#include "Parameter.h"

void Setup_Wifi() { /*-------- Set up Wifi -----------*/
  Serial.println("[ INIT ] WIFI-CONNECT");
  delay(5);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("-");
  }
  Serial.println("");
  Serial.print("[  OK  ] WIFI IP: ");
  Serial.println(WiFi.localIP());
}

void MQTT_Reconnect() { /*-------- MQTT Reconnecting -----------*/
  while (!Client.connected()) {
    if (Client.connect(clientID, mqttUserName, mqttPassword)) {
      Serial.println("[  OK  ] MQTT");
      Client.subscribe("Hello");
      Serial.println("[  OK  ] TOPIC-SUBSCRIBED");
    } else {
      Serial.print("[FAILED] CONNECTION, RC=");
      Serial.print(Client.state());
      Serial.println(" RETRY-AGAIN-IN-1-SECOND");
      delay(1000);  // wait 5sec and retry
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  /*-------- Subcribe Call back -----------*/
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String data = "";
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    data += (char)payload[i];
  }
  Serial.println();
  Serial.print("Message size :");
  Serial.println(length);
  Serial.println();
  Serial.println("-----------------------");
  Serial.println(data);
}

void MQTT_Init(void) {
  Client.setServer(mqttServer, 1883);
  Client.setCallback(callback);
}

void Send2MQTT(void) {
  if (!Client.connected()) {
    MQTT_Reconnect();
  }
  Client.loop();
  messageStr = "{\"action\": \"notification/insert\",\"deviceId\": \"s3s9TFhT9WbDsA0CxlWeAKuZykjcmO6PoxK6\",\"notification\":{\"notification\": \"Temperature\",\"parameters\":{\"Temperature\":" + String(Temperature) + ",\"TDS\":" + String(TDS) + ",\"pH\":" + String(pH) + ",\"Oxygen\":" + String(Oxygen) + "}}}";
  byte arraySize = messageStr.length() + 1;
  char message[arraySize];
  messageStr.toCharArray(message, arraySize);
  if (serialData != "")
    Client.publish(topic, message);

  //Serial.print("Public Data: ");
  //Serial.println(messageStr);
  messageStr = "";  /*----------- Reset String --------------*/
  serialData = "";  // <-- Erase Everything in Serial Data
  delay(10);
}
