#include "Genetic.h"
#include "Utilities.h"

double Genetic::run() {
    double bestAverageSpeed = 0;
    int size = Utilities::WIDTH * Utilities::HEIGHT;
    for (int i = 0; i < POPULATION_NUMBER; i++) {
        std::vector<std::pair<double, double>> flipIntervals(size);
        for (int j = 0; j < size; j++) {
            flipIntervals.push_back(std::make_pair(rand() * 1. / RAND_MAX, rand() * 1. / RAND_MAX));
        }
        populations.push_back(flipIntervals);
    }
    for (int i = 0; i < RUN_NUMBER; i++) {
        std::vector<std::pair<double, std::vector<std::pair<double, double>>>> newPopulations;
        std::vector<std::pair<double, double>> flipIntervals(size);
        for (int j = 0; j < populations.size(); j++) {
            for (int k = 0; k < size; k++) {
                flipIntervals[k] = populations[j][k];
            }
            int index = rand() % size;
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
            double averageSpeed = Utilities::calculateAverageSpeed(flipIntervals, ITERATIONS_NUMBER);
            newPopulations.push_back(std::make_pair(averageSpeed, flipIntervals));
        }
        for (int j = 0; j < 5 * populations.size(); j++) {
            int index1 = rand() % populations.size(), index2 = rand() % populations.size();
            for (int k = 0; k < size; k++) {
                flipIntervals[k].first = (populations[index1][k].first + populations[index2][k].first) / 2;
                flipIntervals[k].second = (populations[index1][k].second + populations[index2][k].second) / 2;
            }
            double averageSpeed = Utilities::calculateAverageSpeed(flipIntervals, ITERATIONS_NUMBER);
            newPopulations.push_back(std::make_pair(averageSpeed, flipIntervals));
        }
        std::sort(newPopulations.begin(), newPopulations.end());
        reverse(newPopulations.begin(), newPopulations.end());
        if (newPopulations[0].first > bestAverageSpeed) {
            bestAverageSpeed = newPopulations[0].first;
        }
        for (int j = 0; j < populations.size(); j++) {
            populations[j] = newPopulations[j].second;
        }
    }
    return bestAverageSpeed;

}