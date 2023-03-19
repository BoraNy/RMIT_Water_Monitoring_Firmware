#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#define GLOBAL_BAUDRATE 115200
#define SERIAL_FROM_SUB_TX 27
#define SERIAL_FROM_SUB_RX 26
/*---------------- Serial Read Paramater-------------------*/

String TDS;
String pH;
String Oxigen;
String Temperature;
/*---------------- Define Paramater-------------------*/
String messageStr = "";
/*---------------- MQTT Credentials ------------------*/
const char* ssid = "Astro-X";                   /*---------- Wifi SSID ------------*/
const char* password = "Heang187";              /*---------- Wifi Password -------------*/
const char* mqttServer = "broker.hivemq.com";   /*---------- MQTT Broker --------------*/
const char* mqttUserName = "NPIC_MQTT";         /*---------- MQTT Username--------------*/
const char* mqttPassword = "NPIC_RMIT_Project"; /*---------- MQTT Password--------------*/
const char* clientID = "NPIC_ID_1";             /*---------- Client ID--------------*/
const char* topic = "Message";                  /*---------- Topic of Data --------------*/
/*---------------- MQTT Credentials ------------------*/
WiFiClient NPIC_Client;
PubSubClient Client(NPIC_Client);
/*----------------------------------------------------*/
void Setup_Wifi() { /*-------- Set up Wifi -----------*/
  delay(5);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("-");
  }
  Serial.println("");
  Serial.println("Wifi Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}
void MQTT_Reconnect() { /*-------- MQTT Reconnecting -----------*/
  while (!Client.connected()) {
    if (Client.connect(clientID, mqttUserName, mqttPassword)) {
      Serial.println("MQTT Connected");
      Client.subscribe("Hello");
      Serial.println("Topic Subcreibed");
    } else {
      Serial.print(" Connection Fail, rc=");
      Serial.print(Client.state());
      Serial.println(" retry again in 1 seconds");
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
  for (int i = 0; i < length; i++) {
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
void setup() {
  Serial.begin(GLOBAL_BAUDRATE);
  Serial2.begin(GLOBAL_BAUDRATE, SERIAL_8N1, SERIAL_FROM_SUB_RX, SERIAL_FROM_SUB_TX);
  if (!Serial2) {
    Serial.print(" Check Connection from Sub-controller");
    while (1)
      ;
  } else {
    Serial.println(" Ready for Serial Read ");
  }
  Setup_Wifi();
  Client.setServer(mqttServer, 1883);
  Client.setCallback(callback);
}
void loop() {
  if (Serial2.available() > 0) {
    String data2read = Serial2.readStringUntil('\n');
    TDS = data2read.substring(0, 4);
    pH = data2read.substring(5, 9);
    Oxigen = data2read.substring(10, 14);
    Temperature = data2read.substring(15, 20);
    ;
    if (!Client.connected()) {
      MQTT_Reconnect();
    }
    Client.loop();
    messageStr = "{\"action\": \"notification/insert\",\"deviceId\": \"s3s9TFhT9WbDsA0CxlWeAKuZykjcmO6PoxK6\",\"notification\":{\"notification\": \"Temperature\",\"parameters\":{\"Temperature\":" + String(Temperature) + ",\"TDS\":" + String(TDS) + ",\"pH\":" + String(pH) + ",\"Oxigen\":" + String(Oxigen) + "}}}";
    byte arraySize = messageStr.length() + 1;
    char message[arraySize];
    messageStr.toCharArray(message, arraySize);
    Client.publish(topic, message);
    Serial.print("Public Data: ");
    messageStr = ""; /*----------- Reset String --------------*/
    delay(10);
  }
}