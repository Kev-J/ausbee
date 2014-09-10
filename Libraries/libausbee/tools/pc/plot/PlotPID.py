import sys
sys.path.insert(0,"../")
import plot
import time
import serial

# Initialisation des variables
val = []

# Opening port for serial communication
ser = serial.Serial("/dev/ttyUSB0",115200,timeout = 1)

#Initialisation of PID Plot
PidP = plot.PID_plot(time.time())

state = True

while state:
  val = ser.read()
  val_splited = val.split(",")
  if len(val_splited) == 1:
    if val_splited[0] == 'stop':
        state = false
  elif len(val_splited)>1:
    PidP.add_new_val(val_splited[0],val_splited[1],time.time())
    time.sleep(1)
  
PidP.plot()

