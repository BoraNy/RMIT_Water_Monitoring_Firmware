#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <AESLib.h>

void aes128_enc_single(const uint8_t* key, void* data);
void aes128_dec_single(const uint8_t* key, void* data);

#define TWO_DIGIT_PRECISION 2
#define FOUR_DIGIT_PRECISION 4

char dataBuffer[16];
uint8_t key[] = {
  2, 62, 12, 52, 23, 84, 45, 84,
  92, 23, 52, 62, 12, 74, 47, 25
};

struct float2int_S {
  int wholeNumber, fractional;

  void float2int(float value, int precision) {
    wholeNumber = int(value);
    fractional = (value - int(value)) * pow(10, precision);
  }
};

#endif
