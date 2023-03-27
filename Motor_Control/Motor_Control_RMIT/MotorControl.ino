#include "Parameter.h"
void Motor(void) {
  pinMode(AIN_1, OUTPUT);
  pinMode(AIN_2, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(BIN_1, OUTPUT);
  pinMode(BIN_2, OUTPUT);
  pinMode(PWM_B, OUTPUT);
}
void runMotor(int8_t Direction, uint8_t duty) {
  if (Direction == 1) {        /*---------- Forward ------------*/
    forward(motor_A, motor_B, duty);
  } else if (Direction == -1) {/*---------- Forward ------------*/
    back(motor_A, motor_B, duty);
  } else {                     /*------------ Stop ------------*/
    brake(motor_A, motor_B);
  }
}
