cmake_minimum_required (VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(crowd-simulation)

set(CMAKE_C_COMPILER /home/sami/sycl_workspace/llvm/build/bin/clang)
set(CMAKE_CXX_COMPILER /home/sami/sycl_workspace/llvm/build/bin/clang++)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(crowdsim src/main.cpp)

set(SYCL_BACKEND "SYCL_BACKEND" CACHE STRING "Backend chosen by the user at CMake configure time")
set_property(CACHE SYCL_BACKEND PROPERTY STRINGS spir cuda hip)

if(SYCL_BACKEND STREQUAL hip)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fsycl -fsycl-targets=amdgcn-amd-amdhsa")
elseif(SYCL_BACKEND STREQUAL cuda)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsycl -fsycl-targets=nvptx64-nvidia-cuda")
else()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsycl -fsycl-targets=spir64")
endif()

add_subdirectory(external)

target_link_libraries(crowdsim PUBLIC ${SDL2_LIBRARIES} external) 
target_include_directories(crowdsim PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/external")
