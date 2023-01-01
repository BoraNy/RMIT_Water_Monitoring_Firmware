#include "cryptography.h"

float reading = 0;

float2int_S PH;

void setup()
{
  Serial.begin(115200);
  Serial.println("Initialization");
}

void loop()
{
  reading = analogRead(0) + (rand() % 1000) * 1e-3;

  PH.float2int(reading, FOUR_DIGIT_PRECISION);

  sprintf(dataBuffer, "PH: %d.%d",
          PH.wholeNumber, PH.fractional);

  aes128_enc_single(key, dataBuffer);
  Serial.println(dataBuffer);

  aes128_dec_single(key, dataBuffer);
  Serial.println(dataBuffer);
  Serial.println();

  delay(1000);
}
