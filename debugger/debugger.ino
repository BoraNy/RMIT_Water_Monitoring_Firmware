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
  turbidity = readTurbiditySensor(0);
  tempC = readTemperatureSensor();
  PH = readPHSensor(1);
  dissOxygen = readOxygenSensor(2, tempC);

  Serial.print("TempC: "); Serial.print(tempC); Serial.print('\t');
  Serial.print("PH: "); Serial.print(PH); Serial.print('\t');
  Serial.print("Turbidity: "); Serial.print(turbidity); Serial.print('\t');
  Serial.print("Dissolve Oxygen: "); Serial.print(dissOxygen);
  Serial.println();
}
