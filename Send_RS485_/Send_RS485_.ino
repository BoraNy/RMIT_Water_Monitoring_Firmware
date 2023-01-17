struct
{
  float temperature;
  float turbidity;
  float ph;
  float oxygen;
} data2send;
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}
void loop() {
  data2send.temperature = random(0, 100);
  data2send.turbidity = random(0, 100);
  data2send.ph = random(0, 100);
  data2send.oxygen = random(0, 100);
  Serial1.write((uint8_t*)&data2send, sizeof(data2send));
  delay(5);
}
