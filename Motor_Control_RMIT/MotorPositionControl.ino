#define QUATER_SPEED int(255 / 4)
#define HALF_SPEED int(255 / 2)
#define FULL_SPEED 255
#define STARTUP_MOTOR_DELAY 500
#define MOTOR_DELAY 1000

float oldReading = 0;
float newReading = 0;
const float BETA = 0.9;

const int MAX_ADC_READING = -1,
          MIN_ADC_READING = -1;
const int MAX_HOUR = -1,
          MIN_HOUR = -1;
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
  LowPassFilter(analogRead(adcPin), &newReading, &oldReading, &adcReading, BETA);
  while (adcReading <= (MAX_ADC_READING - 10)) {
    LowPassFilter(analogRead(adcPin), &newReading, &oldReading, &adcReading, BETA);
    motor.drive(HALF_SPEED, STARTUP_MOTOR_DELAY);  // <-- Change Motor Direction Here
  }

  /* --- Move Down --- */
  LowPassFilter(analogRead(adcPin), &newReading, &oldReading, &adcReading, BETA);
  while (adcReading >= (MIN_ADC_READING + 10)) {
    LowPassFilter(analogRead(adcPin), &newReading, &oldReading, &adcReading, BETA);
    motor.drive(-HALF_SPEED, STARTUP_MOTOR_DELAY);  // <-- Change Motor Direction Here
  }
}

void trackAndControlPosition(uint8_t adcPin, uint8_t time) {
  /* --- (!!Integer is Good Enough) Use Linear Equation for Relation of Position and Hour --- */
  setPoint = map(time, MIN_HOUR, MAX_HOUR, MIN_ADC_READING, MAX_ADC_READING);
  for (int i = 0; i < 5; i++)
    LowPassFilter(analogRead(adcPin), &newReading, &oldReading, &adcReading, BETA);
  error = long(adcReading) - setPoint;

  if (error > 0)
    motor.drive(-HALF_SPEED, MOTOR_DELAY);  // <-- Change Motor Direction Here
  else
    motor.drive(HALF_SPEED, MOTOR_DELAY);  // <-- Change Motor Direction Here
}

static long manualSetpoint = MIN_HOUR;
void manualPositionControl(uint8_t adcPin) {
  if (Serial.available() > 0) {
    manualSetpoint = Serial.parseInt();

    if (manualSetpoint > MAX_HOUR) manualSetpoint = MAX_HOUR;
    if (manualSetpoint < MIN_HOUR) manualSetpoint = MIN_HOUR;
  }

  for (int i = 0; i < 5; i++)
    LowPassFilter(analogRead(adcPin), &newReading, &oldReading, &adcReading, BETA);
  error = long(adcReading) - manualSetpoint;

  if (error > 0)
    motor.drive(-HALF_SPEED, MOTOR_DELAY);
  else
    motor.drive(HALF_SPEED, MOTOR_DELAY);
}