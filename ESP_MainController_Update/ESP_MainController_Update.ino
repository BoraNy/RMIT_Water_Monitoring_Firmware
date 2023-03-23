#include "Parameter.h"
/*---------------- MQTT Credentials ------------------*/
WiFiClient NPIC_Client;
PubSubClient Client(NPIC_Client);
/*----------------------------------------------------*/

void setup() {
  Serial.begin(GLOBAL_BAUDRATE);
  Serial1.begin(GLOBAL_BAUDRATE, SERIAL_8N1, RX_, TX_);
  if (!Serial1) {
    Serial.print(" Check Connection from Sub-controller");
    while (1)
      ;
  } else {
    Serial.println(" Ready for Serial Read ");
  }

  Setup_Wifi();
  MQTT_Init();
  Client.setServer(mqttServer, 1883);  //setting MQTT server
  Client.setCallback(callback);
  // SD_Card_Init();
  // RTC_Init();
}

void loop() {
  readSerial();
  // getDateTime();
  // data2SD_Card();
  Send2MQTT();
}