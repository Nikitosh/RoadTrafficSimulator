#ifndef ROADTRAFFICSIMULATOR_COUNTER_H
#define ROADTRAFFICSIMULATOR_COUNTER_H

class Counter {
private:
    static Counter *instance;
    Counter();
    int id = 0;

public:
    static Counter& getInstance();
    int getId();
};

#endif //ROADTRAFFICSIMULATOR_COUNTER_H
