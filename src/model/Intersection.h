#ifndef ROADTRAFFICSIMULATOR_INTERSECTION_H
#define ROADTRAFFICSIMULATOR_INTERSECTION_H

#include "src/geometry/Rectangle.h"
#include "Road.h"
#include "TrafficLight.h"

class Intersection {
private:
    Rectangle<double> rectangle;
    std::vector<Road*> inRoads;
    std::vector<Road*> outRoads;
    TrafficLight *trafficLight;
    int id;

public:
    Intersection(const Rectangle<double> &rectangle);
    Intersection(const Intersection &intersection);
    ~Intersection();
    void update() const;
    void addInRoad(Road *road);
    void addOutRoad(Road *road);

    inline TrafficLight* getTrafficLight() const {
        return trafficLight;
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
