# SYCL-Crowd-Simulation

SYCL GPU-accelerated crowd simulation engine based on Helbing et. al.'s social force model.

Dirk Helbing introduced the social force model in a paper in 1995, aimed at modelling the behaviour of crowds using Langevin equations. He proposed a refined model in a 2000 paper, "Simulating Dynamical Features of Escape Panic". Helbing posits that human behaviour in large crowds is determined by three component forces: A personal impulse towards one's destination, the cumulative force exerted by neighbouring people, and the repulsive force of any nearby walls. Together, these forces form the basis of a differential equation which can subsequently be integrated in order to calculate the actor's velocity.

## Features

- Performantly simulate tens of thousands of actors in real time
- Define different crowds with different characteristics and different destinations 
- Define rooms and obstacles
- Fully configurable environments (see [Input Format](#input-format))
- Record and graph simulation metrics
- Target and build for multiple SYCL supported backends
- Apply a force heatmap across actors
- The simulation kernels may be used separately from the GUI

## Dependencies

- The [DPC++ compiler](https://intel.github.io/llvm-docs/GetStartedGuide.html) is required to compile SYCL code
- If targeting the DPC++ CUDA backend, the [CUDA runtime](https://intel.github.io/llvm-docs/GetStartedGuide.html#build-dpc-toolchain-with-support-for-nvidia-cuda) is required
- If targeting the DPC++ OpenCL backend, an [OpenCL runtime](https://intel.github.io/llvm-docs/GetStartedGuide.html#install-low-level-runtime) is require
- [CMake](https://cmake.org/install/) is used for build configuration
- Graphics are rendered with [SDL2](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/linux/index.php), installed with apt: `$ apt install libsdl2-dev`
- Python is needed to run scripts
- Graphs are plotted using matplotlib, installed via pip: `$ pip install matplotlib`
- To run simulations in headless mode and record video output, install [xvfb](https://www.x.org/releases/X11R7.6/doc/man/man1/Xvfb.1.xhtml) and [ffmpeg](https://ffmpeg.org/download.html) using apt

## Building

Build configuration is carried out using CMake.

The option `-DSYCL_BACKEND` allows you to select which backend to build for (spir, cuda or hip). By default, it builds for spir.

When enabled, the `-DPROFILING_MODE` option builds a headless version which can be run without the SDL dependency.

When enabled, the `-DSTATS` option will collect metrics whilst the simulation is running. Results are written to `output/outputStats.txt`. Graphs can be produced from these metrics by running the python script [PlotGraphs.py](scripts/PlotGraphs.py).

By default, CMake should generate example input files by running [InputFileGenerator.py](scripts/InputFileGenerator.py) when generating the project makefiles.

The `crowdsim` executable takes an input configuration JSON as a command line argument.

```
$ git clone https://github.com/codeplaysoftware/sycl-crowd-simulation.git
$ cd crowd-simulation
$ mkdir build && cd build
$ cmake -DCMAKE_CXX_COMPILER=path/to/llvm/build/bin/clang++ -DSYCL_BACKEND=spir -DPROFILING_MODE=off -DSTATS=on ..
$ cmake --build .
$ ./crowdsim ../input/evacuateRoom.json
```

## Input Format

Below is an annotated example input file which creates a room containing two actors with two different destinations.

```
{
  "config": {                                     <-- Configure environment
    "width": 9,
    "height": 9,
    "scale": 100,                                 
    "delay": 0,
    "bgColor": [0, 0, 0],                         
    "wallColor": [255, 255, 255],
    "heatmapEnabled": true                        <-- Flag denoting whether 
  },                                                  the heatmap should be 
                                                      applied to actors
  "room": {                                       
    "walls": [
      [0.5, 0.5, 8.5, 0.5],                       <-- Walls are defined via their
      [8.5, 0.5, 8.5, 8.5],                           start and end points
      [8.5, 8.5, 0.5, 8.5],
      [0.5, 8.5, 0.5, 0.5]
    ]                                             
  },
                                                  
  "actors": [                                     <-- Populate environment with
    {                                                 actors
      "pos": [3.4, 5.6],
      "velocity": [0.0123, 0.0567],               
      "desiredSpeed": 0.6,
      "pathId": 0,                                
      "mass": 50,
      "radius": 0.05,                             
      "atDestination": false,
      "color": [255, 0, 0],                       
      "heatmapEnabled": true 
    },
    {
      "pos": [0.7, 7.3],                          
      "velocity": [0.0789, 0.0444],
      "desiredSpeed": 0.6,                        
      "pathId": 1,
      "mass": 45,                                 
      "radius": 0.06,
      "atDestination": false,                     
      "color": [0, 255, 0],
      "heatmapEnabled": true                      
    }
  ],                                              

  "paths": [                                      
    {                                             
      "id": 0,                                    <-- Each path has a unique id, 
      "checkpoints": [[[7.9, 5.6], [8.1, 5.8]]]       referenced by any actor which
    },                                                takes that path
    {
      "id": 1,
      "checkpoints": [[[7.9, 5.6], [8.1, 5.8]],   <-- Paths consist of checkpoints
                      [[1.5, 2], [1.7, 2.2]]]         Each checkpoint is a rectangular
    }                                                 region defined as:
  ]                                                   [[minX, minY], [maxX, maxY]]
}
```

Larger input configurations can be generated with python scripts, as demonstrated in [InputFileGenerator.py](scripts/InputFileGenerator.py).

The social force model itself can be tweaked by altering the constexprs defined in [DifferentialEq.hpp](external/DifferentialEq.hpp). For example, in simulations involving large numbers of actors (10,000+), the values `WALLAi` and `PEOPLEAi` will need to be increased to prevent any clipping issues.

## Benchmarks

Ran on NVIDIA Titan RTX with `PROFLILING_MODE` enabled and `STATS` disabled.

|  | **500 iterations<br>1000 actors** | **500 iterations<br>10,000 actors** | **500 iterations<br>50,000 actors** |
|---|---|---|---|
| **Average kernel duration** | 0.0000321078s | 0.0000797784s | 0.00040853s |
| **Total execution time** | 0.180193s | 2.29063s | 20.75141s |

## Citations

- Helbing, D., Farkas, I. & Vicsek, T. Simulating dynamical features of escape panic. Nature 407, 487–490 (2000). https://doi.org/10.1038/35035023
- Marsaglia, G. (2003). Xorshift RNGs. Journal of Statistical Software, 8(14), 1–6. https://doi.org/10.18637/jss.v008.i14
