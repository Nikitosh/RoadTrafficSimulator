#include "World.h"

void World::read(const char *path) {
    FILE *inputFile = fopen(path, "r");
    int intersectionsNumber;
    fscanf(inputFile, "%d", &intersectionsNumber);
    for (int i = 0; i < intersectionsNumber; i++) {
        int left, bottom, width, height;
        fscanf(inputFile, "%d%d%d%d", &left, &bottom, &width, &height);
        addIntersection(new Intersection(Rectangle<double>(left, bottom, width, height)));
    }
    int roadsNumber;
    fscanf(inputFile, "%d", &roadsNumber);
    for (int i = 0; i < roadsNumber; i++) {
        int source, target;
        fscanf(inputFile, "%d%d", &source, &target);
        addRoad(new Road(*intersections[source - 1], *intersections[target - 1]));
    }
    double carLengthScale;
    fscanf(inputFile, "%lf", &carLengthScale);
    Settings::getInstance().setCarLengthScale(carLengthScale);
    double carWidthScale;
    fscanf(inputFile, "%lf", &carWidthScale);
    Settings::getInstance().setCarWidthScale(carWidthScale);
    fscanf(inputFile, "%d", &carsNumber);
    for (int i = 0; i < carsNumber; i++) {
        addRandomCar();
    }
}

void World::onTick(double delta) {
    time += delta;
    refreshCars();
    for (const auto &intersection : intersections) {
        intersection->getControlSignals()->onTick(delta);
    }
    int cnt = 0;
    for (auto it = cars.begin(); it != cars.end();) {
        Car *car = *it;
        car->move(delta);
        if (!car->isAlive()) {
            it = cars.erase(it);
        } else {
            it++;
        }
    }
}

void World::refreshCars() {
    if (cars.size() < carsNumber) {
        addRandomCar();
    }
    if (cars.size() > carsNumber) {
        removeRandomCar();
    }
}

void World::addRoad(Road *road) {
    roads.push_back(road);
    road->getSource()->addOutRoad(road);
    road->getTarget()->addInRoad(road);
    road->update();
}

void World::addRandomCar() {
    Road *road = roads[rand() % roads.size()];
    Lane *lane = road->getLane(rand() % road->getLanesNumber());
    cars.push_back(new Car(*lane, 3 * Settings::getInstance().getCarLengthScale()));
}

void World::removeRandomCar() {
    cars.erase(cars.begin() + std::rand() % cars.size());
}

void World::addIntersection(Intersection *intersection) {
    intersections.push_back(intersection);
}