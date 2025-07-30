import time

scancodes = {}
with open("./scancodes.txt") as f:
    for line in f.readlines():
        words = line.split()
        if len(words) > 0:
            if words[2].isdigit():
                scancodes[words[2]] = words[1][4:]

data = []

with open("./keylogger.txt") as f:
    for line in f.readlines():
        words = line.split()

        timestamp = round(float(words[0][:-1]))
        scancode = words[1]

        data.append((timestamp, scancode))


print("FREQUENCY ANALYSIS")
freqs = {}

for timestamp, scancode in data:
        if scancodes[scancode] in freqs:
            freqs[scancodes[scancode]] += 1
        else:
            freqs[scancodes[scancode]] = 1

for key, freq in freqs.items():
    print("{:<5}: {}".format(key, freq))

print("KEYWORD ANALYSIS\n")
keywords = [
    "S U D O",
    "P A S S W O R D"
]

for keyword in keywords:
    print("\n" + keyword + " occurances:\n")

    keys = keyword.split()

    for i in range(len(data) - len(keys) + 1):
        scanned = []
        for j in range(i, i + len(keys)):
            scanned.append(scancodes[data[j][1]])

        if scanned == keys:
            t1 = data[i][0]
            t2 = data[i + len(keys) - 1][0]
            print("typed from {} ({} seconds ago) to {} ({} seconds ago)".format(t1, round(time.time() - t1), t2, round(time.time() - t2)))