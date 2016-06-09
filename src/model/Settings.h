#ifndef ROADTRAFFICSIMULATOR_SETTINGS_H
#define ROADTRAFFICSIMULATOR_SETTINGS_H

#include <QtCore/Qt>
#include <QtGui/QColor>

class Settings {
private:
    const static int COLORS_SIZE = 7;
    const QColor COLORS[COLORS_SIZE] = {Qt::black, Qt::cyan, Qt::darkCyan, Qt::magenta, Qt::darkMagenta, Qt::blue, Qt::darkBlue};
    static Settings* instance;
    Settings();
    double lightsFlipInterval = 100;
    double gridSize = 50;
    double carLengthScale;
    double carWidthScale;

public:
    static Settings& getInstance();

    inline double getLightsFlipInterval() const {
        return lightsFlipInterval;
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

    inline QColor getColor(int index) const {
        return COLORS[index];
    }
};

#endif //ROADTRAFFICSIMULATOR_SETTINGS_H
