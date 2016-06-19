#include "Settings.h"

Settings* Settings::instance;

Settings::Settings() {
}

Settings& Settings::getInstance() {
    if (!instance) {
        instance = new Settings();
    }
    return *instance;
}

void Settings::initialize() {
    for (int i = 0; i < COLORS_SIZE; i++) {
        carsPixmaps[i] = new QPixmap(QPixmap(("resources/cars_" + QString::number(i + 1).toStdString() + ".png").c_str())
                .scaled(carLength, carWidth, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}