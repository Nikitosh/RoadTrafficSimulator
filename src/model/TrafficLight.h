#ifndef ROADTRAFFICSIMULATOR_CONTROLSIGNALS_H
#define ROADTRAFFICSIMULATOR_CONTROLSIGNALS_H

#include <c++/string>
#include <c++/cstdio>
#include "Settings.h"

class TrafficLight {
private:
    const std::string NONE = "000";
    const std::string LEFT = "001";
    const std::string FORWARD_RIGHT = "110";
    const std::string ALL = "111";
    static const int STATES_NUMBER = 4;
    static const int SIDE_NUMBER = 4;
    const std::string STATES[STATES_NUMBER][SIDE_NUMBER] = {
            {LEFT, NONE, LEFT, NONE},
            {FORWARD_RIGHT, NONE, FORWARD_RIGHT, NONE},
            {NONE, LEFT, NONE, LEFT},
            {NONE, FORWARD_RIGHT, NONE, FORWARD_RIGHT}
    };
    double timeAccumulator;
    double flipIntervals[2];
    int stateNum;
    int roadsNumber;

public:
    TrafficLight(int roadsNumber);

    inline void onTick(double delta) {
        timeAccumulator += delta;
        double flipInterval = flipIntervals[stateNum & 1] * Settings::getInstance().getFlipMultiplier();
        if (timeAccumulator >= flipInterval) {
            timeAccumulator -= flipInterval;
            flip();
        }
    }

    inline std::string getState(int sideId) const {
        if (roadsNumber <= 2) {
            return ALL;
        }
        return STATES[stateNum][sideId];
    }

    inline void incRoadsNumber() {
        roadsNumber++;
    }

    inline const double* getFlipInterval() const {
        return flipIntervals;
    }

    inline void setFlipInterval(double greenFlipInterval, double redFlipInterval) {
        flipIntervals[0] = greenFlipInterval;
        flipIntervals[1] = redFlipInterval;
    }

private:
    inline void flip() {
        stateNum++;
        if (stateNum == STATES_NUMBER) {
            stateNum = 0;
        }
    }
};

#endif //ROADTRAFFICSIMULATOR_CONTROLSIGNALS_H
