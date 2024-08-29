import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT")
    client.subscribe("ifn649")

def on_message(client, userdata, msg):
    message = msg.payload.decode()
    ser = serial.Serial("/dev/rfcomm1", 9600)
    if message == "LED_ON":
        print("The LED is ON")
        ser.write(str.encode('LED_ON'))
    elif message == "LED_OFF":
        print("The LED is OFF")
        ser.write(str.encode('LED_OFF'))


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("13.239.137.36", 1883, 60)
client.loop_forever()
