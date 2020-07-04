import os
import time
from pathlib import Path

import cpager
from multiprocessing.connection import Listener as MultiProcessingListener

from pager.consts import PORT, BASE_DIRECTORY


class Listener:

    def __init__(self, listener: MultiProcessingListener, base_directory: Path):
        self.listener = listener
        self.base_directory = base_directory

    @classmethod
    def create(cls):
        return cls(MultiProcessingListener(('0.0.0.0', PORT)), BASE_DIRECTORY)

    def run(self):
        while True:
            conn = self.listener.accept()
            pid = conn.recv()
            directory = self.base_directory / str(pid)
            directory.mkdir(exist_ok=True)
            cpager.take_snapshot(pid, str(directory))
            conn.send(True)


if __name__ == '__main__':
    Listener.create().run()
