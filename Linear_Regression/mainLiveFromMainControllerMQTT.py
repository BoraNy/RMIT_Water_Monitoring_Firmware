import os
import matplotlib.pyplot as plt
from drawnow import*
from random import uniform
from datetime import datetime
from time import strftime
from paho.mqtt import client as mqtt_client
import json
import random
from datetime import datetime
import pandas
import numpy as np
from sklearn import model_selection
from sklearn.linear_model import LogisticRegression
import pickle

pH, dissolvedOxygen, Temperature, TDS = 0, 0, 0, 0


class LiveDataMonitoring:
    def __init__(self) -> None:
        self.counter = 0
        self.temperature, self.predictedTempearture = [], []
        self.pH, self.predictedpH = [], []
        self.TDS, self.predictedTDS = [], []
        self.dissolvedOxygen, self.predictedDissolvedOxygen = [], []

        # For Detect Missing Log File
        files = os.listdir('./')
        if 'monitoring_data_logging.csv' not in files:
            logFile = open('monitoring_data_logging.csv', 'w')
            logFile.write('Time,Temperature,pH,TDS,DissolvedOxygen\n')
            logFile.close()

        # For Live Matplotlib
        plt.ion()

    def logDataToFile(self, fileName):
        with open(f'./{fileName}.csv', 'a+') as logFile:
            logFile.write(
                f'{datetime.now()},{self.temperature[len(self.temperature)-1]:.2f},{self.pH[len(self.pH)-1]:.2f},{self.TDS[len(self.TDS)-1]:.2f},{self.dissolvedOxygen[len(self.dissolvedOxygen)-1]:.2f}\n')
            logFile.close()

    def createFigure(self):
        plt.subplot(221)
        plt.plot(self.temperature,
                 label=f'Temperature = {self.temperature[len(self.temperature)-1]:.2f}°C')
        plt.ylim(0, 50)
        plt.legend(loc='upper left')

        plt.subplot(222)
        plt.plot(self.pH, label=f'pH = {self.pH[len(self.pH)-1]:.2f}')
        plt.ylim(0, 14)
        plt.legend(loc='upper left')

        plt.subplot(223)
        plt.plot(self.TDS,
                 label=f'TDS = {self.TDS[len(self.TDS)-1]:.2f}ppm')
        plt.ylim(0, 1000)
        plt.legend(loc='upper left')

        plt.subplot(224)
        plt.plot(self.dissolvedOxygen,
                 label=f'Dissolved Oxygen = {self.dissolvedOxygen[len(self.dissolvedOxygen)-1]:.2f}mg/L')
        plt.ylim(0, 30)
        plt.legend(loc='upper left')
        plt4 = plt.twinx()
        plt4.plot(self.predictedDissolvedOxygen, 'g:',
                  label=f'Predicted = {self.predictedDissolvedOxygen[len(self.predictedDissolvedOxygen)-1]:.2f}mg/L')
        plt.ylim(0, 30)
        plt4.legend(loc='lower left')

    def visualize(self, temperature, pH, TDS, dissolvedOxygen, predictedDissolvedOxygen):
        # Get Raw Data Update
        self.temperature.append(temperature)
        self.pH.append(pH)
        self.TDS.append(TDS)
        self.dissolvedOxygen.append(dissolvedOxygen)
        self.predictedDissolvedOxygen.append(predictedDissolvedOxygen)

        drawnow(self.createFigure)
        plt.pause(1e-6)
        self.counter += 1
        if self.counter > 60:
            self.temperature.pop(0)
            self.pH.pop(0)
            self.TDS.pop(0)
            self.dissolvedOxygen.pop(0)
            self.predictedDissolvedOxygen.pop(0)


#---> Read Data over MQTT -----------#
broker = "broker.hivemq.com"
port = 1883
topic = "Message"
client_ID = f'python-mqtt-{random.randint(0, 100)}'
username = "NPIC_MQTT"
password = "NPIC_RMIT_Project"

#----------------------- Check Connection --------------------#


def MQTT_Connection() -> mqtt_client:
    def on_connection(client, userdata, flags, rc):
        if rc == 0:
            print("Successfully Connected to MQTT Broker!")
        else:
            print("Fialed to Connect to MQTT Broker")
    client = mqtt_client.Client(client_ID)
    client.username_pw_set(username, password)
    client.on_connect = on_connection
    client.connect(broker, port)
    return client

#----------------------- Check Subscribe --------------------#


def subscribe(client: mqtt_client):
    def on_message(client, userdata, message):
        global TDS, pH, dissolvedOxygen, Temperature
        global pHInfoState, DOInfoState, TDSInfoState, TemperatureInfoState
        #---------------- Print Data from Json ---------------------#
        try:
            data = json.loads(message.payload.decode())
            Temperature = str(data["notification"]["parameters"]["Temperature"])
            TDS = str(data["notification"]["parameters"]["TDS"])
            pH = str(data["notification"]["parameters"]["pH"])
            dissolvedOxygen = str(data["notification"]["parameters"]["Oxygen"])
        except:
            pass

    client.subscribe(topic)
    client.on_message = on_message


filename = 'water_quality_model.pkl'
if __name__ == '__main__':
    live = LiveDataMonitoring()
    client = MQTT_Connection()
    subscribe(client)
    client.loop_start()
    AIModel = pickle.load(open(filename, 'rb'))

    while True:
        # print(Temperature, pH, TDS, dissolvedOxygen)
        X_data = np.array([[Temperature, pH, TDS]], dtype=np.float64)
        predictedDissolvedOxygen = AIModel.predict(X_data)
        live.visualize(float(Temperature), float(pH), float(TDS), float(
            dissolvedOxygen), float(predictedDissolvedOxygen))
        live.logDataToFile('realtime_data_logging')
        # client.loop_stop()
