#include <c++/ctime>
#include "Utilities.h"

double Utilities::calculateAverageSpeed(std::vector<std::pair<double, double>> flipIntervals, int iterationsNumber) {
    World *world = World::generateFullMap(HEIGHT, WIDTH, 100);
    world->setFlipIntervals(flipIntervals);
    return world->getAverageSpeed(iterationsNumber, 1);
    delete world;
}
