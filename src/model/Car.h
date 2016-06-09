#ifndef ROADTRAFFICSIMULATOR_CAR_H
#define ROADTRAFFICSIMULATOR_CAR_H

#include "Lane.h"

class Trajectory;

class Car {
private:
    int id;
    int color;
    double speed;
    double width;
    double length;
    static constexpr double maxSpeed = 30;
    static constexpr double distanceGap = 2;
    static constexpr double timeHeadway = 1.5;
    static constexpr double maxAcceleration = 1;
    static constexpr double maxDeceleration = 3;
    bool alive = true;
    Lane *nextLane;
    Trajectory *trajectory;
public:
    Car(Lane &lane, double position);
    double getAcceleration();
    void move(double delta);
    Road* pickNextRoad();
    Lane* pickNextLane();
    Lane* popNextLane();
    void release();
    Point<double> getCoordinates();
    double getDirection();

    inline double getSpeed() {
        return speed;
    }

    inline void setSpeed(double speed) {
        this->speed = speed;
    }

    inline double getLength() {
        return length;
    }

    inline double getWidth() {
        return width;
    }

    inline Lane* getNextLane() const {
        return nextLane;
    }

    inline bool isAlive() const {
        return alive;
    }

    inline int getId() const {
        return id;
    }

    inline int getColor() const {
        return color;
    }
};

#endif //ROADTRAFFICSIMULATOR_CAR_H
