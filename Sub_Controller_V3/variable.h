#ifndef __VARIABLE_H
#define __VARIABLE_H

#define REALTIME 0
#define EVERY_ONE_SECOND 1000
#define ENABLE 0x00
#define DISABLE 0x01

const float Qd = 0.1;
const float R = 0.001;

class sensor_s {
public:
  int turbidity = 0;
  float TDS = 0,
        tempC = 0,
        dissOxygen = 0,
        PH = 0;
  int sensorOrder;
  char data[100];

  int READING_SAMPLE = 5;
} sensor;

struct filter_s {
  float oldReading = 0;
  float newReading = 0;
};

const float BETA = 0.1;
float2int_S PH, dissOxygen, tempC, TDS;

#endif
