import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
ser = serial.Serial('/dev/ttyUSB0', 115200)

x_range = 50

fig = plt.figure()

right_ax = fig.add_subplot(1, 2, 1)
right_values = []
right_lines = []
right_lines_text = []

left_ax = fig.add_subplot(1, 2, 2)
left_values = []
left_lines = []
left_lines_text = []

num_lines = 1

x = np.arange(0, x_range, 1)        # x-array

ymin = -1000
ymax = 3000

def animate(num):
    # Right motor
    lineread = ser.readline().split(",")
    for i in range(len(lineread)):
        val_name, val, scale = lineread[i].split(":")
        val = int(val)
        scale = float(scale)
        right_lines_text[i].set_text('%s = %.1f' % (val_name, val))
        right_values[i].append(val * scale)
        if num>x_range:
            right_lines[i].set_ydata(right_values[i][-x_range:])  # update the measure

    l = right_lines[:]
    l.extend(right_lines_text)

    # Left motor
    lineread = ser.readline().split(",")
    for i in range(len(lineread)):
        val_name, val, scale = lineread[i].split(":")
        val = int(val)
        scale = float(scale)
        left_lines_text[i].set_text('%s = %.1f' % (val_name, val))
        left_values[i].append(val * scale)
        if num>x_range:
            left_lines[i].set_ydata(left_values[i][-x_range:])  # update the measure

    l.extend(left_lines[:])
    l.extend(left_lines_text)

    return l

def init():
    global num_lines
    while not ser.readline():
        print("")
    for i in range(len(ser.readline().split(","))):
        right_values.append([])
        left_values.append([])

        line, = right_ax.plot(x, (ymax-ymin)/2*(np.sin(x))-ymin, 'o-')
        right_lines.append(line)
        line, = left_ax.plot(x, (ymax-ymin)/2*(np.sin(x))-ymin, 'o-')
        left_lines.append(line)

        line_text = right_ax.text(0.02, 0.95-i*0.05, '', transform=right_ax.transAxes)
        right_lines_text.append(line_text)
        line_text = left_ax.text(0.02, 0.95-i*0.05, '', transform=left_ax.transAxes)
        left_lines_text.append(line_text)

    num_lines = i+1

#Reset only required for blitting to give a clean slate.
def reset():
    for i in range(num_lines):
        right_lines[i].set_ydata(np.ma.array(x, mask=True))
        right_lines_text[i].set_text('')

        left_lines[i].set_ydata(np.ma.array(x, mask=True))
        left_lines_text[i].set_text('')

    l = right_lines[:]
    l.extend(right_lines_text)

    l.extend(left_lines[:])
    l.extend(left_lines_text)

    return l

init()
ani = animation.FuncAnimation(fig, animate, np.arange(1, 200000), init_func=reset,
    interval=25, blit=True)
plt.show()
