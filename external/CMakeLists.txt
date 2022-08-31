# Copyright (C) 2022 Codeplay Software Ltd.

include("${CMAKE_SOURCE_DIR}/vendor/rapidjson.cmake")

add_library(external Actor.cpp 
                     Room.cpp 
                     Path.cpp 
                     MathHelper.cpp 
                     DifferentialEq.cpp 
                     Heatmap.cpp 
                     ParseInputFile.cpp 
                     RandomNumber.cpp 
                     Stats.cpp
            )

target_include_directories(external PUBLIC ${PROJECT_BINARY_DIR} ${RAPIDJSON_INCLUDE_DIR})

add_dependencies(external rapidjson)
