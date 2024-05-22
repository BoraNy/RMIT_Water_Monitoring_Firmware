import ttkbootstrap as ttk
from serialModule import SerialCommunication
from tkinter import *
from ttkbootstrap.constants import *
from time import strftime
from paho.mqtt import client as mqtt_client
import json
import random
from datetime import datetime

ph, do, tds, tempc = 0, 0, 0, 0
Temperature, TDS, dissolvedOxygen, pH = '', '', '', ''

window = Tk()
width = window.winfo_screenwidth()
height = window.winfo_screenheight()
window.geometry(f'{width}x{height}')
window.state('zoomed')
window.title('Water Quality Monitoring')
window.config(bg='skyblue')

frame1 = Frame(window, width=width * .5, height=height * .1)
frame1.grid(row=0, column=0, padx=20, pady=20)

npic_name_khmer = Label(frame1, font=("Khmer OS Muol Light", 18), text='វិទ្យាស្ថានជាតិពហុបច្ចេកទេសកម្ពុជា')
npic_name_khmer.grid(row=0, column=0)
npic_name_english = Label(frame1, font=("Arial", 16), text='National Polytechnic Institute of Cambodia')
npic_name_english.grid(row=1, column=0)

frame2 = Frame(window, width=width * .5, height=height * .9)
frame2.grid(row=1, column=0, padx=1, pady=1)

# PH
ph_meter = ttk.Meter(frame2,
                     amounttotal=14,
                     meterthickness=30,
                     metersize=frame2.winfo_screenwidth() // 5,
                     padding=5,
                     amountused=ph,
                     metertype="full",
                     subtext="Potential of Hydrogen",
                     interactive=False,
                     subtextfont=["Arial", 16, "bold"]
                     )
ph_meter.grid(row=0, column=0, padx=1, pady=1)
# TDS
tds_meter = ttk.Meter(frame2,
                      amounttotal=1000,
                      meterthickness=30,
                      metersize=frame2.winfo_screenwidth() // 5,
                      padding=5,
                      amountused=tds,
                      metertype="full",
                      subtext="Total Dissolved Solid",
                      interactive=False,
                      subtextfont=["Arial", 16, "bold"]
                      )
tds_meter.grid(row=1, column=0, padx=1, pady=1)
# DO
do_meter = ttk.Meter(frame2,
                     amounttotal=20,
                     meterthickness=30,
                     metersize=frame2.winfo_screenwidth() // 5,
                     padding=5,
                     amountused=do,
                     metertype="full",
                     subtext="Dissolved Oxygen",
                     interactive=False,
                     subtextfont=["Arial", 16, "bold"]
                     )
do_meter.grid(row=0, column=1, padx=1, pady=1)
# TEMPC
tempc_meter = ttk.Meter(frame2,
                        amounttotal=150,
                        meterthickness=30,
                        metersize=frame2.winfo_screenwidth() // 5,
                        padding=5,
                        amountused=tempc,
                        metertype="full",
                        subtext="Temperature",
                        interactive=False,
                        subtextfont=["Arial", 16, "bold"]
                        )
tempc_meter.grid(row=1, column=1, padx=1, pady=1)

frame3 = Frame(window, width=width * .5, height=height * .1)
frame3.grid(row=0, column=1, padx=1, pady=1)
date_text = Label(frame3, font=("Arial", 16),
                  text=f'{datetime.now()}')
date_text.grid(row=0, column=0)

frame4 = Frame(window, width=width * .5, height=height * .9)
frame4.grid(row=1, column=1, padx=1, pady=1)
#
ph_text = Label(frame4, font=("Arial", 16),
                text=f'PH State: NULL')
ph_text.grid(row=0, column=0, padx=1, pady=1, sticky='W')
#
do_text = Label(frame4, font=("Arial", 16),
                text=f'DO State: NULL')
do_text.grid(row=1, column=0, padx=1, pady=1, sticky='W')
#
tds_text = Label(frame4, font=("Arial", 16),
                 text=f'TDS State: NULL')
tds_text.grid(row=2, column=0, padx=1, pady=1, sticky='W')
#
tempc_text = Label(frame4, font=("Arial", 16),
                   text=f'Temperature State: NULL')
tempc_text.grid(row=3, column=0, padx=1, pady=1, sticky='W')


def mqtt_connection() -> mqtt_client:
    broker = "broker.hivemq.com"
    port = 1883
    client_id = f'python-mqtt-{random.randint(0, 100)}'
    username = "NPIC_MQTT"
    password = "NPIC_RMIT_Project"

    def on_connection(client, userdata, flags, rc):
        if rc == 0:
            print("[  OK  ] MQTT-CONNECTION")
        else:
            print("[FAILED] MQTT-CONNECTION")

    client = mqtt_client.Client(mqtt_client.CallbackAPIVersion.VERSION1, client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connection
    client.connect(broker, port)
    return client


def subscribe(client: mqtt_client):
    def on_message(client, userdata, message):
        # ---------------- Print Data from Json ---------------------#
        global pH, Temperature, TDS, dissolvedOxygen
        try:
            data = json.loads(message.payload.decode())
            Temperature = str(data["notification"]["parameters"]["Temperature"])
            TDS = str(data["notification"]["parameters"]["TDS"])
            pH = str(data["notification"]["parameters"]["pH"])
            dissolvedOxygen = str(data["notification"]["parameters"]["Oxygen"])
        except:
            pass

        try:
            global ph, do, tds, tempc
            print(ph, do, tds, tempc)
            ph = float(pH)
            do = float(dissolvedOxygen)
            tds = float(TDS)
            tempc = float(Temperature)

            # Update Meters
            ph_meter.configure(amountused=ph)
            tds_meter.configure(amountused=tds)
            tempc_meter.configure(amountused=tempc)
            do_meter.configure(amountused=do)

            # Update Labels
            date_text.configure(text=f'{datetime.now()}')

        except:
            pass

    client.subscribe("Message")
    client.on_message = on_message


if __name__ == '__main__':
    client = mqtt_connection()
    subscribe(client)
    client.loop_start()
    window.mainloop()
    client.loop_stop()
