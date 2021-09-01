import serial
import time
import os

s = serial.Serial("/dev/ttyS0", 115200)

while True:
        s.write(b"v;")
        voltage = float(s.read_until().decode().strip())
        print(f"{voltage:.2f} V")
        time.sleep(5)

        if voltage < 3.4:
                os.system("shutdown now")
