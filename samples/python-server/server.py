import time
import yarp
from service_implementation import ServiceImplementation


def main():
    log_prefix = '[tcpi-python-server]';

    yarp.Network.init()

    service = ServiceImplementation('/tcpi/python-server/rpc:i')

    # Simulate main thread here
    while True:
        time.sleep(1)


if __name__ == '__main__':
    main()
