#ifndef ROADTRAFFICSIMULATOR_TRAJECTORY_H
#define ROADTRAFFICSIMULATOR_TRAJECTORY_H

#include "src/geometry/Curve.h"
#include "Car.h"
#include "LanePosition.h"

class Trajectory {
private:
    LanePosition *current;
    LanePosition *next;
    bool changingLines;
    Car &car;
    Curve<double> *curve;
    double curvePosition;
    Curve<double> getAdjacentLaneChangeCurve();
    void startChangingLanes(Lane &lane, double nextPosition);
    Lane* finishChangingLanes();

public:
    Trajectory(Car &car, Lane &lane, double position);
    std::pair<Car*, double> getNextCarDistance();
    double getDistanceToStopLine();
    bool isValidTurn();
    bool canEnterIntersection();
    Lane* moveForward(double distance);
    void changeLane(Lane &lane);
    void release();

    inline double getLaneLength() {
        if (curve) {
            return curve->getLength();
        }
        return current->getLane()->getLength();
    }

    inline double getAbsolutePosition() {
        if (curve) {
            return curvePosition;
        }
        return current->getPosition();
    }

    inline double getRelativePosition() {
        return getAbsolutePosition() / getLaneLength();
    }

    inline Point<double> getCoordinates() {
        if (curve) {
            return curve->getPoint(getRelativePosition());
        }
        return current->getCoordinates();
    }

    inline double getDirection() {
        if (curve) {
            return curve->getDirection(getRelativePosition());
        }
        return current->getLane()->getDirection();
    }

    inline Intersection* getNextIntersection() {
        return current->getLane()->getRoad()->getTarget();
    }

    inline Intersection* getPreviousIntersection() {
        return current->getLane()->getRoad()->getSource();
    }

    inline double getDistanceToIntersection() {
        if (changingLines) {
            return std::numeric_limits<double>::max();
        }
        return std::max(0.0, current->getLane()->getLength() - car.getLength() / 2 - current->getPosition());
    }

    inline bool timeToMakeTurn(double plannedStep = 0) {
        return getDistanceToIntersection() <= plannedStep;
    }

    inline bool isChangingLines() {
        return changingLines;
    }

    inline LanePosition* getCurrent() {
        return current;
    }
};


#endif //ROADTRAFFICSIMULATOR_TRAJECTORY_H
