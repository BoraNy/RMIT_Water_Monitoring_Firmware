#include "Parameter.h"

void SD_Card_Init(void) {
  if (!SD.begin(SD_Card_SS)) {
    Serial.println("[FAILED] SD-CARD");
  } else {
    Serial.print("[  OK  ] SD-CARD");
  }
}

void writeFile(const char* path, const char* message) {
  dataBackup = SD.open(path, FILE_WRITE);
  if (dataBackup) {
    Serial.printf(" Writting to %s", path);
    dataBackup.println(message);
    dataBackup.close();
    Serial.println("[  OK  ] WRITE-SD-CARD");
  } else {
    Serial.println("[FAILED] WRITE-SD-CARD");
  }
}

void data2SD_Card(void) {
  writeFile("Sensor Data:", " Tesing Data");
}