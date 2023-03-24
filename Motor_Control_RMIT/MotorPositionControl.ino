void trackAndControlPosition(uint8_t adcPin, uint8_t time) {
  const int MAX_ADC_READING = -1,
            MIN_ADC_READING = -1;
  const int MAX_HOUR = -1,
            MIN_HOUR = -1;

  /* --- (!!Integer is Good Enough) Use Linear Equation for Relation of Position and Hour --- */
  long setPoint = map(time, MIN_HOUR, MAX_HOUR, MIN_ADC_READING, MAX_ADC_READING);
  long error = analogRead(adcPin) - setPoint;

  if (error > 0) {
    runMotor(-1, 200); /*---------- Backward ------------*/
    delay(2000);
  } else {
    runMotor(1, 200); /*---------- Forward ------------*/
    delay(2000);
  }
}