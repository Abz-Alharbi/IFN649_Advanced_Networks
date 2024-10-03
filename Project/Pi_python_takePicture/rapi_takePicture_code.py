import serial
import time
from picamera2 import Picamera2
import os

# Set up the PiCamera2
picam2 = Picamera2()
picam2.start_preview()

# Set up serial communication with Arduino
ser = serial.Serial('/dev/rfcomm0', 9600, timeout=1)

buffer=''

try:
    while True:
        # Read incoming data and append to buffer
        data = ser.read(ser.in_waiting or 1).decode('utf-8', errors='ignore')
        if data:
            buffer += data

        # Check if a complete message has been received
        if '\n' in buffer:
            line, buffer = buffer.split('\n', 1)
            line = line.strip()
            
            if line == "find a movement around the gate":
                print("Received ALERT message, taking a photo...")
                # Prepare the camera and settings if necessary
                config = picam2.create_still_configuration()
                picam2.configure(config)
                picam2.start()

                # Capture the photo and save it on the desktop
                timestamp = time.strftime("%Y%m%d-%H%M%S")
                photo_path = os.path.expanduser(f"~/Desktop/photo_{timestamp}.jpg")
                picam2.capture_file(photo_path)
                print(f"Photo saved as {photo_path}")
                
                picam2.stop()

        time.sleep(1)  # Avoid overloading the CPU with constant listening

except Exception as e:
    print(f"An error occurred: {e}")

finally:
    # Close the serial port and camera
    ser.close()
    picam2.stop_preview()
    print("Connection closed")
