#include <c++/cassert>
#include "World.h"

constexpr int World::TURN[4][2];

World::~World() {
    for (auto car : cars) {
        delete car;
    }
    for (auto intersection : intersections) {
        delete intersection;
    }
    for (auto road : roads) {
        delete road;
    }
}

World* World::generateFullMap(int h, int w, int carsNumber) {
    World *world = new World();
    int intersectionsNumber = h * w;
    double width = Settings::getInstance().getGridSize();
    double roadLength = Settings::getInstance().getRoadLength();
    for (int i = 0; i < h * w; i++) {
        int x = i % w, y = i / w;
        world->addIntersection(new Intersection(Rectangle<double>(x * (width + roadLength), y * (width + roadLength),
                                                                  width, width)));
    }
    auto intersections = world->getIntersections();
    for (int i = 0; i < h * w; i++) {
        int x = i % w, y = i / w;
        for (int j = 0; j < 4; j++) {
            int newX = x + World::TURN[j][0], newY = y + World::TURN[j][1];
            if (newX >= 0 && newX < w && newY >= 0 && newY < h) {
                world->addRoad(new Road(*intersections[i], *intersections[newY * w + newX]));
            }
        }
    }
    world->setCarsNumber(carsNumber);
    for (int i = 0; i < carsNumber; i++) {
        world->addRandomCar();
    }
    return world;
}

void World::clear() {
    cars.clear();
    intersections.clear();
    roads.clear();
    time = 0;
}

void World::read(const char *path) {
    FILE *inputFile = fopen(path, "r");
    int intersectionsNumber;
    fscanf(inputFile, "%d", &intersectionsNumber);
    double width = Settings::getInstance().getGridSize();
    double roadLength = Settings::getInstance().getRoadLength();
    for (int i = 0; i < intersectionsNumber; i++) {
        int x, y;
        fscanf(inputFile, "%d%d", &y, &x);
        addIntersection(new Intersection(Rectangle<double>(x * (width + roadLength), y * (width + roadLength),
                                                           width, width)));
    }
    int roadsNumber;
    fscanf(inputFile, "%d", &roadsNumber);
    for (int i = 0; i < roadsNumber; i++) {
        int source, target;
        fscanf(inputFile, "%d%d", &source, &target);
        addRoad(new Road(*intersections[source - 1], *intersections[target - 1]));
    }
    double scale;
    fscanf(inputFile, "%lf", &scale);
    Settings::getInstance().setScale(scale);
    fscanf(inputFile, "%d", &carsNumber);
    for (int i = 0; i < carsNumber; i++) {
        addRandomCar();
    }
}

void World::onTick(double delta) {
    time += delta;
    refreshCars();
    for (const auto &intersection : intersections) {
        intersection->getTrafficLight()->onTick(delta);
    }
    for (auto it = cars.begin(); it != cars.end();) {
        Car *car = *it;
        car->move(delta);
        if (!car->isAlive()) {
            it = cars.erase(it);
            deadCarsNumber++;
            summaryAverageSpeed += car->getAverageSpeed();
            delete car;
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
    cars.push_back(new Car(*lane, Settings::getInstance().getCarLength() / 2));
}

void World::removeRandomCar() {
    cars.erase(cars.begin() + std::rand() % cars.size());
}

void World::addIntersection(Intersection *intersection) {
    intersections.push_back(intersection);
}

void World::setFlipIntervals(std::vector<std::pair<double, double>> flipIntervals) {
    assert(intersections.size() == flipIntervals.size());
    for (int i = 0; i < intersections.size(); i++) {
        intersections[i]->getTrafficLight()->setFlipInterval(flipIntervals[i].first, flipIntervals[i].second);
    }
}

double World::getAverageSpeed(int iterationsNumber, double delta) {
    for (int i = 0; i < iterationsNumber; i++) {
        onTick(delta);
    }
    return getInstantSpeed();
}