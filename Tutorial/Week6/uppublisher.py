import paho.mqtt.publish as publish
import serial

ser = serial.Serial("/dev/rfcomm1", 9600)  # Adjust to your serial port

while True:
    if ser.in_waiting > 0:
        message = ser.readline().decode().strip()
        if message == "LED_ON":
            publish.single("ifn649", "LED_ON", hostname="13.239.137.36")
            print("Published: LED_ON")
        elif message == "LED_OFF":
            publish.single("ifn649", "LED_OFF", hostname="13.239.137.36")
            print("Published: LED_OFF")
