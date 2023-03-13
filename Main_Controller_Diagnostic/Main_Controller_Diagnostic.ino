#define GLOBAL_BAUDRATE 115200
#define SERIAL_FROM_SUB_TX 27
#define SERIAL_FROM_SUB_RX 26

void setup() {
  Serial.begin(GLOBAL_BAUDRATE);
  Serial2.begin(GLOBAL_BAUDRATE, SERIAL_8N1, SERIAL_FROM_SUB_RX, SERIAL_FROM_SUB_TX);
  Serial.println("Serial Initialized");
}

void loop() {
  if (Serial2.available() > 0)
    Serial.print(Serial2.readString());
}
