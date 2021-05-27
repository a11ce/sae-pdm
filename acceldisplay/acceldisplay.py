import matplotlib.pyplot as plt
import sys

plt.ion()

idx = 0
idxDat = []

histDat = [[] for _ in range(12)]

fig, axs = plt.subplots(4, 3)
axs = axs.flatten()
axs[0].set_ylabel("accel (m/s^2)")
axs[3].set_ylabel("mag (uT)")
axs[6].set_ylabel("gyro (rad/s)")
axs[9].set_ylabel("temp (c)")

SHOW_SECS = 3
SAMPLES = SHOW_SECS * 100

lines = []
for ax in axs:
    line, = ax.plot([0, SAMPLES], [0, 10])
    lines.append(line)

plt.show()

print(lines)
for line in sys.stdin:

    idxDat.append(idx)

    line = line.strip().split(" ")
    if line[0] == "10VALS":
        for valIdx, val in enumerate(line[1:]):
            histDat[valIdx].append(float(val))
            #axs[valIdx].plot(idxDat, histDat[valIdx])
            print(histDat[valIdx])
            lines[valIdx].set_xdata(idxDat)
            lines[valIdx].set_ydata(histDat[valIdx])
        idx += 1
        fig.canvas.draw()
        fig.canvas.flush_events()
