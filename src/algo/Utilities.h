#ifndef ROADTRAFFICSIMULATOR_UTILITIES_H
#define ROADTRAFFICSIMULATOR_UTILITIES_H

#include <src/model/World.h>

class Utilities {
public:
    static const int HEIGHT = 3;
    static const int WIDTH = 4;
    static double calculateAverageSpeed(std::vector<std::pair<double, double>> flipIntervals, int iterationsNumber);
};

#endif //ROADTRAFFICSIMULATOR_UTILITIES_H
