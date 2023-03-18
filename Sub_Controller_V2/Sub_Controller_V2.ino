#include "cryptography.h"
#include "filterAlgorithm.h"
#include "variable.h"

filter_s tempCFilter, PHFilter, TDSFilter, dissOxygenFilter;

void setup() {
  Serial.begin(115200);

  /* --- Read Initialize Data for Filter Calibration --- */
  sensorInitialization();
  sequenceSensorReading();
}

void loop() {
  /* --- Read Value from Sensors --- */
  // sensor.turbidity = readTurbiditySensor(TURBIDITY_SENSOR_PIN);
  sequenceSensorReading();

  /* --- Apply Filter Algorithm --- */
  LowPassFilter(sensor.tempC, &tempCFilter.newReading, &tempCFilter.oldReading, &sensor.tempC, BETA);
  LowPassFilter(sensor.dissOxygen, &dissOxygenFilter.newReading, &dissOxygenFilter.oldReading,
                &sensor.dissOxygen, BETA);
  LowPassFilter(sensor.PH, &PHFilter.newReading, &PHFilter.oldReading,
                &sensor.PH, BETA);
  LowPassFilter(sensor.TDS, &TDSFilter.newReading, &TDSFilter.oldReading,
                &sensor.TDS, BETA);

  sendDataToMainSerial(REALTIME);
}
