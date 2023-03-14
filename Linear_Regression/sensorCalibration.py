from serialModule import SerialCommunication

def logDataToFile(pH, dissolvedOxygen, fileName):
        with open(f'./{fileName}.csv', 'a+') as logFile:
            logFile.write(f'{pH},{dissolvedOxygen}\n')
            logFile.close()

if __name__ == '__main__':
    controller = SerialCommunication(115200)
    i = 1
    while i <= 500:
        try:
            data = controller.read()
            pH = float(data[0])
            dissolvedOxygen = float(data[1])
            print(i, data)
            logDataToFile(pH, dissolvedOxygen, 'phOnly')
            i = i + 1
        except:
             pass
    