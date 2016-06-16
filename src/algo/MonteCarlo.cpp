#include "MonteCarlo.h"
#include "Utilities.h"

MonteCarlo::MonteCarlo() {
    world = new World();
    world->read(Settings::getInstance().MAP_PATH);
}

double MonteCarlo::run() {
    double bestAverageSpeed = 0;
    for (int i = 0; i < RUN_NUMBER; i++) {
        std::vector<std::pair<double, double>> flipIntervals;
        int size = world->getIntersections().size();
        for (int j = 0; j < size; j++) {
            flipIntervals.push_back(std::make_pair(rand() * 1. / RAND_MAX, rand() * 1. / RAND_MAX));
        }
        double averageSpeed = Utilities::calculateAverageSpeed(world, flipIntervals, ITERATIONS_NUMBER);
        if (averageSpeed > bestAverageSpeed) {
            bestAverageSpeed = averageSpeed;
        }
    }
    return bestAverageSpeed;
}
