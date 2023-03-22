#include "Parameter.h"
/*---------------- MQTT Credentials ------------------*/
WiFiClient NPIC_Client;
PubSubClient Client(NPIC_Client);
/*----------------------------------------------------*/

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
  MQTT_Reconnect();
  MQTT_Init();
  SD_Card_Init();
  RTC_Init();
}
void loop() {
  readSerial();
  getDateTime();
  data2SD_Card();
  Send2MQTT();
}