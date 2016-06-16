#ifndef ROADTRAFFICSIMULATOR_MONTECARLO_H
#define ROADTRAFFICSIMULATOR_MONTECARLO_H

#include <src/model/World.h>

class MonteCarlo {
private:
    const static int RUN_NUMBER = 1;
    const static int ITERATIONS_NUMBER = 10000;
    World *world;

public:
    MonteCarlo();
    double run();
};

#endif //ROADTRAFFICSIMULATOR_MONTECARLO_H
