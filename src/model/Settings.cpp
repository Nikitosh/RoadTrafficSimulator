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