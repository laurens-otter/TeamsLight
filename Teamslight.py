import serial
import time
import os

serialPort = 'COM#'  # Change to the serial/COM port of the tower light
baudRate = 9600
raspiled = True

def find_last_occurrence(filename, target_string):
    last_occurrence = None
    
    with open(filename, 'r') as file:
        for line in file:
            if target_string in line:
                last_occurrence = line
    
    return last_occurrence

#Serial = serial.Serial(serialPort, baudRate)

RED_ON = 0x11
RED_OFF = 0x21
RED_BLINK = 0x41

YELLOW_ON= 0x12
YELLOW_OFF = 0x22
YELLOW_BLINK = 0x42

GREEN_ON = 0x14
GREEN_OFF = 0x24
GREEN_BLINK = 0x44

while True:

    # Example usage
    if __name__ == "__main__":
        log_file = "LOCAL USER APPDATA" + "\\Roaming\\Microsoft\\Teams\\logs.txt"  # Change this to your log file path
        target_string = "StatusIndicatorState"
        
        last_occurrence = find_last_occurrence(log_file, target_string)

    last_occurrence = last_occurrence.split(' ')
    for i,word in enumerate(last_occurrence):
        if word == "Added":
            status=last_occurrence[i + 1]
            #print(status)

    
    mSerial = serial.Serial(serialPort, baudRate)
    if status == "Available":
        if raspiled == True:
            mSerial.write(str.encode('green'))
        else:
            mSerial.write(bytes([RED_OFF]))
            mSerial.write(bytes([YELLOW_OFF]))
            mSerial.write(bytes([GREEN_ON]))
    elif  status == "Away":
        if raspiled == True:
            mSerial.write(str.encode('yellow'))
        else:
            mSerial.write(bytes([RED_OFF]))
            mSerial.write(bytes([GREEN_OFF]))
            mSerial.write(bytes([YELLOW_ON]))
    elif  status == "Busy":
        if raspiled == True:
            mSerial.write(str.encode('red'))
        else:
            mSerial.write(bytes([GREEN_OFF]))
            mSerial.write(bytes([YELLOW_OFF]))
            mSerial.write(bytes([RED_ON]))
    mSerial.close()
    time.sleep(2)

