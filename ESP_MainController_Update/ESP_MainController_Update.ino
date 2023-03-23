#include "Parameter.h"
/*---------------- MQTT Credentials ------------------*/
WiFiClient NPIC_Client;
PubSubClient Client(NPIC_Client);
/*----------------------------------------------------*/
void setup() {
  Serial.begin(GLOBAL_BAUDRATE);
  Serial1.begin(GLOBAL_BAUDRATE, SERIAL_8N1, RX_, TX_);
  I2Cone.begin(SDA_1, SCL_1, 100000);

  // check_serial();
  Setup_Wifi();
  MQTT_Init();
  Client.setServer(mqttServer, 1883);  //setting MQTT server
  Client.setCallback(callback); 
  // SD_Card_Init();
  RTC_Init();
}

void loop() {
  readSerial();
  // getDateTime();
  // data2SD_Card();
  Send2MQTT();
}