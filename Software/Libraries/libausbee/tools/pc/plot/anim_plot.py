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
lines = []
lines_text = []

values=[]

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

#Init only required for blitting to give a clean slate.
def init():
    for i in range(4):
        values.append([])

        line, = ax.plot(x, (ymax-ymin)/2*(np.sin(x))-ymin, 'o-')
        line.set_ydata(np.ma.array(x, mask=True))
        lines.append(line)

        line_text = ax.text(0.02, 0.95-i*0.05, '', transform=ax.transAxes)
        line_text.set_text('')
        lines_text.append(line_text)

    l = lines[:]
    l.extend(lines_text)
    return l

ani = animation.FuncAnimation(fig, animate, np.arange(1, 200000), init_func=init,
    interval=25, blit=True)
plt.show()
