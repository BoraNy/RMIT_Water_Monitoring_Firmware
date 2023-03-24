#include "Parameter.h"

void setup() {
  Serial.begin(GLOBLE_BAUDRATE);
  _LED();
  delay(2000);
  RTC_Init();
  Motor();
}
void loop() {
  getDateTime();

  trackAndControlPosition(POT_ADC_PIN, hour);
}
