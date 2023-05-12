#ifndef __KALMAN_FILTER_H
#define __KALMAN_FILTER_H

class KalmanFilter {
private:
  float Qd = 0, R = 0;
  float Ak = 1,
        Bk = 0,
        Ck = 1,
        Dk = 0;
  float x = 0,
        P = 0,
        uk = 0,
        W = 0;
public:
  void init(float Qd, float R) {
    this->Qd = Qd;
    this->R = R;
  }

  float filter(float input) {
    // Compute Kalman Gain
    float W = P * Ck / (Ck * P * Ck + R);

    // Update Predicted Value by Observation
    x = x + W * (input - Ck * x - Dk * uk);

    // Time Update
    x = Ak * x + Bk * uk;

    // Update Error Covariance Matrices
    P = P - W * Ck * P;
    P = Ak * P * Ak + Qd;
    return x;
  }
};

#endif