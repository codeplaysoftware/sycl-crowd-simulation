from curses.ascii import isdigit
from pickletools import read_unicodestringnl
import matplotlib.pyplot as plt
import csv

# Plot average forces
with open("../output/averageForces.csv") as file:
    reader = csv.reader(file, quoting=csv.QUOTE_NONNUMERIC)
    averageForces = list(reader)
    averageForces = list(zip(*averageForces))

plt.plot(averageForces[0], averageForces[1])
plt.xlabel("Timestep")
plt.ylabel("Average Force (N)")
plt.title("Average Force Applied to Actor")
plt.savefig("../output/averageForcesGraph.png")

plt.clf()

with open("../output/kernelDurations.csv") as file:
    reader = csv.reader(file, quoting=csv.QUOTE_NONNUMERIC)
    kernelDurations = list(reader)
    kernelDurations = list(zip(*kernelDurations))

plt.plot(kernelDurations[0], kernelDurations[1], linewidth=0.5)
plt.xlabel("Kernel Number")
plt.ylabel("Execution Time (μs)")
plt.title("Kernel Execution Times")
plt.savefig("../output/kernelDurationsGraph.png")

plt.clf()

with open("../output/destinationTimes.csv") as file:
    reader = csv.reader(file, quoting=csv.QUOTE_NONNUMERIC)
    destinationTimes = []
    for entry in reader:
        if entry[1] != -1:
           destinationTimes.append([int(entry[0]), int(entry[1])]) 
    destinationTimes = list(zip(*destinationTimes))

if len(destinationTimes) > 0:
    plt.plot(destinationTimes[0], destinationTimes[1])
    plt.show()
