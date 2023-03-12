#include "sensorLib.h"
#include "cryptography.h"
#include "filterAlgorithm.h"
#include "variable.h"

filter_s tempCFilter, PHFilter, TDSFilter, dissOxygenFilter;

void setup()
{
  Serial.begin(115200);

  /* --- Read Initialize Data for Filter Calibration --- */
  for (int i = 0; i < 10; i++)
  {
    tempCFilter.oldReading = readTemperatureSensor();
    PHFilter.oldReading = readPHSensor(PH_SENSOR_PIN, sensor.tempC);
    TDSFilter.oldReading = readTDSSensor(TDS_SENSOR_PIN, sensor.tempC);
    dissOxygenFilter.oldReading = readOxygenSensor(OXYGEN_SENSOR_PIN, sensor.tempC);
  }

  sensorInitialization();
}

void loop()
{
  /* --- Read Value from Sensors --- */
  // sensor.turbidity = readTurbiditySensor(TURBIDITY_SENSOR_PIN);
  sensor.tempC = readTemperatureSensor();
  sensor.PH = readPHSensor(PH_SENSOR_PIN, sensor.tempC);
  sensor.TDS = readTDSSensor(TDS_SENSOR_PIN, sensor.tempC);
  sensor.dissOxygen = readOxygenSensor(OXYGEN_SENSOR_PIN, sensor.tempC);

  /* --- Apply Filter Algorithm --- */
  LowPassFilter(sensor.tempC, &tempCFilter.newReading, &tempCFilter.oldReading,
                &sensor.tempC, BETA);
  LowPassFilter(sensor.dissOxygen, &dissOxygenFilter.newReading, &dissOxygenFilter.oldReading,
                &sensor.dissOxygen, BETA);
  LowPassFilter(sensor.PH, &PHFilter.newReading, &PHFilter.oldReading,
                &sensor.PH, BETA);
  LowPassFilter(sensor.TDS, &TDSFilter.newReading, &TDSFilter.oldReading,
                &sensor.TDS, BETA);

  /* --- Convert Floating Point to Integer --- */
  PH.float2int(sensor.PH, TWO_DIGIT_PRECISION);
  tempC.float2int(sensor.tempC, TWO_DIGIT_PRECISION);
  dissOxygen.float2int(sensor.dissOxygen, TWO_DIGIT_PRECISION);
  TDS.float2int(sensor.TDS, TWO_DIGIT_PRECISION);

  // serialDebug();

  if (millis() - tick >= 0)
  {
    tick = millis();
    sendDataToMain();
  }
}

void sendDataToMain(void)
{
  sprintf(sensor.data, "%d.%d,%d.%d,%d.%d,%d.%d\r\n",
          TDS.wholeNumber, TDS.fractional,
          PH.wholeNumber, PH.fractional,
          dissOxygen.wholeNumber, dissOxygen.fractional,
          tempC.wholeNumber, tempC.fractional);
  Serial.print(sensor.data);
}
