cmake_minimum_required(VERSION 3.4)
project(RoadTrafficSimulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/geometry/Point.h src/geometry/Rectangle.h src/geometry/Curve.h src/model/Counter.cpp src/model/Counter.h src/model/Intersection.cpp src/model/Intersection.h src/model/Road.cpp src/model/Road.h src/model/ControlSignals.cpp src/model/ControlSignals.h src/model/Lane.cpp src/model/Lane.h src/model/Settings.cpp src/model/Settings.h src/model/LanePosition.cpp src/model/LanePosition.h src/model/Car.cpp src/model/Car.h)
add_executable(RoadTrafficSimulator ${SOURCE_FILES})