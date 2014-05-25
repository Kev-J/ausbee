import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
from subplot import Subplot, SubplotTable

if len(sys.argv) == 1:
    ser = serial.Serial('/dev/ttyUSB0', 115200)
    is_file = False
else:
    ser = open(sys.argv[1], 'r')
    is_file = True

fig = plt.figure()
x_range = 100

#right_motor_subplot = Subplot( -1000, 1000, x_range, fig, 20, 20, 0)
#left_motor_subplot  = Subplot( -1000, 1000, x_range, fig, 2, 2, 2)
distance_subplot    = Subplot( -100, 1200, x_range, fig, 1, 1, 1)
#angle_subplot       = Subplot( -400,  400,  x_range, fig, 2, 2, 4)
#angle_subplot.hide()

#robot_subplot       = SubplotTable(fig, 20, 20, 0)

def readline_starting_with(start_string):
    c = 'a'
    line = []
    while c != '\n':
        if is_file:
            c = ser.read(1)
        else:
            c = ser.read()
        if c != '\x00':
            line.append(c)

    line = ''.join(line)
    if line.startswith(start_string):
        return line
    else:
        return readline_starting_with(start_string)

def animate(frame_num):
    #l = right_motor_subplot.update_lines(frame_num, readline_starting_with("Right"))
    #l.extend(left_motor_subplot.update_lines(frame_num, readline_starting_with("Left")))
    l = distance_subplot.update_lines(frame_num, readline_starting_with("Distance"))
    #l.extend(angle_subplot.update_lines(frame_num, readline_starting_with("Angle")))
    #l.extend(robot_subplot.update_lines(frame_num, readline_starting_with("Robot")))

    return l

#Reset only required for blitting to give a clean slate.
def reset():
    #l = right_motor_subplot.reset()
    #l.extend(left_motor_subplot.reset())
    #l.extend(distance_subplot.reset())
    l = distance_subplot.reset()
    #l.extend(angle_subplot.reset())
    #l.extend(robot_subplot.reset())
    return l

ani = animation.FuncAnimation(fig, animate, np.arange(1, 200000), init_func=reset,
    interval=25, blit=True)
plt.show()
