import serial
import serial.tools.list_ports

class SerialCommunication:
    def __init__(self, baudrate) -> None:
        self.hardwarePort = ''
        self.ports = serial.tools.list_ports.comports()
        for port in self.ports:
            if 'Arduino' in port.description:
                self.hardwarePort = port.device
            if 'CH340' in port.description:
                self.hardwarePort = port.device
                
        self.hardwareSerial = serial.Serial(self.hardwarePort, baudrate, timeout=1000)
    
    def read(self):
        data = str(self.hardwareSerial.readline())
        data = data.replace('\\r\\n', '')
        data = data.replace('b', '')
        data = data.replace('\'', '')
        return data.split(',')

if __name__ == '__main__':
    arduinoSerial = SerialCommunication(115200)
    
    while True:
        print(arduinoSerial.read())
        