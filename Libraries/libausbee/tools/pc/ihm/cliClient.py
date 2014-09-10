import sys
sys.path.insert(0,"./")
import cli

ui = cli.ausbee_command_line_interface("/dev/ttyUSB0",115200)

ui.start()
