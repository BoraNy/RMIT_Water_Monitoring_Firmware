#include "Parameter.h"
/*---------------- MQTT Credentials ------------------*/
WiFiClient NPIC_Client;
PubSubClient Client(NPIC_Client);
/*----------------------------------------------------*/
void setup() {
  Serial.begin(GLOBAL_BAUDRATE);
  check_serial();
  RTC_Init();
  Setup_Wifi();
  MQTT_Init();
  Client.setServer(mqttServer, 1883);  //setting MQTT server
  Client.setCallback(callback);
  // SD_Card_Init();
}

void loop() {
  //RTC_Init();
  //SD_Card_Init();
  //check_serial();
  //delay(100);
  readSerial();
  //Serial.print(TDS);
  getDateTime();
  //data2SD_Card();
  Send2MQTT();
}
