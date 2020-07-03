import sys
import cpager


def trace(frame, event, arg):
    if event == "line":
        cpager.run_on_line()
    return trace


def start_recording():
    sys.settrace(cpager.run_on_line)


if __name__ == '__main__':
    start_recording()

