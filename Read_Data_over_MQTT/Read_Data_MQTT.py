from paho.mqtt import client as mqtt_client
import json
import random
#----------------------- MQTT Identify --------------------#
broker = "broker.hivemq.com"
port = 1883
topic = "Message"
client_ID = f'python-mqtt-{random.randint(0, 100)}'
username = "NPIC_MQTT"
password = "NPIC_RMIT_Project"
#----------------------- Check Connection --------------------#
def MQTT_Connection() -> mqtt_client:
    def on_connection(client, userdata, flags, rc):
        if rc == 0:
            print("Successfully Connected to MQTT Broker!")
        else:
            print("Fialed to Connect to MQTT Broker")
    client = mqtt_client.Client(client_ID)
    client.username_pw_set(username,password)
    client.on_connect = on_connection
    client.connect(broker,port)
    return client
#----------------------- Check Subscribe --------------------# 
def subscribe(client: mqtt_client):
    def on_message(client, userdata, message):
        #---------------- Print Data from Json ---------------------#
        #print(f"Recieved '{message.payload.decode()}' from '{message.topic}' topic")
        data = json.loads(message.payload.decode())
        Temperature = str(data["notification"]["parameters"]["Temperature"])
        Turbidity = str(data["notification"]["parameters"]["Turbidity"])
        pH = str(data["notification"]["parameters"]["pH"])
        Oxigen = str(data["notification"]["parameters"]["Oxigen"])
        print("Temperature:" + Temperature + "\tTurbidity:" + Turbidity + "\tpH:" + pH + "\t\tOxigen:" + Oxigen)
    client.subscribe(topic)
    client.on_message = on_message

def main():
    client = MQTT_Connection()
    subscribe(client)
    client.loop_forever()
if __name__ == "__main__":
    main()
