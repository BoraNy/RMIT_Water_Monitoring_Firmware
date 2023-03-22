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

String serialData,
       delimiter = ",";
String splited[4];

void readSerial(void) {
  if (Serial1.available() > 0)
    serialData = Serial1.readStringUntil('\n');

  for (int i = 0; i < 4; i++)
  {
    splited[i] = serialData.substring(0, serialData.indexOf(delimiter));
    serialData.replace((splited[i] + ","), "");
  }

  TDS = splited[0];
  pH = splited[1];
  Oxigen = splited[2];
  Temperature = splited[3];
}
