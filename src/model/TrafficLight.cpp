#include <c++/cstdlib>
#include "TrafficLight.h"

TrafficLight::TrafficLight(int roadsNumber) {
    this->roadsNumber = roadsNumber;
    for (int i = 0; i < 2; i++) {
        flipIntervals[i] = 0.1 + rand() * 1.0 / RAND_MAX;
    }
    timeAccumulator = 0;
    stateNum = 0;
}