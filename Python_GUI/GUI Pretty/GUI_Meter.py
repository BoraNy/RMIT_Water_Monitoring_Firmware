from tkinter import*
import ttkbootstrap as ttk
from ttkbootstrap.constants import*

window = Tk()
window.geometry("1920x1080")
window.title("Water Quality Monitoring")

# --> Title " Water Quality Monitoring "
tille_monitor = Label(window,text = " Water Quality Monitoring ",foreground="#1B105E", font=("Times New Roman bold italic",25)) 
tille_monitor.place(x = 755, y = 10)
# --> NPIC Logo
npic_logo = Canvas(window, width=100, height=100)
npic_logo.place(x=10, y=10)
NPIC_logo = PhotoImage(file="NPIC.png")
npic_logo.create_image(False, False, anchor=NW, image=NPIC_logo)
title_npic_Khmer = Label(window,text="វិទ្យាស្ថានជាតិពហុបច្ចេកទេសកម្ពុជា",foreground="#1B105E",font=("Khmer OS Muol Light", 11))
title_npic_Khmer.place(x=115, y=28)
title_npic_English = Label(window,text="National Polytechnic Institute of Cambodia",foreground="#1B105E",font=("Times New Roman", 12))
title_npic_English.place(x=108, y=68)

# --> Temperature
temCircle = ttk.Meter(window
                        ,amounttotal =100 # --> Maximum Value
                        ,amountused = 100 # --> access data 
                        ,metersize = 250   # --> Radius of Circle
                        ,meterthickness = 20  # --> Width of Circle
                        ,bootstyle = SUCCESS 
                        ,interactive = True
                        ,textfont = ["Times",26,'bold']
                        ,textright = "°C"
                        ,subtext = "Temperature"
                        ,subtextfont = ["Times",15,"bold"])
temCircle.place(x=50, y=200)

# --> Turbidity
turCircle = ttk.Meter(window
                        ,amounttotal =4000 # --> Maximum Value
                        ,amountused = 100 # --> access data  
                        ,metersize = 250   # --> Radius of Circle
                        ,meterthickness = 20  # --> Width of Circle
                        ,bootstyle = PRIMARY 
                        ,interactive = True
                        ,textfont=["Times",26,'bold']
                        ,textright = "NTU"
                        ,subtext = "Turbidity"
                        ,subtextfont =["Times",15,"bold"])
turCircle.place(x=370, y=200)

# --> Potential of Hydrogen
phCircle = ttk.Meter(window
                        ,amounttotal = 14 # --> Maximum Value
                        ,amountused = 3.7 # --> access data 
                        ,metersize = 250   # --> Radius of Circle
                        ,meterthickness = 20  # --> Width of Circle
                        ,bootstyle = DANGER 
                        ,interactive = True
                        ,textfont=["Times",26,'bold']
                        ,textright = "pHs"
                        ,subtext = "Potential of Hydrogen"
                        ,subtextfont =["Times",15,"bold"])
phCircle.place(x=50, y=520)

# --> Oxygen
oxygenCircle = ttk.Meter(window
                        ,amounttotal =16 # --> Maximum Value
                        ,amountused = 10 # --> access data 
                        ,metersize =250   # --> Radius of Circle
                        ,meterthickness = 20  # --> Width of Circle
                        ,bootstyle = INFO
                        ,interactive = True
                        ,textfont = ["Times",26,'bold']
                        ,textright = "mg/l"
                        ,subtext = "Oxygen"
                        ,subtextfont = ["Times",15,"bold"])
oxygenCircle.place(x=370, y=520)

window.mainloop()