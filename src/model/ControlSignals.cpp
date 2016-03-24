#include <c++/cstdlib>
#include "ControlSignals.h"

ControlSignals::ControlSignals(int roadsNumber) {
    flipMultiplier = rand() * 1.0 / RAND_MAX;
    phaseOffset = 100 * rand() * 1.0 / RAND_MAX;
    timeAccumulator = phaseOffset;
    stateNum = 0;
    this->roadsNumber = roadsNumber;
}