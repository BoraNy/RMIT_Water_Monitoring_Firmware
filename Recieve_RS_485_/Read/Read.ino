struct
{
  float temperature;
  float turbidity;
  float ph;
  float oxygen;
} data2read;
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}
void loop() {
  if (Serial1.available() > 0)
  {
    Serial1.readBytes((uint8_t*)&data2read, sizeof(data2read));
    Serial.print("Data : ");
    Serial.print(data2read.temperature);
    Serial.print("\t");
    Serial.print(data2read.turbidity);
    Serial.print("\t");
    Serial.print(data2read.ph);
    Serial.print("\t");
    Serial.println(data2read.oxygen);
    delay(10);

  }
}
