#include <c++/cassert>
#include "Lane.h"
#include "LanePosition.h"

Lane::Lane(const Segment<double> &sourceSegment, const Segment<double> &targetSegment, Road &road) {
    this->sourceSegment = Segment<double>(sourceSegment);
    this->targetSegment = Segment<double>(targetSegment);
    this->road = &road;
    update();
}

Lane::Lane() {
    sourceSegment = Segment<double>();
    targetSegment = Segment<double>();
    update();
}

void Lane::update() {
    middleLine = Segment<double>(sourceSegment.getCenter(), targetSegment.getCenter());
}

void Lane::setAdjacents(Lane *leftAdjacent, Lane *rightAdjacent, Lane *leftmostAdjacent, Lane *rightmostAdjacent) {
    this->leftAdjacent = leftAdjacent;
    this->rightAdjacent = rightAdjacent;
    this->leftmostAdjacent = leftmostAdjacent;
    this->rightmostAdjacent = rightmostAdjacent;
}

void Lane::addCarPosition(LanePosition *carPosition) {
    carsPositions.insert(carPosition);
}

void Lane::removeCarPosition(LanePosition *carPosition) {
    carsPositions.erase(carPosition);
}

LanePosition* Lane::getNext(LanePosition *carPosition) {
    LanePosition *best = NULL;
    double bestDistance = std::numeric_limits<double>::max();
    for (auto &entry : carsPositions) {
        assert(!entry->isFree());
        double distance = entry->getPosition() - carPosition->getPosition();
        if (distance > 0 && distance < bestDistance && !entry->isFree()) {
            bestDistance = distance;
            best = entry;
        }
    }
    return best;
}


