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
  runMotor(1, 200);/*---------- Forward ------------*/
  delay(2000);
  runMotor(-1, 200);/*---------- Backward ------------*/
  delay(2000);
}
