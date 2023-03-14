#ifndef __VARIABLE_H
#define __VARIABLE_H

#define PH_SENSOR_CALIBRATION 11.53763019
#define DISSOLVED_OXYGEN_CALIBRATION 3.578413759

struct sensor_s {
  int turbidity = 0;
  float TDS = 0;
  float tempC = 0,
        dissOxygen = 0,
        PH = 0;
  char data[100];
} sensor;

struct filter_s {
  float oldReading = 0;
  float newReading = 0;
};

const float BETA = 0.9;
static unsigned long tick = 0;
float2int_S PH, dissOxygen, tempC, TDS;

#endif