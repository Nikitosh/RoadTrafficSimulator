#include <c++/ctime>
#include "Utilities.h"

double Utilities::calculateAverageSpeed(World *world, std::vector<std::pair<double, double>> flipIntervals, int iterationsNumber) {
    world->clear();
    world->read(Settings::getInstance().MAP_PATH);
    world->setFlipIntervals(flipIntervals);
    return world->getAverageSpeed(iterationsNumber, 0.3);
}
