#define QUATER_SPEED int(255 / 4)
#define HALF_SPEED int(255 / 2)
#define FULL_SPEED 255
#define STARTUP_MOTOR_DELAY 0
#define MOTOR_DELAY 0
#define FILTER_SAMPLING 2000

float oldReading = 0;
float newReading = 0;
const float BETA = 0.1;

const int MAX_ADC_READING = 18,
          MIN_ADC_READING = 0;
const int MAX_HOUR = 18,
          MIN_HOUR = 6;
float adcReading = 0;
long setPoint = 0,
     error = 0;

void LowPassFilter(float noisySignal, float *newReading, float *oldReading,
                   float *filteredSignal, const float beta) {
  *newReading = beta * noisySignal + (1 - beta) * (*oldReading);
  *oldReading = *newReading;
  *filteredSignal = *newReading;
}

void motorInit(uint8_t adcPin) {
  /* --- Move Up --- */
  oldReading = analogRead(adcPin);
  while (int(adcReading) < (MAX_ADC_READING)) {
    Serial.print("UP: ");
    Serial.println(adcReading);
    blinker(1000);
    for (int i = 0; i < FILTER_SAMPLING; i++)
      LowPassFilter(analogRead(adcPin), &newReading, &oldReading, &adcReading, BETA);
    motor.drive(FULL_SPEED, STARTUP_MOTOR_DELAY);  // <-- Change Motor Direction Here
  }

  /* --- Move Down --- */
  oldReading = analogRead(adcPin);
  while (int(adcReading) > (MIN_ADC_READING)) {
    Serial.print("DOWN: ");
    Serial.println(adcReading);
    blinker(1000);
    for (int i = 0; i < FILTER_SAMPLING; i++)
      LowPassFilter(analogRead(adcPin), &newReading, &oldReading, &adcReading, BETA);
    motor.drive(-FULL_SPEED, STARTUP_MOTOR_DELAY);  // <-- Change Motor Direction Here
  }
}

void trackAndControlPosition(uint8_t adcPin, uint8_t time) {
  /* --- (!!Integer is Good Enough) Use Linear Equation for Relation of Position and Hour --- */
  setPoint = map(time, MIN_HOUR, MAX_HOUR, MIN_ADC_READING, MAX_ADC_READING);
  for (int i = 0; i < FILTER_SAMPLING; i++)
    LowPassFilter(analogRead(adcPin), &newReading, &oldReading, &adcReading, BETA);
  adcReading = int(adcReading);
  error = adcReading - setPoint;

  if (error > 0)
    motor.drive(-FULL_SPEED, MOTOR_DELAY);
  else if (error < 0)
    motor.drive(FULL_SPEED, MOTOR_DELAY);
  else
    motor.brake();

  Serial.print(adcReading);
  Serial.print(",\t");
  Serial.print(setPoint);
  Serial.print(",\t");
  Serial.println(error);
}

int manualSetpoint = 9;
void manualPositionControl(uint8_t adcPin) {
  for (int i = 0; i < FILTER_SAMPLING; i++)
    LowPassFilter(analogRead(adcPin), &newReading, &oldReading, &adcReading, BETA);
  adcReading = int(adcReading);
  error = adcReading - manualSetpoint;

  if (error > 0)
    motor.drive(-FULL_SPEED, MOTOR_DELAY);
  else if (error < 0)
    motor.drive(FULL_SPEED, MOTOR_DELAY);
  else
    motor.brake();

  Serial.print(adcReading);
  Serial.print(",\t");
  Serial.print(manualSetpoint);
  Serial.print(",\t");
  Serial.println(error);
}
