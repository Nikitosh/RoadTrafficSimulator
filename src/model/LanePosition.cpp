#include "LanePosition.h"

LanePosition::LanePosition(Car &car, Lane &lane, double position) {
    this->position = position;
    this->car = &car;
    this->lane = &lane;
}

LanePosition::LanePosition() {
    position = 0;
}

LanePosition* LanePosition::getNext() const {
    if (!lane || isFree) {
        return NULL;
    }
    return lane->getNext(*this);
}

void LanePosition::acquire() {
    isFree = false;
    lane->addCarPosition(*this);
}

void LanePosition::release() {
    if (!isFree) {
        isFree = true;
        lane->removeCarPosition(*this);
    }
}

std::pair<Car*, double> LanePosition::getNextCarDistance() {
    LanePosition *next = getNext();
    if (!next) {
        return std::make_pair((Car*) NULL, std::numeric_limits<double>::max());
    }
    return std::pair<Car *, double>();
}
