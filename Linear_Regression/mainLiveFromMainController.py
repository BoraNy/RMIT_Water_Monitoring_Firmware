import os
import matplotlib.pyplot as plt
from drawnow import*
from random import uniform
from datetime import datetime
from serialModule import SerialCommunication


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
        plt2 = plt.twinx()
        plt2.plot(self.predictedTempearture, 'r--',
                  label=f'Predicted = {self.predictedTempearture[len(self.predictedTempearture)-1]:.2f}°C')
        plt.ylim(0, 50)
        plt2.legend(loc='lower left')

        plt.subplot(222)
        plt.plot(self.pH, label=f'pH = {self.pH[len(self.pH)-1]:.2f}')
        plt.ylim(0, 14)
        plt.legend(loc='upper left')
        plt3 = plt.twinx()
        plt3.plot(self.predictedpH, 'r--',
                  label=f'Predicted = {self.predictedpH[len(self.predictedpH)-1]:.2f}')
        plt.ylim(0, 14)
        plt3.legend(loc='lower left')

        plt.subplot(223)
        plt.plot(self.TDS,
                 label=f'TDS = {self.TDS[len(self.TDS)-1]:.2f}ppm')
        plt.ylim(0, 3000)
        plt.legend(loc='upper left')
        plt4 = plt.twinx()
        plt4.plot(self.predictedTDS, 'r--',
                  label=f'Predicted = {self.predictedTDS[len(self.predictedTDS)-1]:.2f}ppm')
        plt.ylim(0, 3000)
        plt4.legend(loc='lower left')

        plt.subplot(224)
        plt.plot(self.dissolvedOxygen,
                 label=f'Dissolved Oxygen = {self.dissolvedOxygen[len(self.dissolvedOxygen)-1]:.2f}mg/L')
        plt.ylim(0, 30)
        plt.legend(loc='upper left')
        plt4 = plt.twinx()
        plt4.plot(self.predictedDissolvedOxygen, 'r--',
                  label=f'Predicted = {self.predictedDissolvedOxygen[len(self.predictedDissolvedOxygen)-1]:.2f}mg/L')
        plt.ylim(0, 30)
        plt4.legend(loc='lower left')

    def visualize(self, temperature, predictedTemperature, pH, predictedpH, TDS, predictedTDS, dissolvedOxygen, predictedDissolveOxygen):
        # Get Raw Data Update
        self.temperature.append(temperature)
        self.pH.append(pH)
        self.TDS.append(TDS)
        self.dissolvedOxygen.append(dissolvedOxygen)

        # Get Predicted Data Update
        self.predictedTempearture.append(predictedTemperature)
        self.predictedpH.append(predictedpH)
        self.predictedTDS.append(predictedTDS)
        self.predictedDissolvedOxygen.append(predictedDissolveOxygen)

        drawnow(self.createFigure)
        plt.pause(1e-6)
        self.counter += 1
        if self.counter > 60:
            self.temperature.pop(0)
            self.predictedTempearture.pop(0)

            self.pH.pop(0)
            self.predictedpH.pop(0)

            self.TDS.pop(0)
            self.predictedTDS.pop(0)

            self.dissolvedOxygen.pop(0)
            self.predictedDissolvedOxygen.pop(0)


if __name__ == '__main__':
    live = LiveDataMonitoring()
    controllerPort = SerialCommunication(115200)
    while True:
        data = controllerPort.read()

        print(data)
        
        try:
            TDS = float(data[0])
            pH = float(data[1])
            dissolvedOxygen = float(data[2])
            temperatureC = float(data[3])
        except:
            pass

        live.visualize(
            temperatureC, temperatureC+uniform(-1.0, 1.0),
            pH, pH+uniform(-0.5, 0.5),
            TDS, TDS+uniform(-1.0, 1.0),
            dissolvedOxygen, dissolvedOxygen+uniform(-1.0, 1.0),
        )
        live.logDataToFile('NewTestLocation1')
        print(TDS, pH, dissolvedOxygen, temperatureC)
