import json
import random
import sys

# Available configurations:
# - fourSquare
# - twoExitsTwoGroups
# - evacuateRoom
# - evacuateRoomLarge

def main(argv):
    if len(argv) == 0:
        toGenerate = ["fourSquare", "evacuateRoom", "twoExitsTwoGroups", "evacuateRoomLarge"]
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

            offsets = [[0.5, 0.5], [6.5, 0.5], [0.5, 6.5], [6.5, 6.5]]
            pathList = []
            actorList = []
            colors = [[255, 0, 0], [0, 255, 0], [0, 0, 255], [150, 150, 150]]
            idCounter = 0
            for o in range (0, len(offsets)):
                for i in range(0, 5):
                    for j in range(0, 5):
                        pathList.append({
                            "id": idCounter,
                            "checkpoints": [[offsets[len(offsets) - o - 1][0] + (i * 0.5), offsets[len(offsets) - o - 1][1] + (j * 0.5)]]
                        })
                        actorList.append({
                            "pos": [offsets[o][0] + (i * 0.5), offsets[o][1] + (j * 0.5)],
                            "velocity": [0.01, 0.01],
                            "desiredSpeed": 2.0,
                            "pathId": idCounter,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": colors[o],
                            "heatmapEnabled": False
                        })
                        idCounter += 1
            fourSquare["actors"] = actorList
            fourSquare["paths"] = pathList
            
            with open("fourSquare.json", "w") as out:
                json.dump(fourSquare, out, ensure_ascii=False, indent=4)

            print("Finished Generating ../input/fourSquare.json")

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
                        "pathId": 0,
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
                        "pathId": 1,
                        "mass": 50,
                        "radius": 0.05,
                        "atDestination": False,
                        "color": [0, 255, 0],
                        "heatmapEnabled": False
                    })
            twoExitsTwoGroups["paths"] = [{"id": 0, "checkpoints": [[0.5, 4.0], [-10, 4.0]]},
                                     {"id": 1, "checkpoints": [[8.5, 6.2], [20, 6.2]]}]
            twoExitsTwoGroups["actors"] = actorList

            with open("twoExitsTwoGroups.json", "w") as out:
                json.dump(twoExitsTwoGroups, out, ensure_ascii=False, indent=4)
            
            print("Finished Generating ../input/twoExitsTwoGroups.json")
        
        elif config == "evacuateRoom":
            evacuateRoom = {}
            evacuateRoom["config"] = {"width": 9, "height": 9, "scale": 100, "delay": 0}

            evacuateRoom["room"] = {"walls": [
                [0.5, 0.5, 8.5, 0.5],
                [8.5, 0.5, 8.5, 8.5],
                [8.5, 8.5, 0.5, 8.5],
                [0.5, 8.5, 0.5, 4.2],
                [0.5, 3.8, 0.5, 0.5]
            ]}

            actorList = []
            for i in range(0, 20):
                for j in range(0, 35):
                    actorList.append({
                        "pos": [4 + (i * 0.2), 1 + (j * 0.2)],
                        "velocity": [0.01, 0.01],
                        "desiredSpeed": 2.0,
                        "pathId": 0,
                        "mass": 50,
                        "radius": 0.05,
                        "atDestination": False,
                        "color": [255, 0, 0],
                        "heatmapEnabled": True
                    })
            evacuateRoom["paths"] = [{"id": 0, "checkpoints": [[0.5, 4.1], [-10, 4.1]]}]
            evacuateRoom["actors"] = actorList

            with open("evacuateRoom.json", "w") as out:
                json.dump(evacuateRoom, out, ensure_ascii=False, indent=4)
            
            print("Finished Generating ../input/evacuateRoom.json")
        
        elif config == "evacuateRoomLarge":
            evacuateRoomLarge = {}
            evacuateRoomLarge["config"] = {"width": 30, "height": 19, "scale": 50, "delay": 0}

            evacuateRoomLarge["room"] = {"walls": [
                [0.5, 0.5, 29.5, 0.5],
                [29.5, 0.5, 29.5, 18.5],
                [29.5, 18.5, 0.5, 18.5],
                [0.5, 18.5, 0.5, 9.7],
                [0.5, 9.3, 0.5, 0.5]
            ]}

            actorList = []
            for i in range(0, 120):
                for j in range(0, 85):
                    actorList.append({
                        "pos": [4 + (i * 0.2), 1 + (j * 0.2)],
                        "velocity": [0.01, 0.01],
                        "desiredSpeed": 2.0,
                        "pathId": 0,
                        "mass": 50,
                        "radius": 0.05,
                        "atDestination": False,
                        "color": [255, 0, 0],
                        "heatmapEnabled": True
                    })
            evacuateRoomLarge["paths"] = [{"id": 0, "checkpoints": [[0.5, 9.5], [-10, 9.5]]}]
            evacuateRoomLarge["actors"] = actorList

            with open("evacuateRoomLarge.json", "w") as out:
                json.dump(evacuateRoomLarge, out, ensure_ascii=False, indent=4)
            
            print("Finished Generating ../input/evacuateRoomLarge.json")

if __name__ == "__main__":
    main(sys.argv[1:])
