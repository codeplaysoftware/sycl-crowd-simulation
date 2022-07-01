import json
import random
import sys

# Available configurations:
# - fourSquare
# - twoExitsTwoGroups
# - tightCorner
# - laneFiltering
# - evacuateRoom
# - evacuateRoomLarge

def main(argv):
    if len(argv) == 0:
        toGenerate = ["fourSquare", "twoExitsTwoGroups", "tightCorner", "laneFiltering",
                      "evacuateRoom", "evacuateRoomLarge"]
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
                        point = [offsets[len(offsets) - o - 1][0] + (i * 0.5), offsets[len(offsets) - o - 1][1] + (j * 0.5)]
                        pathList.append({
                            "id": idCounter,
                            "checkpoints": [[[point[0] - 0.01, point[1] - 0.01], 
                                             [point[0] + 0.01, point[1] - 0.01],
                                             [point[0] + 0.01, point[1] + 0.01], 
                                             [point[0] - 0.01, point[1] + 0.01]]]
                        })
                        actorList.append({
                            "pos": [offsets[o][0] + (i * 0.5), offsets[o][1] + (j * 0.5)],
                            "velocity": [0, 0],
                            "desiredSpeed": 0.6,
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
                        "velocity": [0, 0],
                        "desiredSpeed": 1.0,
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
                        "velocity": [0, 0],
                        "desiredSpeed": 1.0,
                        "pathId": 1,
                        "mass": 50,
                        "radius": 0.05,
                        "atDestination": False,
                        "color": [0, 255, 0],
                        "heatmapEnabled": False
                    })

            twoExitsTwoGroups["paths"] = [{"id": 0, "checkpoints": [
                [[0.3, 3.8], [0.7, 3.8], [0.7, 4.2], [0.3, 4.2]],
                [[-11, 3.5], [-10, 3.5], [-10, 4.5], [-11, 4.5]]
            ]},
                                          {"id": 1, "checkpoints": [
                [[8.3, 6], [8.7, 6], [8.7, 6.4], [8.3, 6.4]],
                [[20, 5.7], [21, 5.7], [21, 6.7], [20, 6.7]]
            ]}]
            twoExitsTwoGroups["actors"] = actorList

            with open("twoExitsTwoGroups.json", "w") as out:
                json.dump(twoExitsTwoGroups, out, ensure_ascii=False, indent=4)
            
            print("Finished Generating ../input/twoExitsTwoGroups.json")

        elif config == "tightCorner":
            tightCorner = {}
            tightCorner["config"] = {"width": 9, "height": 9, "scale": 100, "delay": 0}

            tightCorner["room"] = {"walls": [
                [0, 0, 6, 0],
                [0, 0, 0, 4],
                [0, 4, 5.5, 4],
                [5.5, 4, 5.5, 6],
                [5.5, 6, 7.5, 6],
                [7.5, 6, 7.5, 9],
                [6, 0, 6, 5.5],
                [6, 5.5, 8, 5.5],
                [8, 5.5, 8, 9]
            ]}

            actorList = []
            for i in range(0, 30):
                for j in range(0, 18):
                    actorList.append({
                        "pos": [0.1 + (i * 0.2), 0.1 + (j * 0.2)],
                        "velocity": [0, 0], 
                        "desiredSpeed": 1.0,
                        "pathId": 0,
                        "mass": 50,
                        "radius": 0.05,
                        "atDestination": False,
                        "color": [0, 0, 255],
                        "heatmapEnabled": True
                    })

            tightCorner["paths"] = [{"id": 0, "checkpoints": [
                [[6.8, 14.8], [7.2, 14.8], [7.2, 15.2], [6.8, 15.2]]
            ]}]
            tightCorner["actors"] = actorList
            
            with open("tightCorner.json", "w") as out:
                json.dump(tightCorner, out, ensure_ascii=False, indent=4)
            
            print("Finished Generating ../input/tightCorner.json")
        
        elif config == "laneFiltering":
            laneFiltering = {}
            laneFiltering["config"] = {"width": 14, "height": 9, "scale": 100, "delay": 0}

            laneFiltering["room"] = {"walls":  [
                [0.5, 0.5, 13.5, 0.5],
                [13.5, 0.5, 13.5, 8.5],
                [13.5, 8.5, 0.5, 8.5],
                [0.5, 8.5, 0.5, 0.5],

                [8.5, 0.5, 8.5, 3],
                [8.5, 3, 8.7, 3],
                [8.7, 3, 8.7, 0.5],

                [8.5, 3.3, 8.7, 3.3],
                [8.5, 3.6, 8.7, 3.6],
                [8.5, 3.9, 8.7, 3.9],
                [8.5, 4.2, 8.7, 4.2],
                [8.5, 4.5, 8.7, 4.5],
                [8.5, 4.8, 8.7, 4.8],
                [8.5, 5.1, 8.7, 5.1],
                [8.5, 5.4, 8.7, 5.4],
                [8.5, 5.7, 8.7, 5.7],

                [8.5, 6, 8.7, 6],
                [8.5, 6, 8.5, 8.5],
                [8.7, 6, 8.7, 8.5]
            ]}

            actorList = []
            for i in range(0, 20):
                for j in range(0, 35):
                    actorList.append({
                        "pos": [1 + (i * 0.2), 1 + (j * 0.2)],
                        "velocity": [0, 0],
                        "desiredSpeed": 1.0,
                        "pathId": 0,
                        "mass": 50,
                        "radius": 0.05,
                        "atDestination": False,
                        "color": [255, 0, 0],
                        "heatmapEnabled": True
                    })

            laneFiltering["paths"] = [{"id": 0, "checkpoints": [
                [[8.5, 3], [8.7, 3], [8.7, 6], [8.5, 6]],
                [[12.3, 4.3], [12.7, 4.3], [12.7, 4.7], [12.3, 4.7]]
            ]}]
            laneFiltering["actors"] = actorList

            with open("laneFiltering.json", "w") as out:
                json.dump(laneFiltering, out, ensure_ascii=False, indent=4)
            
            print("Finished Generating ../input/laneFiltering.json")            
        
        elif config == "evacuateRoom":
            evacuateRoom = {}
            evacuateRoom["config"] = {"width": 9, "height": 9, "scale": 100, "delay": 0}

            evacuateRoom["room"] = {"walls": [
                [0.5, 0.5, 8.5, 0.5],
                [8.5, 0.5, 8.5, 3.8],
                [8.5, 4.2, 8.5, 8.5],
                [8.5, 8.5, 0.5, 8.5],
                [0.5, 8.5, 0.5, 0.5]
            ]}

            actorList = []
            for i in range(0, 20):
                for j in range(0, 35):
                    actorList.append({
                        "pos": [1 + (i * 0.2), 1 + (j * 0.2)],
                        "velocity": [0, 0],
                        "desiredSpeed": 1.0,
                        "pathId": 0,
                        "mass": 50,
                        "radius": 0.05,
                        "atDestination": False,
                        "color": [255, 0, 0],
                        "heatmapEnabled": True
                    })
            evacuateRoom["paths"] = [{"id": 0, "checkpoints": [
                [[8.3, 3.9], [8.7, 3.9], [8.7, 4.3], [8.3, 4.3]], 
                [[15, 3.5], [16, 3.5], [16, 4.5], [15, 4.5]]
            ]}]
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
                        "velocity": [0, 0],
                        "desiredSpeed": 2.0,
                        "pathId": 0,
                        "mass": 50,
                        "radius": 0.05,
                        "atDestination": False,
                        "color": [255, 0, 0],
                        "heatmapEnabled": True
                    })
            evacuateRoomLarge["paths"] = [{"id": 0, "checkpoints": [
                [[0.3, 9.3], [0.7, 9.3], [0.7, 9.7], [0.3, 9.7]], 
                [[-11, 9], [-10, 9], [-10, 10], [-11, 10]]
            ]}]
            evacuateRoomLarge["actors"] = actorList

            with open("evacuateRoomLarge.json", "w") as out:
                json.dump(evacuateRoomLarge, out, ensure_ascii=False, indent=4)
            
            print("Finished Generating ../input/evacuateRoomLarge.json")


if __name__ == "__main__":
    main(sys.argv[1:])
