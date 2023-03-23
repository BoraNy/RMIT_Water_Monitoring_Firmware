void serialSplitter(void) {
  Serial.println(data);

  for (int i = 0; i < 4; i++) {
    splited[i] = data.substring(0, data.indexOf(delimiter));
    data.replace((splited[i] + ","), "");
  }

  Serial.println();
  Serial.println(splited[0]);
  Serial.println(splited[1]);
  Serial.println(splited[2]);
  Serial.println(splited[3]);
}

void I2CScanner(void) {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++) {
    I2Cone.beginTransmission(address);
    error = I2Cone.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknow error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
  delay(5000);
}