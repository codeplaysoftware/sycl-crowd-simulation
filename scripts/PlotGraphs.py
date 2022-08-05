"""

Copyright (C) 2022 Codeplay Software Ltd.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Codeplay's crowd-simulation

PlotGraphs.py

Description:
  Script for plotting graphs from simulation statistics
 
"""

import matplotlib.pyplot as plt
import csv
import os.path
from threading import Thread
import time

complete = False


def workingAnimation():
    index = 0
    keyframes = "|/-\\"
    while not complete:
        print("Generating graphs " + keyframes[index % len(keyframes)], end="\r")
        index += 1
        time.sleep(0.1)
    print("Graphs have been writted to ../output/images")


animationThread = Thread(target=workingAnimation)
animationThread.start()

fig = plt.figure()
fig.set_facecolor("black")
ax = plt.axes()
ax.set_facecolor("black")
ax.spines["bottom"].set_color("white")
ax.spines["top"].set_color("white")
ax.spines["left"].set_color("white")
ax.spines["right"].set_color("white")
ax.tick_params(axis="x", colors="white")
ax.tick_params(axis="y", colors="white")
ax.xaxis.label.set_color("white")
ax.yaxis.label.set_color("white")
ax.title.set_color("white")

# Plot average forces
if not os.path.exists("../output/csv/averageForces.csv"):
    print("Error: couldn't find averageForces.csv")
else:
    with open("../output/csv/averageForces.csv") as file:
        reader = csv.reader(file, quoting=csv.QUOTE_NONNUMERIC)
        averageForces = list(reader)
        averageForces = list(zip(*averageForces))

    plt.plot(averageForces[0], averageForces[1], color="#A90092")
    plt.xlabel("Timestep")
    plt.ylabel("Average Force (N)")
    plt.title("Average Force Applied to Actor")
    plt.savefig("../output/images/averageForcesGraph.png")

    plt.clf()

fig = plt.figure()
fig.set_facecolor("black")
ax = plt.axes()
ax.set_facecolor("black")
ax.spines["bottom"].set_color("white")
ax.spines["top"].set_color("white")
ax.spines["left"].set_color("white")
ax.spines["right"].set_color("white")
ax.tick_params(axis="x", colors="white")
ax.tick_params(axis="y", colors="white")
ax.xaxis.label.set_color("white")
ax.yaxis.label.set_color("white")
ax.title.set_color("white")

# Plot kernel execution times
if not os.path.exists("../output/csv/kernelDurations.csv"):
    print("Error: couldn't find kernelDurations.csv")
else:
    with open("../output/csv/kernelDurations.csv") as file:
        reader = csv.reader(file, quoting=csv.QUOTE_NONNUMERIC)
        kernelDurations = list(reader)
        kernelDurations = list(zip(*kernelDurations))

    plt.plot(kernelDurations[0], kernelDurations[1], linewidth=0.5, color="#FBFF00")
    plt.xlabel("Kernel Number")
    plt.ylabel("Execution Time (μs)")
    plt.title("Kernel Execution Times")
    plt.savefig("../output/images/kernelDurationsGraph.png")

    plt.clf()

fig = plt.figure()
fig.set_facecolor("black")
ax = plt.axes()
ax.set_facecolor("black")
ax.spines["bottom"].set_color("white")
ax.spines["top"].set_color("white")
ax.spines["left"].set_color("white")
ax.spines["right"].set_color("white")
ax.tick_params(axis="x", colors="white")
ax.tick_params(axis="y", colors="white")
ax.xaxis.label.set_color("white")
ax.yaxis.label.set_color("white")
ax.title.set_color("white")

# Plot actor arrival times
if not os.path.exists("../output/csv/destinationTimes.csv"):
    print("Error: couldn't find distinationTimes.csv")
else:
    with open("../output/csv/destinationTimes.csv") as file:
        reader = csv.reader(file, quoting=csv.QUOTE_NONNUMERIC)
        destinationTimes = []
        for entry in reader:
            if entry[1] != -1:
                destinationTimes.append([int(entry[0]), int(entry[1])])
        destinationTimes = list(zip(*destinationTimes))

        if len(destinationTimes) > 0:
            operatingOn = sorted(destinationTimes[1])

            alteredDestinationTimes = [
                [i for i in range(0, max(operatingOn))],
                [0 for i in range(0, max(operatingOn))],
            ]
            for timestamp in operatingOn:
                if timestamp != -1:
                    for x in range(timestamp, max(operatingOn)):
                        alteredDestinationTimes[1][x] += 1

    if len(destinationTimes) > 0:
        plt.plot(
            alteredDestinationTimes[0], alteredDestinationTimes[1], color="#22AEE7"
        )
        plt.xlabel("No. of Actors at Destination")
        plt.ylabel("Time (ms)")
        plt.title("Actor Arrival Times at Destination")
        plt.savefig("../output/images/destinationTimesGraph.png")

complete = True
