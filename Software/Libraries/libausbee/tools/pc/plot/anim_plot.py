import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
ser = serial.Serial('/dev/ttyUSB0', 115200)

x_range = 50

fig, ax = plt.subplots()

x = np.arange(0, x_range, 1)        # x-array

ymin = -1000
ymax = 3000
values = []
lines = []
lines_text = []
num_lines = 1

def animate(num):
    lineread = ser.readline().split(",")
    for i in range(len(lineread)):
        val_name, val, scale = lineread[i].split(":")
        val = int(val)
        scale = float(scale)
        lines_text[i].set_text('%s = %.1f' % (val_name, val))
        values[i].append(val * scale)
        if num>x_range:
            lines[i].set_ydata(values[i][-x_range:])  # update the measure
    l = lines[:]
    l.extend(lines_text)
    return l

def init():
    global num_lines
    while not ser.readline():
        print("")
    for i in range(len(ser.readline().split(","))):
        values.append([])

        line, = ax.plot(x, (ymax-ymin)/2*(np.sin(x))-ymin, 'o-')
        lines.append(line)

        line_text = ax.text(0.02, 0.95-i*0.05, '', transform=ax.transAxes)
        lines_text.append(line_text)

    num_lines = i+1

#Reset only required for blitting to give a clean slate.
def reset():
    for i in range(num_lines):
        lines[i].set_ydata(np.ma.array(x, mask=True))
        lines_text[i].set_text('')

    l = lines[:]
    l.extend(lines_text)
    return l

init()
ani = animation.FuncAnimation(fig, animate, np.arange(1, 200000), init_func=reset,
    interval=25, blit=True)
plt.show()
