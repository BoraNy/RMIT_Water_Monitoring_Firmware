const int bufferlength = 50;
char data2read [bufferlength];
uint8_t charIndex = 0 ;
char inByte;
void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
}
void loop()
{
  if (Serial1.available() > 0)
  {
    inByte = Serial1.read();
    if (inByte != '\n' && (charIndex < bufferlength - 1)) {
      data2read[charIndex] = inByte;
      charIndex++;
    }
    else {
      data2read[charIndex] = '\0';
      Serial.print("Data: ");
      Serial.println(data2read);
      charIndex = 0;
    }
  }
}
