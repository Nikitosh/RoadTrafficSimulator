#ifndef ROADTRAFFICSIMULATOR_MONTECARLO_H
#define ROADTRAFFICSIMULATOR_MONTECARLO_H

#include <src/model/World.h>
#include "OptimizationAlgorithm.h"

class MonteCarlo : public OptimizationAlgorithm {
private:
    const static int RUN_NUMBER = 300;
    const static int ITERATIONS_NUMBER = 1000;

public:
    double run();
};

#endif //ROADTRAFFICSIMULATOR_MONTECARLO_H
