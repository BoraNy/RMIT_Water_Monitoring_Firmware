#include "Parameter.h"

void LEDInit(void) {
  pinMode(LED, OUTPUT);
}

static unsigned long tick = 0;
static bool state = true;

void blinker(void) {
  if (millis() - tick >= 500) {
    tick = millis();
    digitalWrite(LED, state);
    state = !state;
  }
}