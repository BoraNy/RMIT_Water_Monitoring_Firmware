#include "cryptography.h"
#include "filterAlgorithm.h"
#include "variable.h"
#include "kalmanFilter.h"

KalmanFilter KF_pH, KF_Turbidity, KF_Temperature, KF_DO;

void setup() {
  Serial.begin(115200);

  /* --- Initialize Filter --- */
  KF_pH.init(Qd, R);
  KF_Turbidity.init(Qd, R);
  KF_Temperature.init(Qd, R);
  KF_DO.init(Qd, R);

  /* --- Read Initialize Data for Filter Calibration --- */
  sensorInitialization();
  unsigned long startUpTime = millis();
  while (startUpTime < 20000) {
    startUpTime = millis();
    sensorStartupSampling();
  }
}

void loop() {
  /* --- Read Value from Sensors --- */
  // sensor.turbidity = readTurbiditySensor(TURBIDITY_SENSOR_PIN);
  // sequenceSensorReadingMethod0();
  // sequenceSensorReadingMethod1();
  sequenceSensorReadingMethod2();

  /* --- Apply Filter Algorithm --- */

  sendDataToMainSerial(EVERY_ONE_SECOND);
}
