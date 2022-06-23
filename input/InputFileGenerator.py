import json
import random
import sys

# Available configurations:
# - fourSquare
# - evacuateRoom
# - twoExitsTwoGroups

def main(argv):
    if len(argv) == 0:
        toGenerate = ["fourSquare", "evacuateRoom", "twoExitsTwoGroups"]
    else:
        toGenerate = argv
    
    for config in toGenerate:
        if config == "fourSquare":
            fourSquare = {}
            fourSquare["config"] = {"width": 9, "height": 9, "scale": 100, "delay": 0}
            
            fourSquare["room"] = {"walls": [
                [3.15, 3.15, 4.25, 3.15], 
                [4.25, 3.15, 4.25, 4.25], 
                [4.25, 4.25, 3.15, 4.25],
                [3.15, 4.25, 3.15, 3.15], 

                [4.75, 3.15, 5.85, 3.15],
                [5.85, 3.15, 5.85, 4.25],
                [5.85, 4.25, 4.75, 4.25],
                [4.75, 4.25, 4.75, 3.15],

                [3.15, 4.75, 4.25, 4.75],
                [4.25, 4.75, 4.25, 5.85],
                [4.25, 5.85, 3.15, 5.85],
                [3.15, 5.85, 3.15, 4.75],

                [4.75, 4.75, 5.85, 4.75],
                [5.85, 4.75, 5.85, 5.85],
                [5.85, 5.85, 4.75, 5.85],
                [4.75, 5.85, 4.75, 4.75]
            ]}

            actorList = []
            offsets = [[0.5, 0.5], [6.5, 0.5], [0.5, 6.5], [6.5, 6.5]]
            colors = [[255, 0, 0], [0, 255, 0], [0, 0, 255], [150, 150, 150]]
            for o in range (0, len(offsets)):
                for i in range(0, 5):
                    for j in range(0, 5):
                        actorList.append({
                            "pos": [offsets[o][0] + (i * 0.5), offsets[o][1] + (j * 0.5)],
                            "velocity": [0.01, 0.01],
                            "desiredSpeed": 2.0,
                            "path": [[offsets[len(offsets) - o - 1][0] + (i * 0.5), offsets[len(offsets) - o - 1][1] + (j * 0.5)]],
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": colors[o],
                            "heatmapEnabled": False
                        })
            fourSquare["actors"] = actorList
            
            with open("fourSquare.json", "w") as out:
                json.dump(fourSquare, out, ensure_ascii=False, indent=4)

        elif config == "evacuateRoom":
            evacuateRoom = {}
            evacuateRoom["config"] = {"width": 9, "height": 9, "scale": 100, "delay": 0}

            evacuateRoom["room"] = {"walls": [
                [0.5, 0.5, 8.5, 0.5],
                [8.5, 0.5, 8.5, 8.5],
                [8.5, 8.5, 0.5, 8.5],
                [0.5, 8.5, 0.5, 4.15],
                [0.5, 3.85, 0.5, 0.5]
            ]}

            actorList = []
            for i in range(0, 20):
                for j in range(0, 35):
                    actorList.append({
                        "pos": [4 + (i * 0.2), 1 + (j * 0.2)],
                        "velocity": [0.01, 0.01],
                        "desiredSpeed": 2.0,
                        "path": [[0.5, 4.1], [-5, 4.1]],
                        "mass": 50,
                        "radius": 0.05,
                        "atDestination": False,
                        "color": [255, 0, 0],
                        "heatmapEnabled": True
                    })
            evacuateRoom["actors"] = actorList

            with open("evacuateRoom.json", "w") as out:
                json.dump(evacuateRoom, out, ensure_ascii=False, indent=4)

        elif config == "twoExitsTwoGroups":
            twoExitsTwoGroups = {}
            twoExitsTwoGroups["config"] = {"width": 9, "height": 9, "scale": 100, "delay": 0}

            twoExitsTwoGroups["room"] = {"walls": [
                [0.5, 0.5, 8.5, 0.5],
                [8.5, 0.5, 8.5, 6],
                [8.5, 6.4, 8.5, 8.5],
                [8.5, 8.5, 0.5, 8.5],
                [0.5, 8.5, 0.5, 4.2],
                [0.5, 3.8, 0.5, 0.5]
            ]}

            actorList = []
            for i in range(0, 10):
                for j in range(0, 35):
                    actorList.append({
                        "pos": [6.5 + (i * 0.2), 1 + (j * 0.2)],
                        "velocity": [0.01, 0.01],
                        "desiredSpeed": 2.0,
                        "path": [[0.5, 4.0], [-10, 4.0]],
                        "mass": 50,
                        "radius": 0.05,
                        "atDestination": False,
                        "color": [255, 0, 0],
                        "heatmapEnabled": False
                    })
            for i in range(0, 10):
                for j in range(0, 35):
                    actorList.append({
                        "pos": [0.8 + (i * 0.2), 1 + (j * 0.2)],
                        "velocity": [0.01, 0.01],
                        "desiredSpeed": 2.0,
                        "path": [[8.5, 6.2], [20, 6.2]],
                        "mass": 50,
                        "radius": 0.05,
                        "atDestination": False,
                        "color": [0, 255, 0],
                        "heatmapEnabled": False
                    })
            twoExitsTwoGroups["actors"] = actorList

            with open("twoExitsTwoGroups.json", "w") as out:
                json.dump(twoExitsTwoGroups, out, ensure_ascii=False, indent=4)

if __name__ == "__main__":
    main(sys.argv[1:])
