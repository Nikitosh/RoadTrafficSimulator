#ifndef ROADTRAFFICSIMULATOR_SIMULATEDANNEALING_H
#define ROADTRAFFICSIMULATOR_SIMULATEDANNEALING_H

#include <src/model/World.h>

class SimulatedAnnealing {
private:
    const static int RUN_NUMBER = 1;
    const static int ITERATIONS_NUMBER = 10000;
    const static int MAX_T = 100;
    constexpr static double C = 10000;
    World *world;

public:
    SimulatedAnnealing();
    double run();
};

#endif //ROADTRAFFICSIMULATOR_SIMULATEDANNEALING_H
