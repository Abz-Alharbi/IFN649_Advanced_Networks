import paho.mqtt.publish as publish
publish.single("ifn649", "LED_ON", hostname="3.24.218.246")
print("Done")