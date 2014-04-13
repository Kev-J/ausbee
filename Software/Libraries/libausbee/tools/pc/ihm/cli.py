import sys
import readline
sys.path.insert(0,"../plot/")
import plot

class command :

  def __init__(self,cmd):
    s = cmd.split(' ');
    self.cmd_name = s[0]
    self.cmd_arg  = s[1:]
    print self.cmd_name
    print self.cmd_arg 

  def split_arg(self):
    arg_list = []
    if len(self.cmd_arg) >1:
      for arg in self.cmd_arg:
        pair = arg.split(' ')
        arg_list += [[pair[0],int(pair[1])]]
        print arg_list
      self.cmd_arg = arg_list

class ausbee_command_line_interface:

  def __init__(self,serial_path,baudrate):
    self.debile = 0
    self.transmition_plot = plot.ausbee_transmition_plot(serial_path,baudrate)
    # TODO:
    #   - Verifier si il n'y aurait pas un probleme d'update

  def start(self):
    isRunning = True
    while isRunning:
      try:
        cmd = command(raw_input('$ '))
        if cmd.cmd_name == "q" or cmd.cmd_name == "quit":
          isRunning = False
        elif cmd.cmd_name == "Turn":
          cmd.split_arg()
          print "Il faut tourner de %s", cmd.cmd_arg
        elif cmd.cmd_name == "Goforward":
          cmd.split_arg()
          print "Il faut avancer de %s", cmd.cmd_arg
        elif cmd.cmd_name == "PlotPID":
          self.transmition_plot.start_discution()
      except:
        print(" Command not recognize ")
#        isRunning = False

