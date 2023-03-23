#include "Wire.h"
#ifndef _PARAMETER_H
#define _PARAMETER_H

#include <Arduino.h>
#include "FS.h"
#include <WiFi.h>
#include <RTClib.h>
#include <SPI.h>
#include <SD.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

/*---------------- Serial Communication -------------------*/
#define GLOBAL_BAUDRATE 115200
#define TX_ 22
#define RX_ 19
#define SD_Card_SS 4

#define SDA_1 27
#define SCL_1 26
TwoWire I2Cone = TwoWire(0);

/*---------------- Init Sensor -------------------*/
RTC_DS1307 rtc;  /*--------------- RealtimeClock ---------------*/
File dataBackup; /*--------------- SD-Card ---------------------*/
uint8_t second, minute, hour, day, month, year = 0;

/*---------------- Serial Read Paramater-------------------*/
String TDS;
String pH;
String Oxigen;
String Temperature;
String messageStr = "";

/*---------------- MQTT Credentials ------------------*/
const char* ssid = "Astro-X";                   /*---------- Wifi SSID ------------*/
const char* password = "Heang187";              /*---------- Wifi Password -------------*/
const char* mqttServer = "broker.hivemq.com";   /*---------- MQTT Broker --------------*/
const char* mqttUserName = "NPIC_MQTT";         /*---------- MQTT Username--------------*/
const char* mqttPassword = "NPIC_RMIT_Project"; /*---------- MQTT Password--------------*/
const char* clientID = "NPIC_ID_1";             /*---------- Client ID--------------*/
const char* topic = "Message";                  /*---------- Topic of Data --------------*/

#endif