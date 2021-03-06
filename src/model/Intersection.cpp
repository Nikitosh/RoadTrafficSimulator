#include "Intersection.h"
#include "Counter.h"

Intersection::Intersection(const Rectangle<double> &rectangle): rectangle(rectangle) {
    id = Counter::getInstance().getId();
    trafficLight = new TrafficLight(outRoads.size());
}

Intersection::Intersection(const Intersection &intersection): rectangle(intersection.rectangle), id(intersection.id) {
}

Intersection::~Intersection() {
    delete trafficLight;
}

void Intersection::update() const {
    for (Road *road : inRoads) {
        road->update();
    }
    for (Road *road : outRoads) {
        road->update();
    }
}

void Intersection::addInRoad(Road *road) {
    inRoads.push_back(road);
}

void Intersection::addOutRoad(Road *road) {
    outRoads.push_back(road);
    trafficLight->incRoadsNumber();
}

