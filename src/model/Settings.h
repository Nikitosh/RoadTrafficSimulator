#ifndef ROADTRAFFICSIMULATOR_SETTINGS_H
#define ROADTRAFFICSIMULATOR_SETTINGS_H

#include <QtCore/Qt>
#include <QtGui/QColor>
#include <QtGui/QImage>

class Settings {
private:
    static const int COLORS_SIZE = 5;
    static Settings* instance;
    Settings();
    QImage carsImages[COLORS_SIZE];
    static constexpr double flipMultiplier = 100;
    double gridSize = 50;
    double carLengthScale;
    double carWidthScale;

public:
    static constexpr const char *MAP_PATH = "resources/map.txt";
    static Settings& getInstance();

    inline double getFlipMultiplier() const {
        return flipMultiplier;
    }

    inline double getGridSize() const {
        return gridSize;
    }

    inline double getCarLengthScale() const {
        return carLengthScale;
    }

    inline void setCarLengthScale(double carLengthScale) {
        this->carLengthScale = carLengthScale;
    }

    inline double getCarWidthScale() const {
        return carWidthScale;
    }

    inline void setCarWidthScale(double carWidthScale) {
        this->carWidthScale = carWidthScale;
    }

    inline int getColorNumber() const {
        return COLORS_SIZE;
    }

    inline QImage getCarImage(int color) {
        return carsImages[color];
    }
};

#endif //ROADTRAFFICSIMULATOR_SETTINGS_H
