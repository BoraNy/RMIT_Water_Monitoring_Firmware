#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
/*---------------- Define Paramater-------------------*/
uint32_t delayMS = 0;
float Temperature,Turbidity,pH,Oxigen=0;
unsigned long previousMillis = 0;
const long interval = 5000;/*---- 5 seconds ----------*/
String messageStr = "";
/*---------------- MQTT Credentials ------------------*/
const char* ssid = "Linksys01430";/*---------- Wifi SSID ------------*/
const char* password = "ecw11wce";/*---------- Wifi Password -------------*/
const char* mqttServer = "broker.hivemq.com";/*---------- MQTT Broker --------------*/
const char* mqttUserName = "NPIC_MQTT";/*---------- MQTT Username--------------*/
const char* mqttPassword = "NPIC_RMIT_Project";/*---------- MQTT Password--------------*/
const char* clientID = "NPIC_ID_1";/*---------- Client ID--------------*/
const char* topic = "Message";/*---------- Topic of Data --------------*/
/*---------------- MQTT Credentials ------------------*/
WiFiClient NPIC_Client;
PubSubClient Client(NPIC_Client);
/*----------------------------------------------------*/
void Setup_Wifi(){/*-------- Set up Wifi -----------*/
  delay(5);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print("-");
  }
  Serial.println("");
  Serial.println("Wifi Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}
void MQTT_Reconnect(){/*-------- MQTT Reconnecting -----------*/
  while (!Client.connected()){
    if(Client.connect(clientID,mqttUserName,mqttPassword)){
      Serial.println("MQTT Connected");
      Client.subscribe("Hello");
      Serial.println("Topic Subcreibed");
    }
    else{
      Serial.print(" Connection Fail, rc=");
      Serial.print(Client.state());
      Serial.println(" retry again in 1 seconds");
      delay(1000);  // wait 5sec and retry
    }
  } 
}
void callback(char*topic, byte* payload, unsigned int length){
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
  Serial.begin(115200);
  Setup_Wifi();
  Client.setServer(mqttServer,1883);
  Client.setCallback(callback);

}
void loop() {
  if (!Client.connected()){
    MQTT_Reconnect();
  }
  Client.loop();
  Temperature = random(0,100);
  Turbidity = random(0,3000);
  pH = random(0,14);
  Oxigen = random(0,20);
  messageStr = String(Temperature)+","+String(Turbidity)+","+String(pH)+","+String(Oxigen)+",";
  byte arraySize = messageStr.length()+1;
  char message[arraySize];
  Serial.print("Public Data: ");
  Serial.println(messageStr);
  messageStr.toCharArray(message,arraySize);
  Client.publish(topic,message);
  messageStr = ""; /*----------- Reset String --------------*/
  delay(5);
}