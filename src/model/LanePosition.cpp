#include "LanePosition.h"
#include "Counter.h"

LanePosition::LanePosition(Car &car): car(&car) {
    lane = NULL;
    position = 0;
    id = Counter::getInstance().getId();
    free = true;
}

LanePosition::LanePosition(Car &car, Lane &lane, double position) {
    this->position = position;
    this->car = &car;
    this->lane = &lane;
    id = Counter::getInstance().getId();
    free = true;
}

LanePosition::LanePosition() {
    position = 0;
}

std::pair<Car*, double> LanePosition::getNextCarDistance() {
    LanePosition *next = getNext();
    if (!next) {
        return std::make_pair((Car*) NULL, std::numeric_limits<double>::max());
    }
    return std::pair<Car*, double>(next->car,
                                   (next->position - next->car->getLength() / 2) - (position + car->getLength() / 2));
}

LanePosition* LanePosition::getNext() {
    if (!lane || free) {
        return NULL;
    }
    return lane->getNext(this);
}

void LanePosition::acquire() {
    if (lane) {
        free = false;
        lane->addCarPosition(this);
    }
}

void LanePosition::release() {
    if (!free && lane) {
        free = true;
        lane->removeCarPosition(this);
    }
}