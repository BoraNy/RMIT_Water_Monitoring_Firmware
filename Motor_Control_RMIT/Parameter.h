#ifndef _PARAMETER_H
#define _PARAMETER_H

#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_TB6612.h>
#include <RTClib.h>
#define LED 8
#define GLOBLE_BAUDRATE 115200 /*------------- Buadrate-----------*/

/*----------------- Motor Arduino Pin ---------------------------*/
#define STBY 9
/*----------- ChannelA Pin ----------------*/
#define PWM_A 10
#define AIN_1 12
#define AIN_2 11
const int8_t offsetA = 1;
Motor motor_A = Motor(AIN_1, AIN_2, PWM_A, offsetA, STBY); /*--------------- MotorA -----------------*/
/*----------- ChannelB Pin ----------------*/
#define PWM_B 7
#define BIN_1 6
#define BIN_2 5
const int8_t offsetB = 1;
Motor motor_B = Motor(BIN_1, BIN_2, PWM_B, offsetB, STBY); /*--------------- MotorB -----------------*/
/*----------- Setmotor Speed ----------------*/
const uint8_t MotorSpeed = 0;

RTC_DS1307 RTC; /*--------------- RealtimeClock -----------------*/

unsigned long delayTime = 0;
uint8_t second, minute, hour, day, month, year = 0;

/* --- Sensor --- */
#define POT_ADC_PIN 0

#endif