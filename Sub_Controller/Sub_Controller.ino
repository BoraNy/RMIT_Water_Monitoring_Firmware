#include "sensorLib.h"

float tempC = 0,
      turbidity = 0,
      dissOxygen = 0,
      PH = 0;

void setup()
{
  Serial.begin(115200);

  sensorInitialization();
}

void loop()
{
  turbidity = readTurbiditySensor(TURBIDITY_SENSOR_PIN);
  tempC = readTemperatureSensor();
  PH = readPHSensor(PH_SENSOR_PIN, tempC);
  dissOxygen = readOxygenSensor(OXYGEN_SENSOR_PIN, tempC);

  Serial.print("TempC: "); Serial.print(tempC); Serial.print('\t');
  Serial.print("PH: "); Serial.print(PH); Serial.print('\t');
  Serial.print("Turbidity: "); Serial.print(turbidity); Serial.print('\t');
  Serial.print("Dissolve Oxygen: "); Serial.print(dissOxygen);
  Serial.println();
}
