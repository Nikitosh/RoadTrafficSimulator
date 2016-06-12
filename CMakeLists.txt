cmake_minimum_required(VERSION 3.4)
project(RoadTrafficSimulator)

set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.3/mingw482_32)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)

set(SOURCE_FILES src/main.cpp src/geometry/Point.h src/geometry/Rectangle.h src/geometry/Curve.h src/model/Counter.cpp src/model/Counter.h src/model/Intersection.cpp src/model/Intersection.h src/model/Road.cpp src/model/Road.h src/model/ControlSignals.cpp src/model/ControlSignals.h src/model/Lane.cpp src/model/Lane.h src/model/Settings.cpp src/model/Settings.h src/model/LanePosition.cpp src/model/LanePosition.h src/model/Car.cpp src/model/Car.h src/model/Trajectory.cpp src/model/Trajectory.h src/model/World.cpp src/model/World.h src/view/MainWindow.cpp src/view/MainWindow.h src/view/View.cpp src/view/View.h)
add_executable(RoadTrafficSimulator ${SOURCE_FILES})
target_link_libraries(RoadTrafficSimulator Qt5::Widgets Qt5::Gui)
