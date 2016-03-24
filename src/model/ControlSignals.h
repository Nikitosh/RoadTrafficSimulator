#ifndef ROADTRAFFICSIMULATOR_CONTROLSIGNALS_H
#define ROADTRAFFICSIMULATOR_CONTROLSIGNALS_H

#include <c++/string>
#include "Settings.h"

class ControlSignals {
private:
    const std::string NONE = "000";
    const std::string LEFT = "100";
    const std::string FORWARD_RIGHT = "011";
    const std::string ALL = "111";
    static const int STATES_NUMBER = 4;
    static const int SIDE_NUMBER = 4;
    const std::string STATES[STATES_NUMBER][SIDE_NUMBER] = {
            {LEFT, NONE, LEFT, NONE},
            {FORWARD_RIGHT, NONE, FORWARD_RIGHT, NONE},
            {NONE, LEFT, NONE, LEFT},
            {NONE, FORWARD_RIGHT, NONE, FORWARD_RIGHT}
    };
    double flipMultiplier;
    double phaseOffset;
    double timeAccumulator;
    int stateNum;
    int roadsNumber;

public:
    ControlSignals(int roadsNumber);

    inline double getFlipInterval() const {
        return (0.1 + 0.05 * flipMultiplier) * Settings::getInstance().getLightsFlipInterval();
    }

    inline void flip() {
        stateNum++;
        if (stateNum == STATES_NUMBER) {
            stateNum = 0;
        }
    }

    inline void onTick(double delta) {
        timeAccumulator += delta;
        if (timeAccumulator >= getFlipInterval()) {
            flip();
            timeAccumulator -= getFlipInterval();
        }
    }

    inline std::string getState(int sideId) const {
        if (roadsNumber <= 2) {
            return ALL;
        }
        return STATES[stateNum][sideId];
    }

    inline int incRoadsNumber() {
        roadsNumber++;
    }
};

#endif //ROADTRAFFICSIMULATOR_CONTROLSIGNALS_H
