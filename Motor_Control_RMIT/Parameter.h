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
Motor motor = Motor(AIN_1, AIN_2, PWM_A, offsetA, STBY); 

/*--------------- RealtimeClock -----------------*/
RTC_DS1307 RTC; 
unsigned long delayTime = 0;
uint8_t second, minute, hour, day, month, year = 0;

/* --- Sensor --- */
#define POT_ADC_PIN 0

#endif