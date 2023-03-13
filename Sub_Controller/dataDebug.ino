void serialDebug() {
  Serial.print("TempC: ");
  Serial.print(sensor.tempC);
  Serial.print('\t');
  Serial.print("PH: ");
  Serial.print(sensor.PH);
  Serial.print('\t');
  Serial.print("Turbidity: ");
  Serial.print(sensor.turbidity);
  Serial.print('\t');
  Serial.print("Dissolve Oxygen: ");
  Serial.print(sensor.dissOxygen);
  Serial.println();
}
