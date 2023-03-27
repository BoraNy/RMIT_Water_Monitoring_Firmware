#include "Parameter.h"

void LEDInit(void) {
  pinMode(LED, OUTPUT);
}

static void blinker(unsigned long wait) {
  static unsigned long tick = 0;
  static bool state = true;
  if (millis() - tick >= wait) {
    tick = millis();
    digitalWrite(LED, state);
    state = !state;
  }
}
