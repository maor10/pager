import multiprocessing
import os
import subprocess
from functools import wraps
from pathlib import Path
import cpager
from interruptingcow import timeout
from pager import Listener, Client
from pager.consts import BASE_DIRECTORY

PATH = Path('/tmp/demo_client.txt')

#
# def run_in_subprocess(func):
#     module_name = func.__module__.split('.')[-1]
#     child = subprocess.Popen(['python3', "-m", f'{module_name}', func.__name__], env=my_env)
#     child.communicate()
#     rc = child.returncode
#     assert rc == 0, f"RC IS {rc}"
#
#
# def subprocess_test(func):
#     @wraps(func)
#     def _wrapper(should_run=False, *args, **kwargs):
#         if should_run:
#             func(*args, **kwargs)
#         else:
#             run_in_subprocess(func)
#     return _wrapper


def demo_client():
    client = Client.create()
    client.send_request_to_take_snapshot()
    with open(PATH, 'a') as f:
        f.write('a')


def test_listener():
    if PATH.exists():
        PATH.unlink(missing_ok=True)
    listener = Listener.create()
    listener_process = multiprocessing.Process(target=listener.run)
    listener_process.start()
    client_process = multiprocessing.Process(target=demo_client)
    client_process.start()
    with timeout(3):
        while True:
            if PATH.exists():
                break
    listener_process.kill()
    client_process.kill()
    restore_process = multiprocessing.Process(target=cpager.restore_from_snapshot,
                                              args=(str(BASE_DIRECTORY / str(client_process.pid)),))
    restore_process.start()
    # print(str(BASE_DIRECTORY / str(client_process.pid)))
    # os.system(f"sudo pager restore --pid {client_process.pid}")
    # cpager.restore_from_snapshot(str(BASE_DIRECTORY / str(client_process.pid)))
    with timeout(1):
        while True:
            with open(PATH, 'r') as f:
                if len(f.read()) == 2:
                    break
