import ttkbootstrap as ttk
from serialModule import SerialCommunication
from tkinter import *
from ttkbootstrap.constants import *
from time import strftime
from paho.mqtt import client as mqtt_client
import json
import random
from datetime import datetime

pH, dissolvedOxygen, Temperature, TDS = 0, 0, 0, 0
data = ''
window = Tk()
window.geometry("1920x1080")
window.title("Water Quality Monitoring")

# -----------------------------------------> Show Logo <-----------------------------------------#
# --> Title " Water Quality Monitoring "
tille_monitor = Label(window, text=" Water Quality Monitoring ",
                      foreground="Green", font=("Arial bold", 25))
tille_monitor.place(x=830, y=75)

# --> Time


def time():
    string = strftime('%A %x\n%H:%M:%S %p')
    label.config(text="" + string.upper())
    label.after(1000, time)


label = Label(window, font=("Arial", 18), foreground="black")
label.place(x=1550, y=60)

# --- Label for Hazard
pHInfoState = ''


def pHInfo():
    label1.config(text="PH State:\t\t\t" + pHInfoState)
    label1.after(1000, pHInfo)


label1 = Label(window, font=("Arial", 18), foreground="black")
label1.place(x=950, y=180)

DOInfoState = ''


def DOInfo():
    label2.config(text="Dissolved Oxygen State:\t" + DOInfoState)
    label2.after(1000, DOInfo)


label2 = Label(window, font=("Arial", 18), foreground="black")
label2.place(x=950, y=230)

TDSInfoState = ''


def TDSInfo():
    label3.config(text="TDS State:\t\t" + TDSInfoState)
    label3.after(1000, TDSInfo)


label3 = Label(window, font=("Arial", 18), foreground="black")
label3.place(x=950, y=280)

TemperatureInfoState = ''


def TemperatureInfo():
    label4.config(text="Temperature State:\t\t" + TemperatureInfoState)
    label4.after(1000, TemperatureInfo)


label4 = Label(window, font=("Arial", 18), foreground="black")
label4.place(x=950, y=330)

# --> NPIC Logo
npic_logo = Canvas(window, width=100, height=100)
npic_logo.place(x=10, y=10)
NPIC_logo = PhotoImage(file="NPIC.png")
npic_logo.create_image(False, False, anchor=NW, image=NPIC_logo)
title_npic_Khmer = Label(window, text="វិទ្យាស្ថានជាតិពហុបច្ចេកទេសកម្ពុជា",
                         foreground="Blue", font=("Khmer OS Muol Light", 14))
title_npic_Khmer.place(x=115, y=28)
title_npic_English = Label(
    window, text="National Polytechnic Institute of Cambodia", foreground="#1B105E", font=("Arial", 12))
title_npic_English.place(x=130, y=68)

# -----------------------------------------> Show Data <-----------------------------------------#
# --> Temperature
temCircle = ttk.Meter(window, amounttotal=150  # --> Maximum Value
                      , amountused=Temperature  # --> access data
                      , metersize=250   # --> Radius of Circle
                      , meterthickness=20  # --> Width of Circle
                      , bootstyle=PRIMARY, interactive=False, textfont=["Arial", 26, 'bold'], textright="°C", subtext="Temperature", subtextfont=["Arial", 15, "bold"])
temCircle.place(x=70, y=200)

# --> TDS
turCircle = ttk.Meter(window, amounttotal=1000  # --> Maximum Value
                      , amountused=TDS  # --> access data
                      , metersize=250   # --> Radius of Circle
                      , meterthickness=20  # --> Width of Circle
                      , bootstyle=PRIMARY, interactive=False, textfont=["Arial", 26, 'bold'], textright="ppm", subtext="TDS", subtextfont=["Arial", 15, "bold"])
turCircle.place(x=450, y=200)

# --> Potential of Hydrogen
phCircle = ttk.Meter(window, amounttotal=14  # --> Maximum Value
                     , amountused=pH  # --> access data
                     , metersize=250   # --> Radius of Circle
                     , meterthickness=20  # --> Width of Circle
                     , bootstyle=PRIMARY, interactive=False, textfont=["Arial", 26, 'bold'], textright="PH", subtext="pH", subtextfont=["Arial", 15, "bold"])
phCircle.place(x=70, y=550)

# --> Oxygen
oxygenCircle = ttk.Meter(window, amounttotal=20  # --> Maximum Value for sensor is 20mg/L
                         , amountused=dissolvedOxygen  # --> access data
                         , metersize=250   # --> Radius of Circle
                         , meterthickness=20  # --> Width of Circle
                         , bootstyle=PRIMARY, interactive=False, textfont=["Arial", 26, 'bold'], textright="mg/l", subtext="Oxygen", subtextfont=["Arial", 15, "bold"])
oxygenCircle.place(x=450, y=550)

# --> Quality Index
quality_logo = Canvas(window, width=800, height=100)
quality_logo.place(x=950, y=400)
Quality_logo = PhotoImage(file="Quality_Index.png")
quality_logo.create_image(False, False, anchor=NW, image=Quality_logo)

'''
# --> Read Serial
arduino = SerialCommunication(115200)
# -----------------------------------------> <-----------------------------------------#
def readArduinoSerial():
    global TDS, pH, dissolvedOxygen, Temperature
    global pHInfoState, DOInfoState, TDSInfoState, TemperatureInfoState

    try:
        data = arduino.read()
        TDS = float(data[0])/100
        pH = float(data[1])
        dissolvedOxygen = float(data[2])/1000
        Temperature = float(data[3])
'''
#---> Read Data over MQTT -----------#
broker = "broker.hivemq.com"
port = 1883
topic = "Message"
client_ID = f'python-mqtt-{random.randint(0, 100)}'
username = "NPIC_MQTT"
password = "NPIC_RMIT_Project"


def logDataToFile(fileName, temperature, ph, tds, dissolvedOxygen):
    with open(f'./{fileName}.csv', 'a+') as logFile:
        logFile.write(
            f'{datetime.now()},{temperature},{ph},{tds},{dissolvedOxygen}\n')
        logFile.close()

#----------------------- Check Connection --------------------#


def MQTT_Connection() -> mqtt_client:
    def on_connection(client, userdata, flags, rc):
        if rc == 0:
            print("Successfully Connected to MQTT Broker!")
        else:
            print("Fialed to Connect to MQTT Broker")
    client = mqtt_client.Client(mqtt_client.CallbackAPIVersion.VERSION1, client_ID)
    client.username_pw_set(username, password)
    client.on_connect = on_connection
    client.connect(broker, port)
    return client

#----------------------- Check Subscribe --------------------#


def subscribe(client: mqtt_client):
    def on_message(client, userdata, message):
        global data
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
        
        try:
            pH = float(pH)
            dissolvedOxygen = float(dissolvedOxygen)
            TDS = float(TDS)
            Temperature = float(Temperature)
            # --- Change Color Info Here
            if (pH >= 0) and (pH < 4):
                phCircle.configure(bootstyle=DANGER)
                pHInfoState = 'ACIDIC'
            elif (pH >= 4) and (pH < 6):
                phCircle.configure(bootstyle=WARNING)
                pHInfoState = 'ACIDIC'
            elif (pH >= 6) and (pH < 9):
                phCircle.configure(bootstyle=SUCCESS)
                pHInfoState = 'GOOD'
            elif (pH > 9):
                phCircle.configure(bootstyle=PRIMARY)
                pHInfoState = 'ALKALINE'

            if (dissolvedOxygen >= 0) and (dissolvedOxygen <= 4):
                oxygenCircle.configure(bootstyle=DANGER)
                DOInfoState = 'DEADLY'
            elif (dissolvedOxygen > 4) and (dissolvedOxygen <= 6.5):
                oxygenCircle.configure(bootstyle=WARNING)
                DOInfoState = 'POOR'
            elif (dissolvedOxygen > 6.5) and (dissolvedOxygen <= 9.5):
                oxygenCircle.configure(bootstyle=SUCCESS)
                DOInfoState = 'GOOD'
            elif (dissolvedOxygen > 9.5):
                oxygenCircle.configure(bootstyle=PRIMARY)
                DOInfoState = 'EXCELLENT'

            if (TDS >= 0) and (TDS <= 500):
                turCircle.configure(bootstyle=DANGER)
                TDSInfoState = 'LOW'
            elif (TDS > 500) and (TDS <= 1000):
                turCircle.configure(bootstyle=WARNING)
                TDSInfoState = 'MEDIUM'
            elif (TDS > 1000):
                turCircle.configure(bootstyle=PRIMARY)
                TDSInfoState = 'HIGH'

            if (Temperature >= 0) and (Temperature <= 10):
                temCircle.configure(bootstyle=DANGER)
                TemperatureInfoState = 'COLD'
            elif (Temperature > 10) and (Temperature <= 35):
                temCircle.configure(bootstyle=SUCCESS)
                TemperatureInfoState = 'NORMAL'
            elif (Temperature > 35):
                temCircle.configure(bootstyle=WARNING)
                TemperatureInfoState = 'WARNING'

            logDataToFile('NPIC_Pond_Data_for_AI', temperature=Temperature,
                          ph=pH, tds=TDS, dissolvedOxygen=dissolvedOxygen)
            print(TDS, pH, dissolvedOxygen, Temperature)
        except:
            pass

        # Assign Value to Dashboard
        temCircle.configure(amountused=Temperature)
        turCircle.configure(amountused=TDS)
        phCircle.configure(amountused=pH)
        oxygenCircle.configure(amountused=dissolvedOxygen)
    client.subscribe(topic)
    client.on_message = on_message
#    window.after(1000, readArduinoSerial)


if __name__ == '__main__':
    time()
    pHInfo()
    DOInfo()
    TDSInfo()
    TemperatureInfo()
    client = MQTT_Connection()
    subscribe(client)
    client.loop_start()
#    window.after(1000, readArduinoSerial)
    window.mainloop()
    client.loop_stop()
