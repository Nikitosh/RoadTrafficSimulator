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
    double summaryAverageSpeed = 0;
    int deadCarsNumber = 0;

public:
    static constexpr int TURN[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    ~World();
    static World* generateFullMap(int h, int w, int carsNumber);
    void clear();
    void read(const char *path);
    void onTick(double delta);
    void addRoad(Road *road);
    void addRandomCar();
    void removeRandomCar();
    void addIntersection(Intersection *intersection);
    void setFlipIntervals(std::vector<std::pair<double, double>> flipIntervals);
    double getAverageSpeed(int iterationsNumber, double delta);

    inline std::vector<Intersection*> getIntersections() {
        return intersections;
    }

    inline std::vector<Car*> getCars() {
        return cars;
    }

    inline int getCarsNumber() {
        return carsNumber;
    }

    inline void setCarsNumber(int carsNumber) {
        this->carsNumber = carsNumber;
    }

    inline double getInstantSpeed() {
        int allDeadCarsNumber = deadCarsNumber;
        double allSummaryAverageSpeed = summaryAverageSpeed;
        for (auto car : cars) {
            allDeadCarsNumber++;
            allSummaryAverageSpeed += car->getAverageSpeed();
        }
        return allSummaryAverageSpeed / allDeadCarsNumber;
    }

private:
    void refreshCars();
};


#endif //ROADTRAFFICSIMULATOR_WORLD_H
