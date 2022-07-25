import matplotlib.pyplot as plt
import csv
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

# Plot average forces
with open("../output/csv/averageForces.csv") as file:
    reader = csv.reader(file, quoting=csv.QUOTE_NONNUMERIC)
    averageForces = list(reader)
    averageForces = list(zip(*averageForces))

plt.plot(averageForces[0], averageForces[1])
plt.xlabel("Timestep")
plt.ylabel("Average Force (N)")
plt.title("Average Force Applied to Actor")
plt.savefig("../output/images/averageForcesGraph.png")

plt.clf()

with open("../output/csv/kernelDurations.csv") as file:
    reader = csv.reader(file, quoting=csv.QUOTE_NONNUMERIC)
    kernelDurations = list(reader)
    kernelDurations = list(zip(*kernelDurations))

plt.plot(kernelDurations[0], kernelDurations[1], linewidth=0.5)
plt.xlabel("Kernel Number")
plt.ylabel("Execution Time (μs)")
plt.title("Kernel Execution Times")
plt.savefig("../output/images/kernelDurationsGraph.png")

plt.clf()

with open("../output/csv/destinationTimes.csv") as file:
    reader = csv.reader(file, quoting=csv.QUOTE_NONNUMERIC)
    destinationTimes = []
    for entry in reader:
        if entry[1] != -1:
           destinationTimes.append([int(entry[0]), int(entry[1])]) 
    destinationTimes = list(zip(*destinationTimes))

    operatingOn = sorted(destinationTimes[1])

    alteredDestinationTimes = [[i for i in range(0, max(operatingOn))], [0 for i in range(0, max(operatingOn))]]
    for timestamp in operatingOn:
        if timestamp != -1:
            for x in range(timestamp, max(operatingOn)):
                alteredDestinationTimes[1][x] += 1

if len(destinationTimes) > 0:
    plt.plot(alteredDestinationTimes[0], alteredDestinationTimes[1])
    plt.savefig("../output/images/destinationTimesGraph.png")

complete = True
