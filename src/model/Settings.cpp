#include "Settings.h"

Settings* Settings::instance;

Settings::Settings() {
    for (int i = 0; i < COLORS_SIZE; i++) {
        carsImages[i] = QImage(("resources/cars_" + QString::number(i + 1).toStdString() + ".png").c_str());
    }
}

Settings& Settings::getInstance() {
    if (!instance) {
        instance = new Settings();
    }
    return *instance;
}