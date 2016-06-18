#include <c++/ctime>

#include "Car.h"
#include "Counter.h"
#include "Trajectory.h"
#include "Intersection.h"

Car::Car(Lane &lane, double position) {
    id = Counter::getInstance().getId();
    color = rand() % Settings::getInstance().getColorNumber();
    speed = 0;
    length = Settings::getInstance().getCarLength();
    width = Settings::getInstance().getCarWidth();
    alive = true;
    nextLane = NULL;
    trajectory = new Trajectory(*this, lane, position);
}

Car::~Car() {
    delete trajectory;
}

void Car::move(double delta) {
    double acceleration = getAcceleration();
    speed += acceleration * delta;
    speed = std::max(speed, 0.);
    if (!trajectory->isChangingLines() && nextLane) {
        Lane *currentLane = trajectory->getCurrent()->getLane();
        int turnNumber = currentLane->getTurnDirection(nextLane);
        Lane *preferredLane = currentLane;
        if (turnNumber == 0) {
            preferredLane = currentLane->getLeftmostAdjacent();
        } else if (turnNumber == 2) {
            preferredLane = currentLane->getRightmostAdjacent();
        }
        if (preferredLane != currentLane && preferredLane != NULL) {
            trajectory->changeLane(*preferredLane);
        }
    }
    double step = speed * delta + 0.5 * acceleration * delta * delta;
    if (trajectory->getNextCarDistance().second < step) {
        //something went wrong
    }
    if (trajectory->timeToMakeTurn(step)) {
        if (nextLane == NULL) {
            trajectory->release();
            alive = false;
            return;
        }
    }
    trajectory->moveForward(step);
    time += delta;
    distance += std::max(step, 0.);
}

Lane* Car::pickNextLane() {
    nextLane = NULL;
    Road *nextRoad = pickNextRoad();
    if (nextRoad == NULL) {
        return NULL;
    }
    int turnNumber = trajectory->getCurrent()->getLane()->getRoad()->getTurnDirection(nextRoad);
    int laneNumber = 0;
    if (turnNumber == 0) {
        laneNumber = nextRoad->getLanesNumber() - 1;
    } else {
        laneNumber = rand() % nextRoad->getLanesNumber();
    }
    nextLane = nextRoad->getLane(laneNumber);
    return nextLane;
}

Lane* Car::popNextLane() {
    Lane *lastLane = nextLane;
    nextLane = NULL;
    return lastLane;
}

Point<double> Car::getCoordinates() {
    return trajectory->getCoordinates();
}

double Car::getDirection() {
    return trajectory->getDirection();
}

double Car::getAcceleration() {
    auto nextCarDistance = trajectory->getNextCarDistance();
    double distanceToNextCar = std::max(0.0, nextCarDistance.second);
    double a = maxAcceleration;
    double b = maxDeceleration;
    double deltaSpeed = 0;
    if (nextCarDistance.first != NULL) {
        deltaSpeed = speed - nextCarDistance.first->getSpeed();
    }
    double freeRoadCoefficient = pow(speed / maxSpeed, 4);
    double distanceGap = this->distanceGap;
    double timeGap = speed * timeHeadway;
    double breakGap = speed * deltaSpeed / (2 * sqrt(a * b));
    double safeDistance = distanceGap + timeGap + breakGap;
    double busyRoadCoefficient = pow(safeDistance / distanceToNextCar, 2);
    double safeIntersectionDistance = 1 + timeGap + pow(speed, 2) / (2 * b);
    double intersectionCoefficient = pow(safeIntersectionDistance / trajectory->getDistanceToStopLine(), 2);
    return maxAcceleration * (1 - freeRoadCoefficient - busyRoadCoefficient - intersectionCoefficient);
}

Road* Car::pickNextRoad() {
    Intersection *intersection = trajectory->getNextIntersection();
    Lane *currentLane = trajectory->getCurrent()->getLane();
    int roadsNumber = intersection->getRoadsNumber();
    std::vector<Road*> possibleRoads;
    for (int i = 0; i < roadsNumber; i++) {
        if (intersection->getRoad(i)->getTarget() != currentLane->getRoad()->getSource()) {
            possibleRoads.push_back(intersection->getRoad(i));
        }
    }
    if (possibleRoads.size() == 0) {
        return NULL;
    }
    return possibleRoads[rand() % possibleRoads.size()];
}

