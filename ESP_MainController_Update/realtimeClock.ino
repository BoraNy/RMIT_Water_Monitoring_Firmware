#include "Parameter.h"

void RTC_Init(void) {
  if (!rtc.begin()) {
    Serial.println("[FAILED] RTC");
  } else {
    Serial.print("[  OK  ] RTC");
  }
  //rtc.adjust(DateTime(__DATE__, __TIME__));
}

void getDateTime(void) {
  DateTime now = rtc.now();
  second = now.secondstime();
  minute = now.minute();
  hour = now.hour();
  day = now.day();
  month = now.month();
  year = now.year();
}
