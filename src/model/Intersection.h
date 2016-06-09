#ifndef ROADTRAFFICSIMULATOR_INTERSECTION_H
#define ROADTRAFFICSIMULATOR_INTERSECTION_H

#include "src/geometry/Rectangle.h"
#include "Road.h"
#include "ControlSignals.h"

class Intersection {
private:
    Rectangle<double> rectangle;
    std::vector<Road*> inRoads;
    std::vector<Road*> outRoads;
    ControlSignals *controlSignals;
    int id;

public:
    Intersection(const Rectangle<double> &rectangle);
    Intersection(const Intersection &intersection);
    void update() const;
    void addInRoad(Road *road);
    void addOutRoad(Road *road);

    inline ControlSignals* getControlSignals() const {
        return controlSignals;
    }

    inline Rectangle<double> getRectangle() const {
        return rectangle;
    }

    inline int getRoadsNumber() const {
        return outRoads.size();
    }

    inline Road* getRoad(int index) const {
        return outRoads[index];
    }
};

#endif //ROADTRAFFICSIMULATOR_INTERSECTION_H
