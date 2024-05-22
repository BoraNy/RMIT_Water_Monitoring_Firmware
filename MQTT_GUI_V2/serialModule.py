import serial
import serial.tools.list_ports


class SerialCommunication:
    def __init__(self, baudrate) -> None:
        self.hardwarePort = ''
        self.ports = serial.tools.list_ports.comports()
        for port in self.ports:
            if 'Arduino Uno (COM11)' in port.description:  # USB-SERIAL CH340
                self.hardwarePort = port.device
        self.hardwareSerial = serial.Serial(self.hardwarePort, baudrate)

    def read(self):
        data = str(self.hardwareSerial.readline())
        data = data.replace('\\r\\n', '')
        data = data.replace('\\r', '')
        data = data.replace('b', '')
        data = data.replace('\'', '')
        return data.split(',')


if __name__ == '__main__':
    arduinoSerial = SerialCommunication(115200)

    while True:
        print(arduinoSerial.read())
