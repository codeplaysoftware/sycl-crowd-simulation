cmake_minimum_required (VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(crowd-simulation)

set(CMAKE_C_COMPILER /home/sami/sycl_workspace/llvm/build/bin/clang)
set(CMAKE_CXX_COMPILER /home/sami/sycl_workspace/llvm/build/bin/clang++)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(crowdsim src/main.cpp)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fsycl -fsycl-targets=spir64-gen")

add_subdirectory(external)

target_link_libraries(crowdsim PUBLIC ${SDL2_LIBRARIES} external) 
target_include_directories(crowdsim PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/external")
