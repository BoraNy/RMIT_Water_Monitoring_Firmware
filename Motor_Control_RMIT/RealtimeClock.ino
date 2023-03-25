#include "Parameter.h"

void RTCInit(void) {
  if (!RTC.begin()) {
    Serial.println(" Couldn't find RealtimeClock");
    while (1) {
      Blink();
    }
  } else {
    Serial.println("Ready for RealtimeClock");
    digitalWrite(LED, 1);
  }
  RTC.adjust(DateTime(__DATE__, __TIME__));
}

void getDateTime(void) {
  DateTime now = RTC.now();
  second = now.secondstime();
  minute = now.minute();
  hour = now.hour();
  day = now.day();
  month = now.month();
  year = now.year();
}
void showTime(void) {
  Serial.print(" Time :");
  Serial.print(" Hour:");
  Serial.print(hour);
  Serial.print("\t");
  Serial.print(" Minute:");
  Serial.println(minute);
}
