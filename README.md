# RoadTrafficSimulator

### Overview

Road traffic simulation system

### Sources

* ```geometry``` directory: some easy geometry stuff, like Point, Segment, Rectangle and Bezier Curve
* ```model``` directory: model implementation 
* ```view``` directory: visualization (with help of Qt framework, QGraphicsScene/QGraphicsView widgets were used).
* ```algo``` directory: implementation of 4 optimization algorithms (as metric a sum of car average speeds is used): 
	* Monte-Carlo bruteforce method
	* Simulated Annealing method
	* Genetic algorithms method
	* Cross-entropy method

### Build

* Install MinGW (4.8 or later is required)
* Install Qt (5.3 or later is required)
* Install CMake (3.5.1 or later is required)
* Add paths to all these programs to ```PATH``` system variable
* Run ```./build.sh```
* Executable file will be in ```build``` directory

