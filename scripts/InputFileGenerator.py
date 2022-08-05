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

InputFileGenerator.py

Description:
  Script for generating JSON input configurations
 
"""

# Available configurations:
# - fourSquare
# - fourCorridor
# - twoGroups
# - twoGroups10000
# - tightCorner
# - laneFiltering
# - corridorWidening
# - evacuateRoom
# - evacuateRoom10000
# - evacuateRoom50000

# Running script without args will generate all input configurations

import json
import random
import sys
from threading import Thread
import time

complete = False


def workingAnimation():
    index = 0
    keyframes = "|/-\\"
    while not complete:
        print("Generating input files " + keyframes[index % len(keyframes)], end="\r")
        index += 1
        time.sleep(0.1)
    print("Input files have been writted to ../input")


def main(argv):
    if len(argv) == 0:
        toGenerate = [
            ["fourSquare", {}],
            ["fourCorridor", {}],
            ["twoGroups", {}],
            ["twoGroups10000", {}],
            ["tightCorner", {}],
            ["laneFiltering", {}],
            ["corridorWidening", {}],
            ["evacuateRoom", {}],
            ["evacuateRoom10000", {}],
            ["evacuateRoom50000", {}],
        ]
    else:
        toGenerate = []
        for target in argv:
            toGenerate.append([target, {}])

    for config in toGenerate:
        if config[0] == "fourSquare":
            fourSquare = config[1]
            fourSquare["config"] = {
                "width": 9,
                "height": 9,
                "scale": 100,
                "delay": 0,
                "bgColor": [0, 0, 0],
                "wallColor": [255, 255, 255],
                "heatmapEnabled": False,
            }

            fourSquare["room"] = {
                "walls": [
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
                    [4.75, 5.85, 4.75, 4.75],
                ]
            }

            offsets = [[0.5, 0.5], [6.5, 0.5], [0.5, 6.5], [6.5, 6.5]]
            pathList = []
            actorList = []
            colors = [[169, 0, 146], [251, 255, 0], [34, 174, 231], [0, 150, 0]]
            idCounter = 0
            for o in range(0, len(offsets)):
                for i in range(0, 5):
                    for j in range(0, 5):
                        point = [
                            offsets[len(offsets) - o - 1][0] + (i * 0.5),
                            offsets[len(offsets) - o - 1][1] + (j * 0.5),
                        ]
                        pathList.append(
                            {
                                "id": idCounter,
                                "checkpoints": [
                                    [
                                        [point[0] - 0.01, point[1] - 0.01],
                                        [point[0] + 0.01, point[1] + 0.01],
                                    ]
                                ],
                            }
                        )
                        actorList.append(
                            {
                                "pos": [
                                    offsets[o][0] + (i * 0.5),
                                    offsets[o][1] + (j * 0.5),
                                ],
                                "velocity": [0, 0],
                                "desiredSpeed": 0.6,
                                "pathId": idCounter,
                                "mass": 50,
                                "radius": 0.05,
                                "atDestination": False,
                                "color": colors[o],
                            }
                        )
                        idCounter += 1

            fourSquare["actors"] = actorList
            fourSquare["paths"] = pathList

        elif config[0] == "fourCorridor":
            fourCorridor = config[1]
            fourCorridor["config"] = {
                "width": 9,
                "height": 9,
                "scale": 100,
                "delay": 0,
                "bgColor": [0, 0, 0],
                "wallColor": [255, 255, 255],
                "heatmapEnabled": False,
            }

            fourCorridor["room"] = {
                "walls": [
                    [-10, 3.5, 3.5, 3.5],
                    [3.5, 3.5, 3.5, -10],
                    [3.5, -10, 5.5, -10],
                    [5.5, -10, 5.5, 3.5],
                    [5.5, 3.5, 19, 3.5],
                    [19, 3.5, 19, 5.5],
                    [19, 5.5, 5.5, 5.5],
                    [5.5, 5.5, 5.5, 19],
                    [5.5, 19, 3.5, 19],
                    [3.5, 19, 3.5, 5.5],
                    [3.5, 5.5, -10, 5.5],
                    [-10, 5.5, -10, 3.5],
                ]
            }

            actorList = []
            for i in range(0, 9):
                for j in range(0, 50):
                    actorList.append(
                        {
                            "pos": [3.7 + (i * 0.2), -9.9 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 1.7,
                            "pathId": 0,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [34, 174, 231],
                        }
                    )
            for i in range(0, 9):
                for j in range(0, 50):
                    actorList.append(
                        {
                            "pos": [3.7 + (i * 0.2), 18.9 - (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 1.6,
                            "pathId": 1,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [251, 255, 0],
                        }
                    )
            for i in range(0, 50):
                for j in range(0, 9):
                    actorList.append(
                        {
                            "pos": [-9.9 + (i * 0.2), 3.7 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 1.8,
                            "pathId": 2,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [169, 0, 146],
                        }
                    )
            for i in range(0, 50):
                for j in range(0, 9):
                    actorList.append(
                        {
                            "pos": [18.9 - (i * 0.2), 3.7 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 1.5,
                            "pathId": 3,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [0, 150, 0],
                        }
                    )

            fourCorridor["paths"] = [
                {
                    "id": 0,
                    "checkpoints": [[[3.5, 18], [5.5, 19]]],
                },
                {
                    "id": 1,
                    "checkpoints": [[[3.5, -9], [5.5, -10]]],
                },
                {
                    "id": 2,
                    "checkpoints": [[[18, 3.5], [19, 5.5]]],
                },
                {
                    "id": 3,
                    "checkpoints": [[[-10, 3.5], [-9, 5.5]]],
                },
            ]

            fourCorridor["actors"] = actorList

        elif config[0] == "twoGroups":
            twoGroups = config[1]
            twoGroups["config"] = {
                "width": 9,
                "height": 9,
                "scale": 100,
                "delay": 0,
                "bgColor": [0, 0, 0],
                "wallColor": [255, 255, 255],
                "heatmapEnabled": False,
            }

            twoGroups["room"] = {
                "walls": [
                    [0.5, 0.5, 8.5, 0.5],
                    [8.5, 0.5, 8.5, 6],
                    [8.5, 6.4, 8.5, 8.5],
                    [8.5, 8.5, 0.5, 8.5],
                    [0.5, 8.5, 0.5, 4.2],
                    [0.5, 3.8, 0.5, 0.5],
                ]
            }

            actorList = []
            for i in range(0, 10):
                for j in range(0, 35):
                    actorList.append(
                        {
                            "pos": [6.5 + (i * 0.2), 1 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 1.5,
                            "pathId": 0,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [251, 255, 0],
                        }
                    )
            for i in range(0, 10):
                for j in range(0, 35):
                    actorList.append(
                        {
                            "pos": [0.8 + (i * 0.2), 1 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 1.5,
                            "pathId": 1,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [169, 0, 146],
                        }
                    )

            twoGroups["paths"] = [
                {
                    "id": 0,
                    "checkpoints": [
                        [[0.3, 3.8], [0.7, 4.2]],
                        [[-11, 3.5], [-10, 4.5]],
                    ],
                },
                {
                    "id": 1,
                    "checkpoints": [
                        [[8.3, 6], [8.7, 6.4]],
                        [[20, 5.7], [21, 6.7]],
                    ],
                },
            ]
            twoGroups["actors"] = actorList

        elif config[0] == "twoGroups10000":
            twoGroups10000 = config[1]
            twoGroups10000["config"] = {
                "width": 30,
                "height": 20,
                "scale": 50,
                "delay": 0,
                "bgColor": [0, 0, 0],
                "wallColor": [255, 255, 255],
                "heatmapEnabled": False,
            }

            twoGroups10000["room"] = {
                "walls": [
                    [-10, 0, 40, 0],
                    [40, 0, 40, 20],
                    [40, 20, -10, 20],
                    [-10, 20, -10, 0],
                ]
            }

            actorList = []
            for i in range(0, 50):
                for j in range(0, 99):
                    actorList.append(
                        {
                            "pos": [29.8 - (i * 0.2), 0.2 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 2,
                            "pathId": 0,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [251, 255, 0],
                        }
                    )
            for i in range(0, 50):
                for j in range(0, 99):
                    actorList.append(
                        {
                            "pos": [0.2 + (i * 0.2), 0.2 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 2,
                            "pathId": 1,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [169, 0, 146],
                        }
                    )

            twoGroups10000["paths"] = [
                {
                    "id": 0,
                    "checkpoints": [
                        [[-10, 5], [-9, 15]],
                    ],
                },
                {
                    "id": 1,
                    "checkpoints": [
                        [[39, 5], [40, 15]],
                    ],
                },
            ]
            twoGroups10000["actors"] = actorList

        elif config[0] == "tightCorner":
            tightCorner = config[1]
            tightCorner["config"] = {
                "width": 9,
                "height": 9,
                "scale": 100,
                "delay": 0,
                "bgColor": [0, 0, 0],
                "wallColor": [255, 255, 255],
                "heatmapEnabled": True,
            }

            tightCorner["room"] = {
                "walls": [
                    [0, 9, 4, 9],
                    [0, 9, 0, 3],
                    [4, 9, 4, 3.5],
                    [4, 3.5, 6, 3.5],
                    [6, 3.5, 6, 1.5],
                    [6, 1.5, 9, 1.5],
                    [0, 3, 5.5, 3],
                    [5.5, 3, 5.5, 1],
                    [5.5, 1, 9, 1],
                ]
            }

            actorList = []
            for i in range(0, 20):
                for j in range(0, 30):
                    actorList.append(
                        {
                            "pos": [0.1 + (i * 0.2), 3.1 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 1.0,
                            "pathId": 0,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [34, 174, 231],
                        }
                    )

            tightCorner["paths"] = [
                {
                    "id": 0,
                    "checkpoints": [
                        [[5.5, 3], [6, 3.5]],
                        [[5.5, 1], [6, 1.5]],
                        [[10, 0.5], [12, 2]],
                    ],
                }
            ]
            tightCorner["actors"] = actorList

        elif config[0] == "laneFiltering":
            laneFiltering = config[1]
            laneFiltering["config"] = {
                "width": 16,
                "height": 9,
                "scale": 100,
                "delay": 0,
                "bgColor": [0, 0, 0],
                "wallColor": [255, 255, 255],
                "heatmapEnabled": False,
            }

            laneFiltering["room"] = {
                "walls": [
                    [0.5, 0.5, 19.5, 0.5],
                    [19.5, 0.5, 19.5, 8.5],
                    [19.5, 8.5, 0.5, 8.5],
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
                    [8.7, 6, 8.7, 8.5],
                ]
            }

            actorList = []
            for i in range(0, 20):
                for j in range(0, 35):
                    actorList.append(
                        {
                            "pos": [1 + (i * 0.2), 1 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 1.5,
                            "pathId": 0,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [169, 0, 146],
                        }
                    )

            laneFiltering["paths"] = [
                {
                    "id": 0,
                    "checkpoints": [
                        [[8.5, 3.1], [8.7, 5.9]],
                        [[18.7, 3.3], [19, 6]],
                    ],
                }
            ]
            laneFiltering["actors"] = actorList

        elif config[0] == "corridorWidening":
            corridorWidening = config[1]
            corridorWidening["config"] = {
                "width": 12,
                "height": 9,
                "scale": 100,
                "delay": 0,
                "bgColor": [0, 0, 0],
                "wallColor": [255, 255, 255],
                "heatmapEnabled": True,
            }

            corridorWidening["room"] = {
                "walls": [
                    [-10, 6, -10, 3],
                    [-10, 3, 4, 3],
                    [4, 3, 6, 0.1],
                    [6, 0.1, 8, 3],
                    [8, 3, 12, 3],
                    [-10, 6, 4, 6],
                    [4, 6, 6, 8.9],
                    [6, 8.9, 8, 6],
                    [8, 6, 12, 6],
                ]
            }

            actorList = []
            for i in range(0, 39):
                for j in range(0, 12):
                    actorList.append(
                        {
                            "pos": [-9.8 + (i * 0.25), 3.1 + (j * 0.25)],
                            "velocity": [0, 0],
                            "desiredSpeed": 5.0,
                            "pathId": 0,
                            "mass": 50,
                            "radius": 0.1,
                            "atDestination": False,
                            "color": [255, 0, 0],
                        }
                    )

            corridorWidening["paths"] = [
                {
                    "id": 0,
                    "checkpoints": [[[20, 3], [22, 6]]],
                }
            ]
            corridorWidening["actors"] = actorList

        elif config[0] == "evacuateRoom":
            evacuateRoom = config[1]
            evacuateRoom["config"] = {
                "width": 9,
                "height": 9,
                "scale": 100,
                "delay": 0,
                "bgColor": [0, 0, 0],
                "wallColor": [255, 255, 255],
                "heatmapEnabled": True,
            }

            evacuateRoom["room"] = {
                "walls": [
                    [0.5, 0.5, 8.5, 0.5],
                    [8.5, 0.5, 8.5, 4.3],
                    [8.5, 4.7, 8.5, 8.5],
                    [8.5, 8.5, 0.5, 8.5],
                    [0.5, 8.5, 0.5, 0.5],
                ]
            }

            actorList = []
            for i in range(0, 20):
                for j in range(0, 35):
                    actorList.append(
                        {
                            "pos": [1 + (i * 0.2), 1 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 1.0,
                            "pathId": 0,
                            "mass": 50,
                            "radius": random.uniform(0.04, 0.06),
                            "atDestination": False,
                            "color": [34, 174, 231],
                        }
                    )
            evacuateRoom["paths"] = [
                {
                    "id": 0,
                    "checkpoints": [
                        [[8.3, 4.3], [8.7, 4.7]],
                        [[15, 3.5], [16, 4.5]],
                    ],
                }
            ]
            evacuateRoom["actors"] = actorList

        elif config[0] == "evacuateRoom10000":
            evacuateRoom10000 = config[1]
            evacuateRoom10000["config"] = {
                "width": 30,
                "height": 19,
                "scale": 50,
                "delay": 0,
                "bgColor": [0, 0, 0],
                "wallColor": [255, 255, 255],
                "heatmapEnabled": True,
            }

            evacuateRoom10000["room"] = {
                "walls": [
                    [0.5, 0.5, 29.5, 0.5],
                    [29.5, 0.5, 29.5, 18.5],
                    [29.5, 18.5, 0.5, 18.5],
                    [0.5, 18.5, 0.5, 9.7],
                    [0.5, 9.3, 0.5, 0.5],
                ]
            }

            actorList = []
            for i in range(0, 120):
                for j in range(0, 85):
                    actorList.append(
                        {
                            "pos": [5.2 + (i * 0.2), 1 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 2.0,
                            "pathId": 0,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [34, 174, 231],
                        }
                    )
            evacuateRoom10000["paths"] = [
                {
                    "id": 0,
                    "checkpoints": [
                        [[0.3, 9.3], [0.7, 9.7]],
                        [[-11, 9], [-10, 10]],
                    ],
                }
            ]
            evacuateRoom10000["actors"] = actorList

        elif config[0] == "evacuateRoom50000":
            evacuateRoom50000 = config[1]
            evacuateRoom50000["config"] = {
                "width": 100,
                "height": 50,
                "scale": 10,
                "delay": 0,
                "bgColor": [0, 0, 0],
                "wallColor": [255, 255, 255],
                "heatmapEnabled": True,
            }

            evacuateRoom50000["room"] = {
                "walls": [
                    [0.5, 0.5, 99.5, 0.5],
                    [99.5, 0.5, 99.5, 49.5],
                    [99.5, 49.5, 0.5, 49.5],
                    [0.5, 49.5, 0.5, 25],
                    [0.5, 24, 0.5, 0.5],
                ]
            }

            actorList = []
            for i in range(0, 250):
                for j in range(0, 200):
                    actorList.append(
                        {
                            "pos": [40 + (i * 0.2), 1 + (j * 0.2)],
                            "velocity": [0, 0],
                            "desiredSpeed": 2.0,
                            "pathId": 0,
                            "mass": 50,
                            "radius": 0.05,
                            "atDestination": False,
                            "color": [34, 174, 231],
                        }
                    )
            evacuateRoom50000["paths"] = [
                {
                    "id": 0,
                    "checkpoints": [
                        [[0.3, 24], [0.7, 25]],
                        [[-11, 24], [-10, 25]],
                    ],
                }
            ]
            evacuateRoom50000["actors"] = actorList

    # Write configurations to JSON files
    for config in toGenerate:
        with open("../input/" + config[0] + ".json", "w") as out:
            json.dump(config[1], out, ensure_ascii=False, indent=4)
        print("Finished Generating ../input/" + config[0] + ".json")


if __name__ == "__main__":
    animationThread = Thread(target=workingAnimation)
    animationThread.start()
    main(sys.argv[1:])
    complete = True
