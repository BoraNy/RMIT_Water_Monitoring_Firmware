#define GLOBAL_BAUDRATE 115200
#define SERIAL_FROM_SUB_TX 27
#define SERIAL_FROM_SUB_RX 26

const int bufferlength = 50;
char data2read [bufferlength];
uint8_t charIndex = 0 ;
char inByte;

void setup()
{
  Serial.begin(GLOBAL_BAUDRATE);
  Serial2.begin(GLOBAL_BAUDRATE, SERIAL_8N1, SERIAL_FROM_SUB_RX, SERIAL_FROM_SUB_TX);
}

void loop()
{
  if (Serial2.available() > 0)
  {
    inByte = Serial2.read();
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
