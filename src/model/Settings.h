#ifndef ROADTRAFFICSIMULATOR_SETTINGS_H
#define ROADTRAFFICSIMULATOR_SETTINGS_H

#include <QtCore/Qt>
#include <QtGui/QColor>
#include <QtGui/QPixmap>

class Settings {
private:
    static const int COLORS_SIZE = 5;
    static Settings* instance;
    const double flipMultiplier = 100;
    const double gridSize = 700;
    const double roadLength = 1500;
    const double carLength = 150;
    const double carWidth = 75;
    const int laneNumber = 3;
    double scale = 1;
    QPixmap *carsPixmaps[COLORS_SIZE];

public:
    static constexpr const char *MAP_PATH = "resources/map.txt";
    static Settings& getInstance();
    void initialize();

    inline double getFlipMultiplier() const {
        return flipMultiplier;
    }

    inline double getGridSize() const {
        return gridSize;
    }

    inline double getRoadLength() const {
        return roadLength;
    }

    inline double getCarLength() const {
        return carLength;
    }

    inline double getCarWidth() const {
        return carWidth;
    }

    inline int getLaneNumber() const {
        return laneNumber;
    }

    inline double getScale() const {
        return scale;
    }

    inline void setScale(double scale) {
        this->scale = scale;
    }

    inline int getColorNumber() const {
        return COLORS_SIZE;
    }

    inline QPixmap getCarPixmap(int color) {
        return *carsPixmaps[color];
    }

private:
    Settings();
};

#endif //ROADTRAFFICSIMULATOR_SETTINGS_H
