from serialModule import SerialCommunication

arduinoSerial = SerialCommunication(115200)

while True:
    print(arduinoSerial.read())
