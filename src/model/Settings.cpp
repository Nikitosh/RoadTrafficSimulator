#include "Settings.h"

Settings* Settings::instance;

Settings::Settings() {
    for (int i = 0; i < COLORS_SIZE; i++) {
        carsPixmaps[i] = QPixmap(("resources/cars_" + QString::number(i + 1).toStdString() + ".png").c_str())
                .scaled(carLength, carWidth, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
}

Settings& Settings::getInstance() {
    if (!instance) {
        instance = new Settings();
    }
    return *instance;
}