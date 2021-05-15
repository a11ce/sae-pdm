import random
import time
import sys

while True:
    print("10VALS {} {} {} {} {} {} {} {} {} {}".format(
        random.randint(0, 10),
        random.randint(0, 10),
        random.randint(0, 10),
        random.randint(0, 10),
        random.randint(0, 10),
        random.randint(0, 10),
        random.randint(0, 10),
        random.randint(0, 10),
        random.randint(0, 10),
        random.uniform(0, 1),
    ))
    sys.stdout.flush()
    time.sleep(0.05)
