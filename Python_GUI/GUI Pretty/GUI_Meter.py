import ttkbootstrap as ttk
import matplotlib
from tkinter import*
from ttkbootstrap.constants import*
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg,NavigationToolbar2Tk)

window = Tk()
window.geometry("1920x1080")
window.title("Water Quality Monitoring")

# --> Select Data
ttk.Label(window,text="Select Data:"
    	  ,foreground="#0080ff"
          ,font=("Times New Roman bold",15)).place(x=1450,y=50)

# --> Select Box
data = StringVar()
dataSelect = ttk.Combobox(window,width=30,textvariable=data)

# --> Create type of Data
dataSelect['value'] = ( "Temperature"
                       ,"Oxygen"
                       ,"Turbidity"
                       ,"pH")
dataSelect.place(x = 1600, y = 50)
dataSelect.current(0)

#-----------------------------------------> Show Logo <-----------------------------------------#
# --> Title " Water Quality Monitoring "
tille_monitor = Label(  window,text = " Water Quality Monitoring "
                        ,foreground="Green"
                        ,font=("Times New Roman bold italic",25)) 
tille_monitor.place(x = 755, y = 10)

# --> NPIC Logo
npic_logo = Canvas(window, width=100, height=100)
npic_logo.place(x=10, y=10)
NPIC_logo = PhotoImage(file="NPIC.png")
npic_logo.create_image(False, False, anchor=NW, image=NPIC_logo)
title_npic_Khmer = Label(   window,text="វិទ្យាស្ថានជាតិពហុបច្ចេកទេសកម្ពុជា"
                            ,foreground="Blue"
                            ,font=("Khmer OS Muol Light", 11))
title_npic_Khmer.place(x=115, y=28)
title_npic_English = Label( window,text="National Polytechnic Institute of Cambodia"
                            ,foreground="#1B105E",font=("Times New Roman", 12))
title_npic_English.place(x=108, y=68)

#-----------------------------------------> Show Data <-----------------------------------------#
# --> Temperature
temCircle = ttk.Meter(window
                        ,amounttotal =100 # --> Maximum Value
                        ,amountused = 20 # --> access data 
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

#-----------------------------------------> Show Graph<-----------------------------------------#
matplotlib.use('TKAgg')
class App(Tk):
    def __init__(self):
        super().__init__()
        temData = { "High Quality":9.5,
                    "Good Quality":8.00,
                    "Moderate Quality":6.5,
                    "Poor Quality":4.5,
                    "Very Poor Guality":0
                }
        languages = temData.keys()
        popularity = temData.values()

        figure = Figure(figsize=(8,4),dpi=50)
        figure_canvas = FigureCanvasTkAgg(figure,self)
        NavigationToolbar2Tk(figure_canvas,self)
        axes = figure.add_subplot()
        axes.bar(languages, popularity)
        axes.set_title('Quality')
        axes.set_ylabel('Popularity')
        figure_canvas.get_tk_widget().pack()


#-----------------------------------------> <-----------------------------------------#
App()
window.mainloop()