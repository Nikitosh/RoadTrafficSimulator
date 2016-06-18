#include "Genetic.h"
#include "Utilities.h"

Genetic::Genetic() {
    world = World::generateFullMap(3, 5, 100);
}

double Genetic::run() {
    double bestAverageSpeed = 0;
    for (int i = 0; i < POPULATION_NUMBER; i++) {
        int size = world->getIntersections().size();
        std::vector<std::pair<double, double>> flipIntervals(size);
        for (int j = 0; j < size; j++) {
            flipIntervals.push_back(std::make_pair(rand() * 1. / RAND_MAX, rand() * 1. / RAND_MAX));
        }
        populations.push_back(flipIntervals);
    }
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