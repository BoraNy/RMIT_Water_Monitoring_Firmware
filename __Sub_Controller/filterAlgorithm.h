void LowPassFilter(float noisySignal, float *newReading, float *oldReading,
                                        float *filteredSignal, const float beta)
{
  *newReading = beta * noisySignal + (1 - beta) * (*oldReading);
  *oldReading = *newReading;
  *filteredSignal = *newReading;
}
