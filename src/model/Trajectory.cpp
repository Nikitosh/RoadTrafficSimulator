#include "Trajectory.h"
#include "Intersection.h"

Trajectory::Trajectory(Car &car, Lane &lane, double position) : car(car) {
    current = new LanePosition(car, lane, position);
    current->acquire();
    next = new LanePosition(car);
    changingLines = false;
    curve = NULL;
}

Trajectory::~Trajectory() {
    delete current;
    delete next;
}

std::pair<Car *, double> Trajectory::getNextCarDistance() {
    auto a = current->getNextCarDistance();
    auto b = next->getNextCarDistance();
    if (a.second < b.second) {
        return a;
    }
    return b;
}

double Trajectory::getDistanceToStopLine() {
    if (!canEnterIntersection()) {
        return getDistanceToIntersection();
    }
    return std::numeric_limits<double>::max();
}

Lane *Trajectory::moveForward(double distance) {
    distance = std::max(distance, 0.0);
    current->setPosition(current->getPosition() + distance);
    next->setPosition(next->getPosition() + distance);
    curvePosition += distance;
    if (timeToMakeTurn() && canEnterIntersection() && isValidTurn()) {
        startChangingLanes(*car.popNextLane(), 0);
    }
    if (changingLines) {
        double curveRelativePosition = curvePosition / curve->getLength();
        double gap = std::min(2 * car.getLength(), curve->getLength() * 1.5 / 3);
        if (curvePosition > gap && !current->isFree()) {
            current->release();
        }
        if (next->isFree() && curvePosition + gap > curve->getLength()) {
            next->acquire();
        }
        if (curveRelativePosition >= 1) {
            return finishChangingLanes();
        }
    }
    if (current->getLane() && !changingLines && !car.getNextLane()) {
        return car.pickNextLane();
    }
    return NULL;
}

void Trajectory::changeLane(Lane &lane) {
    double nextPosition = current->getPosition() + 3 * car.getLength();
    startChangingLanes(lane, nextPosition);
}

void Trajectory::release() {
    if (current) {
        current->release();
    }
    if (next) {
        next->release();
    }
}

Curve<double> Trajectory::getAdjacentLaneChangeCurve() {
    Point<double> p1 = current->getLane()->getPoint(current->getRelativePosition());
    Point<double> p2 = next->getLane()->getPoint(next->getRelativePosition());
    double distance = (p2 - p1).getLength();
    Point<double> direction1 = current->getLane()->getMiddleLine().getVector().getNormalizedPoint() * distance * 0.3;
    Point<double> control1 = p1 + direction1;
    Point<double> direction2 = next->getLane()->getMiddleLine().getVector().getNormalizedPoint() * distance * 0.3;
    Point<double> control2 = p2 - direction2;
    return Curve<double>(p1, p2, control1, control2);
}

void Trajectory::startChangingLanes(Lane &lane, double nextPosition) {
    changingLines = true;
    next->setLane(&lane);
    next->setPosition(nextPosition);
    curve = new Curve<double>(getAdjacentLaneChangeCurve());
    curvePosition = 0;
    next->setPosition(nextPosition - curve->getLength());
}

Lane *Trajectory::finishChangingLanes() {
    changingLines = false;
    delete current;
    current = next;
    next = new LanePosition(car);
    delete curve;
    curve = NULL;
    curvePosition = 0;
    return current->getLane();
}

bool Trajectory::isValidTurn() {
    return true;
}

bool Trajectory::canEnterIntersection() {
    if (!car.getNextLane()) {
        return true;
    }
    int turnNumber = current->getLane()->getTurnDirection(car.getNextLane());
    int sideId = current->getLane()->getRoad()->getTargetSideId();
    return getNextIntersection()->getTrafficLight()->getState(sideId)[turnNumber] - '0';
}

