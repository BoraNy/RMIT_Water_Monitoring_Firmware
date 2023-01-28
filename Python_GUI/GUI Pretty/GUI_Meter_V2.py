import ttkbootstrap as ttk
from serialModule import SerialCommunication
from tkinter import *
from ttkbootstrap.constants import *
from time import strftime

pH, DO, Temperature, Turbidity = 0, 0, 0, 0

window = Tk()
window.geometry("1920x1080")
window.title("Water Quality Monitoring")

# -----------------------------------------> Show Logo <-----------------------------------------#
# --> Title " Water Quality Monitoring "
tille_monitor = Label(window, text=" Water Quality Monitoring ",
                      foreground="Green", font=("Times New Roman bold italic", 25))
tille_monitor.place(x=755, y=10)

# --> Time 
def time():
    string = strftime('%A %x\n%H:%M:%S %p')
    label.config(text="" + string)
    label.after(1000, time)
label = Label(window,font=("Times New Roman", 18),foreground="black")
label.place(x=1400, y=110)

# --> NPIC Logo
npic_logo = Canvas(window, width=100, height=100)
npic_logo.place(x=10, y=10)
NPIC_logo = PhotoImage(file="NPIC.png")
npic_logo.create_image(False, False, anchor=NW, image=NPIC_logo)
title_npic_Khmer = Label(window, text="វិទ្យាស្ថានជាតិពហុបច្ចេកទេសកម្ពុជា",
                         foreground="Blue", font=("Khmer OS Muol Light", 11))
title_npic_Khmer.place(x=115, y=28)
title_npic_English = Label(
    window, text="National Polytechnic Institute of Cambodia", foreground="#1B105E", font=("Times New Roman", 12))
title_npic_English.place(x=108, y=68)

# -----------------------------------------> Show Data <-----------------------------------------#
# --> Temperature
temCircle = ttk.Meter(window, amounttotal=150  # --> Maximum Value
                      , amountused=Temperature  # --> access data
                      , metersize=250   # --> Radius of Circle
                      , meterthickness=20  # --> Width of Circle
                      , bootstyle=SUCCESS, interactive=False, textfont=["Times New Roman", 26, 'bold'], textright="°C", subtext="Temperature", subtextfont=["Times New Roman", 15, "bold"])
temCircle.place(x=50, y=200)

# --> Turbidity
turCircle = ttk.Meter(window, amounttotal=50000  # --> Maximum Value
                      , amountused=Turbidity  # --> access data
                      , metersize=250   # --> Radius of Circle
                      , meterthickness=20  # --> Width of Circle
                      , bootstyle=PRIMARY, interactive=False, textfont=["Times New Roman", 26, 'bold'], textright="NTU", subtext="Turbidity", subtextfont=["Times New Roman", 15, "bold"])
turCircle.place(x=400, y=200)

# --> Potential of Hydrogen
phCircle = ttk.Meter(window, amounttotal=14  # --> Maximum Value
                     , amountused=pH  # --> access data
                     , metersize=250   # --> Radius of Circle
                     , meterthickness=20  # --> Width of Circle
                     , bootstyle=DANGER, interactive=False, textfont=["Times New Roman", 26, 'bold'], textright="PH", subtext="pH", subtextfont=["Times New Roman", 15, "bold"])
phCircle.place(x=50, y=550)

# --> Oxygen
oxygenCircle = ttk.Meter(window, amounttotal=3000  # --> Maximum Value
                         , amountused=DO  # --> access data
                         , metersize=250   # --> Radius of Circle
                         , meterthickness=20  # --> Width of Circle
                         , bootstyle=INFO, interactive=False, textfont=["Times New Roman", 26, 'bold'], textright="mg/l", subtext="Oxygen", subtextfont=["Times New Roman", 15, "bold"])
oxygenCircle.place(x=400, y=550)

# --> Read Serial



arduino = SerialCommunication(115200)
# -----------------------------------------> <-----------------------------------------#


def readArduinoSerial():
    global Turbidity, pH, DO, Temperature
    
    try:
        data = arduino.read()
        Turbidity = float(data[0])
        pH = float(data[1])
        DO = float(data[2])
        Temperature = float(data[3])

        temCircle.configure(amountused=Temperature)
        turCircle.configure(amountused=Turbidity)
        phCircle.configure(amountused=pH)
        oxygenCircle.configure(amountused=DO)

        print(Turbidity, pH, DO, Temperature)
    except:
        pass

    window.after(1000, readArduinoSerial)

if __name__ == '__main__':
    time()
    window.after(1000, readArduinoSerial)
    window.mainloop()
