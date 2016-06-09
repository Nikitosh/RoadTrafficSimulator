#include <c++/cstdlib>
#include "ControlSignals.h"

ControlSignals::ControlSignals(int roadsNumber) {
    flipMultiplier = rand() * 1.0 / RAND_MAX;
    timeAccumulator = 0;
    stateNum = 0;
    this->roadsNumber = roadsNumber;
}