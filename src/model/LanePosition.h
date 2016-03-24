#ifndef ROADTRAFFICSIMULATOR_LANEPOSITION_H
#define ROADTRAFFICSIMULATOR_LANEPOSITION_H

#include "Car.h"
#include "Lane.h"

class LanePosition {
private:
    Car *car;
    bool isFree;
    double position;
    int id;
    Lane *lane;

public:
    LanePosition(Car &car, Lane &lane, double position);
    LanePosition();
    std::pair<Car*, double> getNextCarDistance();
    LanePosition* getNext() const;
    void acquire();
    void release();

    inline double getRelativePosition() const {
        return position / lane->getLength();
    }

    inline double getPosition() const {
        return position;
    }

    inline int getId() const {
        return id;
    }
};

#endif //ROADTRAFFICSIMULATOR_LANEPOSITION_H
