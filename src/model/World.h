#ifndef ROADTRAFFICSIMULATOR_WORLD_H
#define ROADTRAFFICSIMULATOR_WORLD_H

#include "Road.h"
#include "Car.h"
#include "Intersection.h"

class World {
private:
    double time;
    int carsNumber;
    std::vector<Car*> cars;
    std::vector<Intersection*> intersections;
    std::vector<Road*> roads;
public:
    void read(const char *path);
    void onTick(double delta);
    void refreshCars();
    void addRoad(Road *road);
    void addRandomCar();
    void removeRandomCar();
    void addIntersection(Intersection *intersection);

    inline std::vector<Intersection*> getIntersections() {
        return intersections;
    }

    inline std::vector<Car*> getCars() {
        return cars;
    }

    inline int getCarsNumber() {
        return carsNumber;
    }
};


#endif //ROADTRAFFICSIMULATOR_WORLD_H
