import PySimpleGUI as sg
import time

#RANGES = {"temp": (5, 45)}
#RANGES.update({"accel" + d: (-4, 4) for d in "xy"})
#RANGES.update({"accelz": (-12, -8)})
#RANGES.update({"mag" + d: (-100, 100) for d in "xyz"})
#RANGES.update({"gyro" + d: (-4, +4) for d in "xyz"})

RANGES = {"Front left brake temp (C)": (5, 45)}
RANGES.update({"Front right brake temp (C)": (5, 45)})
RANGES.update({"accel" + d + " (m/s^2)": (-4, 4) for d in "xy"})
RANGES.update({"accel z (m/s^2)": (-12, 2)})
RANGES.update({"gyro (rad/s)" + d: (-4, +4) for d in "xyz"})

#the next line defines which portions of the piped input string are considered FL brake temp, FR brake temp, etc
usefulindexes = [4, 5, 24, 25, 26, 27, 28, 29]
#as written, the 4th element is FL brake temp, the 5th is FR brake temp, the 24th is accel x, the 25th is accel y
#the 26th is accel z, the 27th is gyro x, 28th gyro y and 29th gyro z
#everything else in the string is discarded
#this may need a little tweaking to match the output of main.py
#the string is separated by spaces, so "1 2 3 4" becomes [1,2,3,4]

ORDERED_KEYS = list(RANGES.keys())

HISTDAT = {key: [] for key in ORDERED_KEYS}
CUR_DRAWN = {key: [] for key in ORDERED_KEYS}

sg.theme("DarkPurple4")


def makeGraph(gKey, gRange):
    return sg.Graph(canvas_size=(300, 150),
                    graph_bottom_left=(300, gRange[0]),
                    graph_top_right=(0, gRange[1]),
                    key=gKey,
                    background_color='white')


def makeWindow():
    print(ORDERED_KEYS)
    print(RANGES)
    print(ORDERED_KEYS[0:2])
    print(ORDERED_KEYS[2:5])
    print(ORDERED_KEYS[5:8])
    controlSection = [sg.Text("30 most recent data points from telemetry")]

    layout = [[makeGraph(key, RANGES[key])
               for key in ORDERED_KEYS[0:2]] + controlSection,
              [makeGraph(key, RANGES[key]) for key in ORDERED_KEYS[2:5]],
              [makeGraph(key, RANGES[key]) for key in ORDERED_KEYS[5:8]]]

    window = sg.Window("window title", layout, finalize=True)
    return window


def initGraphs(window):
    for graphKey in ORDERED_KEYS:
        graph = window[graphKey]
        cRange = RANGES[graphKey]
        graph.DrawText(graphKey, (80, cRange[1] // 2))
        for y in range(cRange[0], cRange[1], (cRange[1] - cRange[0]) // 3):
            graph.DrawLine((300, y), (0, y), color="#CCCCCC")
            graph.DrawText(y, (250, y), font="arial 10")
        graph.DrawLine((300, 0), (0, 0))


def updateGraphs(window):
    for graphKey in ORDERED_KEYS:
        graph = window[graphKey]
        for figID in CUR_DRAWN[graphKey]:
            graph.delete_figure(figID)
        CUR_DRAWN[graphKey] = []

        for valIdx, val in enumerate(HISTDAT[graphKey][::-1]):
            CUR_DRAWN[graphKey].append(
                graph.DrawCircle((valIdx * 10, val), 2, line_color="purple"))


def main():
    window = makeWindow()
    print(window)
    initGraphs(window)
    fpsCount = 0
    start_time = time.time()
    while True:

        event, values = window.read(timeout=0.005)
        if event == sg.WIN_CLOSED or event == 'Exit':
            break
        inLine = input().strip().split(" ")
        valuesused = 0
        for valIdx, val in enumerate(inLine[1:]):
            if valIdx in usefulindexes:
                HISTDAT[ORDERED_KEYS[valuesused]].append(float(val))
                HISTDAT[ORDERED_KEYS[valuesused]] = HISTDAT[
                    ORDERED_KEYS[valuesused]][-30::]
                valuesused += 1

        #print(inLine)
        updateGraphs(window)

        fpsCount += 1
        if (time.time() - start_time) > 1:
            print("FPS: ", fpsCount / (time.time() - start_time))
            fpsCount = 0
            start_time = time.time()


if __name__ == "__main__":
    main()
