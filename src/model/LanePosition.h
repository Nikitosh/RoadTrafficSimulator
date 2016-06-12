#ifndef ROADTRAFFICSIMULATOR_LANEPOSITION_H
#define ROADTRAFFICSIMULATOR_LANEPOSITION_H

#include "Car.h"
#include "Lane.h"

class LanePosition {
private:
    Car *car;
    bool free;
    double position;
    int id;
    Lane *lane;

public:
    LanePosition(Car &car);
    LanePosition(Car &car, Lane &lane, double position);
    LanePosition();
    std::pair<Car*, double> getNextCarDistance();
    LanePosition* getNext() const;
    void acquire();
    void release();

    inline Lane* getLane() const {
        return lane;
    }

    inline void setLane(Lane *lane) {
        this->lane = lane;
    }

    inline Point<double> getCoordinates() const {
        return lane->getMiddleLine().getPoint(getRelativePosition());
    }

    inline double getRelativePosition() const {
        return position / lane->getLength();
    }

    inline double getPosition() const {
        return position;
    }

    inline void setPosition(double position) {
        this->position = position;
    }

    inline int getId() const {
        return id;
    }

    inline bool isFree() const {
        return free;
    }

    inline Car* getCar() const {
        return car;
    }
};

#endif //ROADTRAFFICSIMULATOR_LANEPOSITION_H
