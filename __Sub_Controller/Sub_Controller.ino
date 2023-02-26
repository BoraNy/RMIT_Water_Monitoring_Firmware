#include "sensorLib.h"
#include "cryptography.h"

struct sensor_s
{
  int turbidity = 0;
  float tempC = 0,
        dissOxygen = 0,
        PH = 0;
  char data[50];
} sensor;

static unsigned long tick = 0;
float2int_S PH, dissOxygen, tempC;

void setup()
{
  Serial.begin(115200);

  sensorInitialization();
}

void loop()
{
  /* --- Read Value from Sensors --- */
  sensor.turbidity = readTurbiditySensor(TURBIDITY_SENSOR_PIN);
  sensor.tempC = readTemperatureSensor();
  sensor.PH = readPHSensor(PH_SENSOR_PIN, sensor.tempC);
  sensor.dissOxygen = readOxygenSensor(OXYGEN_SENSOR_PIN, sensor.tempC);

  /* --- Convert Floating Point to Integer --- */
  PH.float2int(sensor.PH, TWO_DIGIT_PRECISION);
  tempC.float2int(sensor.tempC, TWO_DIGIT_PRECISION);
  dissOxygen.float2int(sensor.dissOxygen, TWO_DIGIT_PRECISION);

  // serialDebug();

  if (millis() - tick >= 1000)
  {
    tick = millis();
    sendDataToMain();
  }
}

void sendDataToMain(void)
{
  sprintf(sensor.data, "%d,%d.%d,%d.%d,%d.%d\r\n",
          sensor.turbidity,
          PH.wholeNumber, PH.fractional,
          dissOxygen.wholeNumber, dissOxygen.fractional,
          tempC.wholeNumber, tempC.fractional);
  Serial.print(sensor.data);
}
