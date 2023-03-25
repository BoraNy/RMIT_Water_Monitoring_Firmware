#include "Parameter.h"

void setup() {
  Serial.begin(GLOBLE_BAUDRATE);
  LEDInit();
  RTCInit();
  //motorInit(POT_ADC_PIN);
}

void loop() {
  getDateTime();

  manualPositionControl(POT_ADC_PIN);
  // trackAndControlPosition(POT_ADC_PIN, hour);
}
