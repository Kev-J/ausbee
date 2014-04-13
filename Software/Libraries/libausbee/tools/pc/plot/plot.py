import numpy as np
import pylab as pl
from matplotlib import animation
import time
import serial


class PID_plot:

  def __init__(self,time_init):
    self.time      = []
    self.value     = []
    self.reference = []
    self.time_init = time_init

  def add_new_val(self,value,reference,time):
    self.time      += [time - self.time_init]
    self.value     += [value]
    self.reference += [reference]

  def plot(self):
    self.plot = pl.plot(self.time,self.value,'r', label     = 'value')
    self.plot1 = pl.plot(self.time,self.reference,'b', label     = 'Reference')
    pl.title('Plot PID')
    pl.xlabel('Plot by time')
    pl.ylabel('value')
    pl.legend(loc = 'upper left' , numpoints = 1)
    pl.show()

class ausbee_transmition_plot:

  def __init__(self,serial_path,baudrate):
    self.state = False
    self.ser = serial.Serial(str(serial_path),baudrate)
    self.pid_plot = PID_plot(time.time())

  def start_discution(self):
    self.state = True
    while self.state:
      val = self.ser.read(10)
      if len(val)!= 0:
        val_splited = val.split(",")
        if len(val_splited) == 1:
          if val_splited[0] == "stop":
              self.state = False
        elif len(val_splited)>1:
          self.pid_plot.add_new_val(val_splited[0],val_splited[1],time.time())
        time.sleep(0.01)
    self.pid_plot.plot()
    

