#ifndef ROADTRAFFICSIMULATOR_SCENE_H
#define ROADTRAFFICSIMULATOR_SCENE_H

#include <src/model/World.h>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsEllipseItem>

class Scene : public QGraphicsScene {
private:
    static constexpr double OFFSET_X[4][3] = {
            {0.6, 0.725, 0.85},
            {0.85, 0.85, 0.85},
            {0.35, 0.225, 0.1},
            {0.1, 0.1, 0.1}
    };
    static constexpr double OFFSET_Y[4][3] = {
            {0.85, 0.85, 0.85},
            {0.35, 0.225, 0.1},
            {0.1, 0.1, 0.1},
            {0.6, 0.725, 0.85}
    };
    static constexpr double SPEED_SCALE_FACTOR = 1.5;
    World *world;
    std::vector<QGraphicsEllipseItem*> trafficLightsItems;
    std::map<Car*, QGraphicsItem*> carsItems;
    double speedScale = 1;

public:
    Scene(World *world);
    void updateState();
    void scaleSpeed(int value);

private:
    void addIntersections(QPen pen, QBrush brush);
    void addRoads(QPen solidLinePen, QPen dashedLinePen, QBrush brush);
    void addTrafficLights();
    void addCars();
    void addCar(Car *car);
    void updateTrafficLights();
    void updateCars();
};

#endif //ROADTRAFFICSIMULATOR_SCENE_H
