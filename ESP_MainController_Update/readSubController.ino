#include "Parameter.h"

/*
  void readSerial(void) {
  if (Serial.available() > 0) {
    String data2read = Serial.readStringUntil('\n');
    TDS = data2read.substring(0, 4);
    pH = data2read.substring(5, 9);
    Oxigen = data2read.substring(10, 14);
    Temperature = data2read.substring(15, 20);
  }
  }
*/
void check_serial(void) {
  if (!Serial) {
    Serial.print("[FAILED] SUB-SYSTEM-DATA");
    while (1)
      ;
  } else {
    Serial.println("[  OK  ] SUB-SYSTEM-DATA");
  }
}

void readSerial(void) {
  while (Serial.available() > 0)
    serialData = Serial.readStringUntil('\n');

  Serial.print("[  OK  ] DATA: ");
  Serial.println(serialData);

  for (int i = 0; i < 4; i++) {
    splited[i] = serialData.substring(0, serialData.indexOf(delimiter));
    serialData.replace((splited[i] + ","), "");
  }

  TDS = splited[0];
  pH = splited[1];
  Oxygen = splited[2];
  Temperature = splited[3];
}
