import random
import time
import sys

tenbrackets = "{} {} {} {} {} {} {} {} {} {} "

while True:
    print(("35VALS " + tenbrackets + tenbrackets + tenbrackets + "{} {} {} {} {}").format(
        random.randint(0, 10), #0
        random.randint(0, 10), #1
        random.randint(0, 10), #2
        random.randint(5, 45), #3
        random.randint(5, 45), #FL brake temp
        random.randint(5, 20), #FR brake temp
        random.randint(0, 10),
        random.randint(0, 10),
        random.randint(0, 10),
        random.uniform(0, 1),
        
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
        
        random.randint(0, 10), #20
        random.randint(0, 10), #21
        random.randint(0, 10), #22
        random.randint(0, 10), #23
        random.randint(0, 10), #accelx
        random.randint(0, 1),  #accely
        -random.randint(8, 12), #accelz
        -random.randint(0, 1), #gyrox
        -random.randint(0, 2), #gyroy
        random.uniform(0, 1),  #gyroz
        
        random.randint(0, 10),
        random.randint(0, 10),
        random.randint(0, 10),
        random.randint(0, 10),
        random.randint(0, 10),
        
    ))
    sys.stdout.flush()
    time.sleep(0.05)
