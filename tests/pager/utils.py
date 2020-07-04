

@contextlib.contextmanager
def timeout_raiser(seconds_till_timeout):
    start_time = time.time()

    def checker(exception):
        if time.time() - seconds_till_timeout > start_time:
            raise TimeoutException from exception

    yield checker
