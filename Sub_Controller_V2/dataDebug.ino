void serialDebug() {
  Serial.print("TempC: ");
  Serial.print(sensor.tempC);
  Serial.print('\t');
  Serial.print("PH: ");
  Serial.print(sensor.PH);
  Serial.print('\t');
  Serial.print("TDS: ");
  Serial.print(sensor.TDS);
  Serial.print('\t');
  Serial.print("Dissolve Oxygen: ");
  Serial.print(sensor.dissOxygen);
  Serial.println();
}

void debugPHandDissolvedOxygen(void)
{
  Serial.print(sensor.PH);
  Serial.print(',');
  Serial.println(sensor.dissOxygen);
}
