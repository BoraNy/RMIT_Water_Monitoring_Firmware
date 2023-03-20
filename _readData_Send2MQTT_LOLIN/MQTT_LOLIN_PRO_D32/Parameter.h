#ifndef _PARAMETER_H
#define _PARAMETER_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#define GLOBAL_BAUDRATE 115200
#define SERIAL_FROM_SUB_TX 27
#define SERIAL_FROM_SUB_RX 26
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