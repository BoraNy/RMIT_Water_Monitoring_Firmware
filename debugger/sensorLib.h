#ifndef SENSOR_LIB_H
#define SENSOR_LIB_H

#include <OneWire.h>
#include <DallasTemperature.h>

/* --- Temperature Sensor Parameters --- */
#define DS18B20_PIN             4
OneWire oneWire(DS18B20_PIN);
DallasTemperature DS18B20(&oneWire);


/* --- Oxygen Sensor Parameters --- */
#define VREF                    5000
#define ADC_RES                 1024
#define TWO_POINT_CALIBRATION   0
#define READ_TEMP               (25)
#define CAL1_V                  (131)
#define CAL1_T                  (25)
#define CAL2_V                  (1300)
#define CAL2_T                  (15)

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

void sensorInitialization()
{
  DS18B20.begin();
}

float readPHSensor(int analogPin)
{
  float ph = analogRead(analogPin);
  return ph * 0.017;
}

float readTurbiditySensor(int analogPin)
{
  float v = analogRead(analogPin);
  return (-1120.4 * sq(v) + 5742.3 * v - 4352.9);
}

float readTemperatureSensor()
{
  DS18B20.requestTemperatures();
  return DS18B20.getTempCByIndex(0);
}

/* --- Oxygen Sensor Functions --- */
int16_t readDO(uint32_t voltage_mv, uint8_t temperature_c)
{
#if TWO_POINT_CALIBRATION == 00
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperature_c - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#endif
}

float readOxygenSensor(int analogPin, int temperature)
{
  Temperaturet = (uint8_t)temperature;
  ADC_Raw = analogRead(analogPin);
  ADC_Voltage = (uint32_t(VREF) * ADC_Raw / ADC_RES);
  return readDO(ADC_Voltage, Temperaturet);
}

#endif
