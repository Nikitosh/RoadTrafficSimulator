#ifndef ROADTRAFFICSIMULATOR_SETTINGS_H
#define ROADTRAFFICSIMULATOR_SETTINGS_H

class Settings {
private:
    static Settings* instance;
    Settings();
    double lightsFlipInterval = 1;
    double gridSize = 14;

public:
    static Settings& getInstance();

    inline double getLightsFlipInterval() const {
        return lightsFlipInterval;
    }

    inline double getGridSize() const {
        return gridSize;
    }
};

#endif //ROADTRAFFICSIMULATOR_SETTINGS_H
