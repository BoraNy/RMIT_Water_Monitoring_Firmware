#include "Parameter.h"

void SD_Card_Init(void) {
  if (!SD.begin(SD_Card_SS)) {
    Serial.println(" SD-Card not Found...!");
    while (1)
      ;
  } else {
    Serial.println(" SD-Card Found...!");
  }
}

void writeFile(const char* path, const char* message) {
  dataBackup = SD.open(path, FILE_WRITE);
  if (dataBackup) {
    Serial.printf(" Writting to %s", path);
    dataBackup.println(message);
    dataBackup.close();
    Serial.println("Complete...!");
  } else {
    Serial.println(" Error SD-Card...!");
  }
}

void data2SD_Card(void) {
  writeFile("Sensor Data:", " Tesing Data");
}