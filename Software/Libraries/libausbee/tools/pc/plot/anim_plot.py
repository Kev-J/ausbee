import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
ser = serial.Serial('/dev/ttyUSB0', 115200)


fig = plt.figure()
x_range = 50

class Subplot:
    def __init__(self, _ymin, _ymax, _x_range, fig, *args, **kwargs):
        self.ax = fig.add_subplot(*args)
        self.values = []
        self.lines = []
        self.lines_text = []
        self.num_lines = 0
        self.ymin = _ymin
        self.ymax = _ymax
        self.x_range = _x_range
        self.x = np.arange(0, x_range, 1)        # x-array
        self.dynamic_init(1)

    def dynamic_init(self, new_size):
        if new_size > self.num_lines:
            for i in range(new_size - self.num_lines):
                self.values.append([])

                line, = self.ax.plot(self.x, (self.ymax-self.ymin)/2*(np.sin(self.x))-self.ymin, 'o-')
                self.lines.append(line)

                line_text = self.ax.text(0.02, 0.95 - (self.num_lines + i) * 0.05, '', transform=self.ax.transAxes)
                self.lines_text.append(line_text)

            self.num_lines = new_size

    def update_lines(self, frame_num, lineread):
        splited_read = lineread.split(";")
        self.dynamic_init(len(splited_read))
        for i in range(self.num_lines):
            try:
                val_name, val, scale = splited_read[i].split(":")
                val = int(val)
                scale = float(scale)
                self.lines_text[i].set_text('%s = %.1f' % (val_name, val))
                self.values[i].append(val * scale)
            except ValueError:
                self.values[i].append(0)
                print("[ValueError] Input: \"" + splited_read[i] + "\"")
            if frame_num > self.x_range:
                self.lines[i].set_ydata(self.values[i][-x_range:])  # update the measure

        l = self.lines[:]
        l.extend(self.lines_text)

        return l

    def reset(self):
        for i in range(self.num_lines):
            self.lines[i].set_ydata(np.ma.array(self.x, mask=True))
            self.lines_text[i].set_text('')

        l = self.lines[:]
        l.extend(self.lines_text)

        return l

right_motor_subplot = Subplot(-1000, 3000, x_range, fig, 2, 2, 2)
left_motor_subplot = Subplot(-100, 3000, x_range, fig, 2, 2, 4)
robot_subplot = Subplot(-200, 1200, x_range, fig, 1, 2, 1)

def readline_starting_with(start_string):
    c = 'a'
    line = []
    while c != '\n':
        c = ser.read()
        if c != '\x00':
            line.append(c)

    line = ''.join(line)
    if line.startswith(start_string):
        return line
    else:
        return readline_starting_with(start_string)

def animate(frame_num):
    l = right_motor_subplot.update_lines(frame_num, readline_starting_with("Right"))
    l.extend(left_motor_subplot.update_lines(frame_num, readline_starting_with("Left")))
    l.extend(robot_subplot.update_lines(frame_num, readline_starting_with("Robot")))
    return l

#Reset only required for blitting to give a clean slate.
def reset():
    l = right_motor_subplot.reset()
    l.extend(left_motor_subplot.reset())
    l.extend(robot_subplot.reset())
    return l

ani = animation.FuncAnimation(fig, animate, np.arange(1, 200000), init_func=reset,
    interval=25, blit=True)
plt.show()
