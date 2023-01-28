import ttkbootstrap as ttk
from serialModule import SerialCommunication
from tkinter import *
from ttkbootstrap.constants import *
from time import strftime

pH, dissolvedOxygen, Temperature, Turbidity = 0, 0, 0, 0

window = Tk()
window.geometry("1920x1080")
window.title("Water Quality Monitoring")

# -----------------------------------------> Show Logo <-----------------------------------------#
# --> Title " Water Quality Monitoring "
tille_monitor = Label(window, text=" Water Quality Monitoring ",
                      foreground="Green", font=("Arial bold", 25))
tille_monitor.place(x=830, y=68)

# --> Time


def time():
    string = strftime('%A %x\n%H:%M:%S %p')
    label.config(text="" + string.upper())
    label.after(1000, time)


label = Label(window, font=("Arial", 18), foreground="black")
label.place(x=1550, y=75)


# --- Label for Hazard
pHInfoState = ''


def pHInfo():
    label1.config(text="PH State:\t\t\t" + pHInfoState)
    label1.after(1000, pHInfo)


label1 = Label(window, font=("Arial", 18), foreground="black")
label1.place(x=850, y=180)

DOInfoState = ''


def DOInfo():
    label2.config(text="Dissolved Oxygen State:\t" + DOInfoState)
    label2.after(1000, DOInfo)


label2 = Label(window, font=("Arial", 18), foreground="black")
label2.place(x=850, y=230)

TurbidityInfoState = ''


def TurbidityInfo():
    label3.config(text="Turbidity State:\t\t" + TurbidityInfoState)
    label3.after(1000, TurbidityInfo)


label3 = Label(window, font=("Arial", 18), foreground="black")
label3.place(x=850, y=280)

TemperatureInfoState = ''


def TemperatureInfo():
    label4.config(text="Temperature State:\t\t" + TemperatureInfoState)
    label4.after(1000, TemperatureInfo)


label4 = Label(window, font=("Arial", 18), foreground="black")
label4.place(x=850, y=330)

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
temCircle.place(x=50, y=200)

# --> Turbidity
turCircle = ttk.Meter(window, amounttotal=3000  # --> Maximum Value
                      , amountused=Turbidity  # --> access data
                      , metersize=250   # --> Radius of Circle
                      , meterthickness=20  # --> Width of Circle
                      , bootstyle=PRIMARY, interactive=False, textfont=["Arial", 26, 'bold'], textright="NTU", subtext="Turbidity", subtextfont=["Arial", 15, "bold"])
turCircle.place(x=400, y=200)

# --> Potential of Hydrogen
phCircle = ttk.Meter(window, amounttotal=14  # --> Maximum Value
                     , amountused=pH  # --> access data
                     , metersize=250   # --> Radius of Circle
                     , meterthickness=20  # --> Width of Circle
                     , bootstyle=PRIMARY, interactive=False, textfont=["Arial", 26, 'bold'], textright="PH", subtext="pH", subtextfont=["Arial", 15, "bold"])
phCircle.place(x=50, y=550)

# --> Oxygen
oxygenCircle = ttk.Meter(window, amounttotal=20  # --> Maximum Value for sensor is 20mg/L
                         , amountused=dissolvedOxygen  # --> access data
                         , metersize=250   # --> Radius of Circle
                         , meterthickness=20  # --> Width of Circle
                         , bootstyle=PRIMARY, interactive=False, textfont=["Arial", 26, 'bold'], textright="mg/l", subtext="Oxygen", subtextfont=["Arial", 15, "bold"])
oxygenCircle.place(x=400, y=550)

# --> Read Serial


arduino = SerialCommunication(115200)
# -----------------------------------------> <-----------------------------------------#


def readArduinoSerial():
    global Turbidity, pH, dissolvedOxygen, Temperature
    global pHInfoState, DOInfoState, TurbidityInfoState, TemperatureInfoState

    try:
        data = arduino.read()
        Turbidity = float(data[0])
        pH = float(data[1])
        DO = float(data[2])
        Temperature = float(data[3])

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
            DOInfoState = 'DEADLY'
        elif (dissolvedOxygen > 4) and (dissolvedOxygen <= 6.5):
            DOInfoState = 'POOR'
        elif (dissolvedOxygen > 6.5) and (dissolvedOxygen <= 9.5):
            DOInfoState = 'GOOD'
        elif (dissolvedOxygen > 4):
            DOInfoState = 'EXCELLENT'

        if (Turbidity >= 0) and (Turbidity <= 500):
            TurbidityInfoState = 'LOW'
        elif (Turbidity > 500) and (Turbidity <= 1000):
            TurbidityInfoState = 'MEDIUM'
        elif (Turbidity > 1000):
            TurbidityInfoState = 'HIGH'

        TemperatureInfoState = 'NORMAL'

        # Assign Value to Dashboard
        temCircle.configure(amountused=Temperature)
        turCircle.configure(amountused=Turbidity)
        phCircle.configure(amountused=pH)
        oxygenCircle.configure(amountused=dissolvedOxygen)

        print(Turbidity, pH, dissolvedOxygen, Temperature)
    except:
        pass

    window.after(1000, readArduinoSerial)


if __name__ == '__main__':
    time()
    pHInfo()
    DOInfo()
    TurbidityInfo()
    TemperatureInfo()
    window.after(1000, readArduinoSerial)
    window.mainloop()
