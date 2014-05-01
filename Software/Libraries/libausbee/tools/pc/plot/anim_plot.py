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
line,  = ax.plot(x, (ymax-ymin)/2*(np.sin(x))-ymin, 'o-')
line2, = ax.plot(x, (ymax-ymin)/2*(np.sin(x))-ymin, 'o-')
line3, = ax.plot(x, (ymax-ymin)/2*(np.sin(x))-ymin, 'o-')
line4, = ax.plot(x, (ymax-ymin)/2*(np.sin(x))-ymin, 'o-')
measure_text   = ax.text(0.02, 0.95, '', transform=ax.transAxes)
error_text     = ax.text(0.02, 0.90, '', transform=ax.transAxes)
error_sum_text = ax.text(0.02, 0.85, '', transform=ax.transAxes)
command_text   = ax.text(0.02, 0.80, '', transform=ax.transAxes)

values=[]
values2=[]
values3=[]
values4=[]

def animate(i):
    lineread = ser.readline().split(",")
    val  = int(lineread[0])
    val2 = int(lineread[1])
    val3 = int(lineread[2])
    val4 = int(lineread[3])
    values.append(val)
    values2.append(val2)
    values3.append(val3/10)
    values4.append(val4*10)
    if i>x_range:
        line.set_ydata(values[-x_range:])  # update the measure
        line2.set_ydata(values2[-x_range:])  # update the error
        line3.set_ydata(values3[-x_range:])  # update the error sum
        line4.set_ydata(values4[-x_range:])  # update the command
    measure_text.set_text('measure = %.1f' % val)
    error_text.set_text('error = %.1f' % val2)
    error_sum_text.set_text('error sum = %.1f' % val3)
    command_text.set_text('command = %.1f' % val4)
    return line, line2, line3, line4, measure_text, error_text, error_sum_text, command_text

#Init only required for blitting to give a clean slate.
def init():
    line.set_ydata(np.ma.array(x, mask=True))
    line2.set_ydata(np.ma.array(x, mask=True))
    line3.set_ydata(np.ma.array(x, mask=True))
    line4.set_ydata(np.ma.array(x, mask=True))
    measure_text.set_text('')
    error_text.set_text('')
    error_sum_text.set_text('')
    command_text.set_text('')
    return line, line2, line3, line4, measure_text, error_text, error_sum_text, command_text

ani = animation.FuncAnimation(fig, animate, np.arange(1, 200000), init_func=init,
    interval=25, blit=True)
plt.show()
