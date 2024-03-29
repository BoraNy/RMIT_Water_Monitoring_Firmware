#ifndef SENSOR_LIB_H
#define SENSOR_LIB_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include <DFRobot_PH.h>
#include <EEPROM.h>

/* --- Sensor Pins --- */
#define TDS_SENSOR_PIN 3
#define TURBIDITY_SENSOR_PIN 0
#define PH_SENSOR_PIN 1
#define OXYGEN_SENSOR_PIN 2

/* --- Temperature Sensor Parameters --- */
#define DS18B20_PIN 13
OneWire oneWire(DS18B20_PIN);
DallasTemperature DS18B20(&oneWire);

/* --- pH Sensor Parameters --- */
DFRobot_PH ph;
float Voltage;
float PHValue;

/* --- Oxygen Sensor Parameters --- */
#define VREF 5000     // VREF (mv)
#define ADC_RES 1024  // ADC Resolution

// Single-point calibration Mode=0
// Two-point calibration Mode=1
#define TWO_POINT_CALIBRATION 0

#define READ_TEMP (25)  // Current water temperature ℃, Or temperature sensor function

// Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1600)  // mv
#define CAL1_T (25)    // ℃
// Two-point calibration needs to be filled CAL2_V and CAL2_T
// CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300)  // mv
#define CAL2_T (15)    // ℃

uint8_t Temperaturet;
uint16_t ADC_Raw;
uint16_t ADC_Voltage;
uint16_t DO;

const uint16_t DO_Table[41] = {
  14460, 14220, 13820, 13440, 13090, 12740, 12420,
  12110, 11810, 11530, 11260, 11010, 10770, 10530,
  10300, 10080, 9860, 9660, 9460, 9270, 9080, 8900,
  8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
  7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730,
  6630, 6530, 6410
};

void sensorInitialization() {
  DS18B20.begin();
  ph.begin();
}

float readPHSensor(int analogPin, int temperature, float *returnValue) {
  // float ph = analogRead(analogPin);
  // return ph * 0.017;
  static unsigned long timepoint = millis();
  if (millis() - timepoint > 1000U) {
    timepoint = millis();
    Temperaturet = (uint8_t)temperature;
    Voltage = analogRead(analogPin) / 1024.0 * 5000;
    PHValue = ph.readPH(Voltage, Temperaturet);
    *returnValue = PHValue;
  }
  ph.calibration(Voltage, Temperaturet);
}

float readTurbiditySensor(int analogPin) {
  float v = analogRead(analogPin) * 5.0 / 1024;
  if (v <= 2.5)
    return 3000;
  if (v >= 4.2002)
    return 0;

  return (-1120.4 * sq(v) + 5742.3 * v - 4352.9);
}

float readTemperatureSensor(float *returnValue) {
  DS18B20.requestTemperatures();
  *returnValue = DS18B20.getTempCByIndex(0);
}

/* --- Oxygen Sensor Functions --- */
int16_t readDO(uint32_t voltage_mv, uint8_t temperature_c) {
#if TWO_POINT_CALIBRATION == 00
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperature_c - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#endif
}

float readOxygenSensor(int analogPin, int temperature, float *returnValue) {
  Temperaturet = (uint8_t)temperature;
  ADC_Raw = analogRead(analogPin);
  ADC_Voltage = (uint32_t(VREF) * ADC_Raw / ADC_RES);
  *returnValue = readDO(ADC_Voltage, Temperaturet) * 1e-3;  //mg/L
}

static const int TDS_SAMPLING_DATA = 30;
static int analogBuffer[TDS_SAMPLING_DATA];
static int analogBufferTemp[TDS_SAMPLING_DATA];
static int analogBufferIndex = 0, copyIndex = 0;
static float averageVoltage = 0, tdsValue = 0;

/* --- TDS Sensor --- */
int getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];

  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }

  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}

float readTDSSensor(int analogPin, float temperature, float *returnValue) {
  static float TDS_Reading;

  static unsigned long analogSampleTimepoint = millis();
  if (millis() - analogSampleTimepoint >= 40U) {
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(analogPin);
    analogBufferIndex++;
    if (analogBufferIndex == TDS_SAMPLING_DATA)
      analogBufferIndex = 0;
  }

  static unsigned long calculationTimeout = millis();
  if (millis() - calculationTimeout >= 800U) {
    calculationTimeout = millis();
    for (copyIndex = 0; copyIndex < TDS_SAMPLING_DATA; copyIndex++)
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];

    averageVoltage = getMedianNum(analogBuffer, TDS_SAMPLING_DATA) * 5.0 / 1024.0;
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
    float compensationVoltage = averageVoltage / compensationCoefficient;
    TDS_Reading = (133.42 * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5;
    *returnValue = TDS_Reading;
  }
}

#endif
