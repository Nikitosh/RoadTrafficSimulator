#include "Counter.h"

Counter* Counter::instance;

Counter::Counter() {
}

Counter& Counter::getInstance() {
    if (!instance) {
        instance = new Counter();
    }
    return *instance;
}

int Counter::getId() {
    return id++;
}