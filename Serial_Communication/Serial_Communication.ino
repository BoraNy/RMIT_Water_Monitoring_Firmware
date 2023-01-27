float turbidity = 0,
      pH = 0,
      dissolveOxygen = 0,
      temperature = 0;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  turbidity = rand() % 50000 + rand() % 1000 * 1e-3;
  pH = rand() % 14 + rand() % 1000 * 1e-3;
  dissolveOxygen = rand() % 3000 + rand() % 1000 * 1e-3;
  temperature = rand() % 150 + rand() % 1000 * 1e-3;

  Serial.print(turbidity);
  Serial.print(",");
  Serial.print(pH);
  Serial.print(",");
  Serial.print(dissolveOxygen);
  Serial.print(",");
  Serial.print(temperature);
  Serial.println();
}
