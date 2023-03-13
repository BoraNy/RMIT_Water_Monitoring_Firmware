#include "variable.h"

void WiFi_Setup()
{ /*-------- Set up Wifi -----------*/
  delay(5);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print("-");
  }
  Serial.println("");
  Serial.println("Wifi Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void MQTT_Reconnect()
{ /*-------- MQTT Reconnecting -----------*/
  while (!Client.connected())
  {
    if (Client.connect(clientID, mqttUserName, mqttPassword))
    {
      Serial.println("MQTT Connected");
      Client.subscribe("Hello");
      Serial.println("Topic Subcreibed");
    }
    else
    {
      Serial.print(" Connection Fail, rc=");
      Serial.print(Client.state());
      Serial.println(" retry again in 1 seconds");
      delay(1000); // wait 5sec and retry
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  /*-------- Subcribe Call back -----------*/
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String data = "";
  for (int i = 0; i < length; i++)
  {
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

void MQTT_Init(void)
{
  Client.setServer(mqttServer, 1883);
  Client.setCallback(callback);
}

void Data2MQTT(void)
{
  if (!Client.connected())
  {
    MQTT_Reconnect();
  }
  Client.loop();
  Temperature = random(0, 100);
  Turbidity = random(0, 3000);
  pH = random(0, 14);
  Oxigen = random(0, 20);
  messageStr = "{\"action\": \"notification/insert\",\"deviceId\": \"s3s9TFhT9WbDsA0CxlWeAKuZykjcmO6PoxK6\",\"notification\":{\"notification\": \"Temperature\",\"parameters\":{\"Temperature\":" + String(Temperature) + ",\"Turbidity\":" + String(Turbidity) + ",\"pH\":" + String(pH) + ",\"Oxigen\":" + String(Oxigen) + "}}}";
  byte arraySize = messageStr.length() + 1;
  char message[arraySize];
  Serial.print("Public Data: ");
  Serial.print("Temerature: ");
  Serial.print(Temperature);
  Serial.print("\t");
  Serial.print("Turbidity: ");
  Serial.print(Turbidity);
  Serial.print("\t");
  Serial.print("pH: ");
  Serial.print(pH);
  Serial.print("\t");
  Serial.print("Oxigen: ");
  Serial.print(Oxigen);
  Serial.print("\n");
  messageStr.toCharArray(message, arraySize);
  Client.publish(topic, message);
  messageStr = ""; /*----------- Reset String --------------*/
  delay(100);
}