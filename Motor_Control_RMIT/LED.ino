#include "Parameter.h"

void LEDInit(void) {
  pinMode(LED, OUTPUT);
}

void Blink(void) {
  digitalWrite(LED, 1);
  delay(500);
  digitalWrite(LED, 0);
  delay(500);
}