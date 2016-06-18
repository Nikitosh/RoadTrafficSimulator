#ifndef ROADTRAFFICSIMULATOR_GENETIC_H
#define ROADTRAFFICSIMULATOR_GENETIC_H

#include <src/model/World.h>
#include "OptimizationAlgorithm.h"

class Genetic : public OptimizationAlgorithm {
private:
    const static int POPULATION_NUMBER = 5;
    const static int RUN_NUMBER = 100;
    const static int ITERATIONS_NUMBER = 100;
    World *world;
    std::vector<std::vector<std::pair<double, double>>> populations;

public:
    Genetic();
    virtual double run();
};

#endif //ROADTRAFFICSIMULATOR_GENETIC_H
