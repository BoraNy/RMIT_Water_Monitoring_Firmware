#include "Parameter.h"

void readSerial(void){
    if (Serial2.available() > 0) {
    String data2read = Serial2.readStringUntil('\n');
    TDS = data2read.substring(0, 4);
    pH = data2read.substring(5, 9);
    Oxigen = data2read.substring(10, 14);
    Temperature = data2read.substring(15, 20);
  }
}
