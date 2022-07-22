cmake_minimum_required (VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(crowd-simulation)

set(CMAKE_C_COMPILER /home/sami/sycl_workspace/llvm/build/bin/clang)
set(CMAKE_CXX_COMPILER /home/sami/sycl_workspace/llvm/build/bin/clang++)

OPTION(PROFILING_MODE "Enable profiling" off)
if(PROFILING_MODE)
    add_definitions(-DPROFILING_MODE)
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

OPTION(STATS "Run in stats mode" off)
if (STATS)
    add_definitions(-DSTATS)
endif()

set(SYCL_BACKEND "SYCL_BACKEND" CACHE STRING "Backend chosen by the user at CMake configure time")
set_property(CACHE SYCL_BACKEND PROPERTY STRINGS spir cuda hip)

if(SYCL_BACKEND STREQUAL hip)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fsycl -fsycl-targets=amdgcn-amd-amdhsa")
elseif(SYCL_BACKEND STREQUAL cuda)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsycl -fsycl-targets=nvptx64-nvidia-cuda")
else()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsycl -fsycl-targets=spir64")
endif()

find_package(Python QUIET)
if(Python_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/input/InputFileGenerator.py")
    execute_process(COMMAND ${Python_EXECUTABLE} ../input/InputFileGenerator.py)
else()
    message(WARNING "Unable to generate input configuration files")
endif()

add_executable(crowdsim src/main.cpp)

add_subdirectory(external)

if (PROFILING_MODE)
    target_link_libraries(crowdsim PUBLIC external) 
else()
    target_link_libraries(crowdsim PUBLIC ${SDL2_LIBRARIES} external)
endif()
target_include_directories(crowdsim PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/external")
