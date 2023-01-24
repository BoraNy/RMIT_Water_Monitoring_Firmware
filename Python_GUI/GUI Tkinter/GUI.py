from tkinter import*
from time import*

# --> GUI Design
window = Tk()
window.title("Water Quality Monitoring")
window.geometry("1920x1080")

# --> Real Time Clock
def realTime():
    time = strftime('%A %x\n%H:%M:%S %p')
    label.config(text = "" + time)
    label.after(1000, realTime)
label = Label(window,font = ("Times New Roman", 25), foreground = "Black")
label.place(x=1330, y=110)

# --> Include Logo

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

# --> Temperature Logo <-- #
temperatue_logo = Canvas(window,width = 65, height = 65)
temperatue_logo.place(x = 280, y = 200)
Temperature_logo = PhotoImage(file = "temperature.png")
temperatue_logo.create_image(False, False, anchor = NW, image = Temperature_logo)
temperatue_label = Label(window, text = "Temperature", foreground = "Black", font =("Times New Roman", 13))
temperatue_label.place(x = 248, y = 270 )
temperatue_data = Label(window, text = "---", foreground = "Black", font =("Times New Roman", 13))
temperatue_data.place(x = 550, y = 227 )

# --> Turbidity Logo <-- #
turbidity_logo = Canvas(window,width = 70, height = 70)
turbidity_logo.place(x = 280, y = 600)
Turbidity_logo = PhotoImage(file = "turbidity.png")
turbidity_logo.create_image(False, False, anchor = NW, image = Turbidity_logo)
turbidity_logo = Label(window, text = "Turbidity", foreground = "Black", font =("Times New Roman", 13))
turbidity_logo.place(x = 270, y = 675 )
turbidity_data = Label(window, text = "---", foreground = "Black", font =("Times New Roman", 13))
turbidity_data.place(x = 550, y = 630 )

# --> PH Logo <-- #
ph_logo = Canvas(window,width = 65, height = 65)
ph_logo.place(x = 1260, y = 200)
PH_logo = PhotoImage(file = "ph.png")
ph_logo.create_image(False, False, anchor = NW, image = PH_logo)
ph_label = Label(window, text = "Potential of Hydrogen", foreground = "Black", font =("Times New Roman", 13))
ph_label.place(x = 1200, y = 270 )
ph_data = Label(window, text = "---", foreground = "Black", font =("Times New Roman", 13))
ph_data.place(x = 1560, y = 227)

# --> Oxygen Logo <-- #
oxygen_logo = Canvas(window,width = 65, height = 65)
oxygen_logo.place(x = 1260, y = 600)
Oxygen_logo = PhotoImage(file = "oxygen.png")
oxygen_logo.create_image(False, False, anchor = NW, image = Oxygen_logo)
oxygen_logo = Label(window, text = "Oxygen", foreground = "Black", font =("Times New Roman", 13))
oxygen_logo.place(x = 1255, y = 675)
ph_data = Label(window, text = "---", foreground = "Black", font =("Times New Roman", 13))
ph_data.place(x = 1560, y = 625)

# --> Replace Data
label = Label(window,font = ("Times New Roman", 25), foreground = "Black")
label.place(x=1330, y=110)

# --> Define main function
def main():
    window.mainloop()

# --> Run GUI to Display 
if __name__ == '__main__':
    main()
