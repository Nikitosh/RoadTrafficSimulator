#include "SimulatedAnnealing.h"
#include "Utilities.h"
#include <c++/ctime>

double SimulatedAnnealing::run() {
    double best = 0;
    for (int i = 0; i < RUN_NUMBER; i++) {
        std::vector<std::pair<double, double>> flipIntervals;
        int size = Utilities::WIDTH * Utilities::HEIGHT;
        for (int j = 0; j < size; j++) {
            flipIntervals.push_back(std::make_pair(rand() * 1. / RAND_MAX, rand() * 1. / RAND_MAX));
        }
        double bestSpeed = Utilities::calculateAverageSpeed(flipIntervals, ITERATIONS_NUMBER);
        for (int t = MAX_T; t > 0; t--) {
            int index = rand() % flipIntervals.size();
            auto flipInterval = flipIntervals[index];
            int type = rand() % 2;
            double &intervalToChange = flipIntervals[index].first;
            if (type == 1) {
                intervalToChange = flipIntervals[index].second;
            }
            intervalToChange += (rand() * 0.3 / RAND_MAX - 0.15);
            if (intervalToChange < 0) {
                flipIntervals[index] = flipInterval;
            }
            double newSpeed = Utilities::calculateAverageSpeed(flipIntervals, ITERATIONS_NUMBER);
            if (newSpeed <= bestSpeed) {
                if(rand() * 1. / RAND_MAX > exp(-C * (bestSpeed - newSpeed) / t)) {
                    flipIntervals[index] = flipInterval;
                }
                else {
                    bestSpeed = newSpeed;
                }
            }
            else {
                bestSpeed = newSpeed;
            }
        }
        best = std::max(best, bestSpeed);
    }
    return best;
}