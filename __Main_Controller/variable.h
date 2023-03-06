#ifndef __VARIABLE_H
#define __VARIABLE_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

/*--- Define Paramater ---*/
uint32_t delayMS = 0;
float Temperature, Turbidity, pH, Oxigen = 0;
unsigned long previousMillis = 0;
const long interval = 5000;                       /* --- 5 seconds --- */
String messageStr = "";

/* --- MQTT Credentials --- */
const char *ssid = "Linksys01430";                /* --- Wifi SSID ------- */
const char *password = "ecw11wce";                /* --- Wifi Password --- */
const char *mqttServer = "broker.hivemq.com";     /* --- MQTT Broker ----- */
const char *mqttUserName = "NPIC_MQTT";           /* --- MQTT Username --- */
const char *mqttPassword = "NPIC_RMIT_Project";   /* --- MQTT Password --- */
const char *clientID = "NPIC_ID_1";               /* --- Client ID ------- */
const char *topic = "Message";                    /* --- Topic of Data --- */

#endif