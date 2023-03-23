#include <Wire.h>

#define TX_ 22
#define RX_ 19
String data = "123.12,321.32,456.65,789.98",
       delimiter = ",";
String splited[4];

#define SDA_1 27
#define SCL_1 26
TwoWire I2Cone = TwoWire(0);

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RX_, TX_);
  I2Cone.begin(SDA_1, SCL_1, 100000); 
}

void loop() {
  I2CScanner();
}
