import numpy as np
import matplotlib.pyplot as plt

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
        self.x = np.arange(0, self.x_range, 1)        # x-array
        self.dynamic_init(1)

    def dynamic_init(self, new_size):
        if new_size > self.num_lines:
            for i in range(new_size - self.num_lines):
                self.values.append([])

                line, = self.ax.plot(self.x, (self.ymax-self.ymin)*((np.sin(self.x)+1)/2)+self.ymin, 'o-')
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
                val = float(val)
                scale = float(scale)
                self.lines_text[i].set_text('%s = %.1f' % (val_name, val))
                self.values[i].append(val * scale)
            except ValueError:
                self.values[i].append(0)
                print("[ValueError] Input: \"" + splited_read[i] + "\"")
            if frame_num > self.x_range:
                ydata = self.values[i][-self.x_range:]
            else:
                ydata = np.zeros(self.x_range)
                ydata[-frame_num:] = self.values[i][-frame_num:]
            self.lines[i].set_ydata(ydata)  # update the measure

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

class SubplotTable:
    def __init__(self, fig, *args, **kwargs):
        self.ax = fig.add_subplot(autoscale_on=False, xlim=(-750, 750), ylim=(-750, 750), *args)
        self.lines_x = [0]
        self.lines_y = [0]

        self.line, = self.ax.plot([], [], '-', lw=1)
        self.line_head_slice, = self.ax.plot([], [], '-', color='red', lw=2)
        self.line_head, = self.ax.plot([], [], color='red', marker='o', markeredgecolor='r')
        self.x_text = self.ax.text(0.05, 0.95, '', transform=self.ax.transAxes)
        self.y_text = self.ax.text(0.05, 0.9, '',  transform=self.ax.transAxes)

    def update_lines(self, frame_num, lineread):
        splited_read = lineread.split(";")

        x_name, x = splited_read[0].split(":")
        x = float(x)
        y_name, y = splited_read[1].split(":")
        y = float(y)

        self.x_text.set_text('%s = %.1f' % (x_name, x))
        self.y_text.set_text('%s = %.1f' % (y_name, y))

        self.lines_x.append(x)
        self.lines_y.append(y)

        self.line.set_data(self.lines_x, self.lines_y)
        self.line_head_slice.set_data(self.lines_x[-2:], self.lines_y[-2:])
        self.line_head.set_data(self.lines_x[-1], self.lines_y[-1])

        return self.line, self.line_head_slice, self.line_head, self.x_text, self.y_text

    def reset(self):
        self.line.set_data([], [])
        self.line_head.set_data([], [])
        self.line_head_slice.set_data([], [])
        self.x_text.set_text('')
        self.y_text.set_text('')

        return self.line, self.line_head_slice, self.line_head, self.x_text, self.y_text
