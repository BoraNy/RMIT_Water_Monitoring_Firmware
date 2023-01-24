import tkinter as tk
import math 
from random import randint

# --> Set the variables 
window = tk.Tk()
window.geometry("1920x1080") 

# --> width of the arc 
arcWidth=20

# --> dimensions for the arc 
x1,y1,x2,y2=30,30,355,355 
x,y,r=195,195,135

# --> Access Data to arc
degree = randint(0,180)

# --> Create arc for show
temperature = tk.Canvas(window, width=400, height=400)
temperature.grid(row=0,column=0)
temperature.create_arc(x1, y1,x2,y2, start=0, extent=180,outline='#80FF00',width=arcWidth,style=tk.ARC)
      
# --> small circle at center
temperature.create_oval(x-10,y-10,x+10,y+10,fill='#000099') 
in_radian=math.radians(degree) # getting radian value 
line=temperature.create_line(x,y,(x+r*math.cos(in_radian)),
        (y-r*math.sin(in_radian)),width=6,arrow='last')

if __name__ == "__main__":
    window.mainloop()
