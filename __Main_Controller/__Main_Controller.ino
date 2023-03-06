#include "variable.h"

/*--- MQTT Credentials ---*/
WiFiClient NPIC_Client;
PubSubClient Client(NPIC_Client);

void setup()
{
  Serial.begin(115200);
  WiFi_Setup();
  MQTT_Init();
}

void loop()
{
  Data2SDCard();
  Data2IoTCloud();
  Data2MQTT();
  Data2GSM();
}
