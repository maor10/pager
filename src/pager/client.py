import os
from multiprocessing.connection import Client as MultiProcessingClient
import time
from pager.consts import PORT


class Client:

    def __init__(self, connection: MultiProcessingClient, pid: int):
        self.connection = connection
        self.pid = pid

    @classmethod
    def create(cls):
        return cls(MultiProcessingClient(('localhost', PORT)), pid=os.getpid())

    def send_request_to_take_snapshot(self):
        self.connection.send(self.pid)
        try:
            # TODO check if in replay mode
            self.connection.recv()
        except ConnectionResetError:
            print("Connection reset error")

        for i in range(30):
            time.sleep(1)
            with open('/tmp/play.txt', 'a') as f:
                f.write(f'{i}\n')


if __name__ == '__main__':
    client = Client.create()
    client.send_request_to_take_snapshot()
    print("Finished execution")


