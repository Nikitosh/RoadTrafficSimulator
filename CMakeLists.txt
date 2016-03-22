cmake_minimum_required(VERSION 3.4)
project(RoadTrafficSimulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/geometry/Point.h src/geometry/Rectangle.h)
add_executable(RoadTrafficSimulator ${SOURCE_FILES})