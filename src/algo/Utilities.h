#ifndef ROADTRAFFICSIMULATOR_UTILITIES_H
#define ROADTRAFFICSIMULATOR_UTILITIES_H

#include <src/model/World.h>

class Utilities {
public:
    static double calculateAverageSpeed(World *world, std::vector<std::pair<double, double>> flipIntervals, int iterationsNumber);
};

#endif //ROADTRAFFICSIMULATOR_UTILITIES_H
