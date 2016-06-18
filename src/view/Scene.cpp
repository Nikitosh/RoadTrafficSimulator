#include "Scene.h"
#include "MainWindow.h"
#include <QtWidgets/QGraphicsEllipseItem>

constexpr double Scene::OFFSET_X[4][3];
constexpr double Scene::OFFSET_Y[4][3];

Scene::Scene(World *world) {
    this->world = world;

    std::vector<Intersection*> intersections = world->getIntersections();
    QPen solidLinePen(Qt::SolidLine);
    solidLinePen.setColor(Qt::white);
    solidLinePen.setWidth(5);
    QPen dashedLinePen(Qt::DashLine);
    dashedLinePen.setColor(Qt::white);
    dashedLinePen.setWidth(5);
    QBrush brush(Qt::gray);

    addIntersections(solidLinePen, brush);
    addRoads(solidLinePen, dashedLinePen, brush);
    addTrafficLights();
    addCars();
}


void Scene::updateState() {
    world->onTick(0.3 * speedScale);
    updateTrafficLights();
    updateCars();
    update(sceneRect());
}

void Scene::scaleSpeed(int value) {
    int delta = value - MainWindow::SPEED_SLIDER_INITIAL_POSITION;
    speedScale = pow(SPEED_SCALE_FACTOR, delta);
}

void Scene::addIntersections(QPen pen, QBrush brush) {
    std::vector<Intersection*> intersections = world->getIntersections();
    for (const auto &intersection : intersections) {
        addRect(intersection->getRectangle().toQRect(), pen, brush);
    }
}

void Scene::addRoads(QPen solidLinePen, QPen dashedLinePen, QBrush brush) {
    std::vector<Intersection *> intersections = world->getIntersections();
    for (const auto &intersection : intersections) {
        int roadsNumber = intersection->getRoadsNumber();
        for (int i = 0; i < roadsNumber; i++) {
            Road *road = intersection->getRoad(i);
            addRect(road->getQRect(), solidLinePen, brush);
            int lanesNumber = road->getLanesNumber();
            for (int j = 1; j < lanesNumber; j++) {
                addLine(QLine(road->getSourceSide().getPoint(j * 1. / lanesNumber).toQPoint(),
                              road->getTargetSide().getPoint((lanesNumber - j) * 1. / lanesNumber).toQPoint()),
                        dashedLinePen);
            }
        }

    }
}

void Scene::addTrafficLights() {
    std::vector<Intersection *> intersections = world->getIntersections();
    for (const auto &intersection : intersections) {
        int width = (int) intersection->getRectangle().getWidth();
        for (int i = 0; i < 4; i++) {
            std::string s = intersection->getTrafficLight()->getState(i);
            QColor color = Qt::red;
            for (int j = 0; j < 3; j++) {
                if (s[2 - j] == '1') {
                    color = Qt::green;
                }
                else {
                    color = Qt::red;
                }
                trafficLightsItems.push_back(addEllipse(QRect(intersection->getRectangle().getLeft() + Scene::OFFSET_X[i][j] * width,
                                                              intersection->getRectangle().getBottom() + Scene::OFFSET_Y[i][j] * width,
                                                              width * 0.05, width * 0.05), QPen(color), QBrush(color)));
            }
        }
    }
}

void Scene::addCars() {
    std::vector<Car*> cars = world->getCars();
    for (const auto &car : cars) {
        addCar(car);
    }
}

void Scene::addCar(Car *car) {
    Point<double> coordinates = car->getCoordinates();
    double x = coordinates.getX();
    double y = coordinates.getY();
    QPixmap pixmap = Settings::getInstance().getCarPixmap(car->getColor());
    QGraphicsPixmapItem *pixmapItem = addPixmap(pixmap);
    pixmapItem->setOffset(-0.5 * QPointF(pixmap.width(), pixmap.height()));
    pixmapItem->setPos(x, y);
    pixmapItem->setRotation(qRadiansToDegrees(car->getDirection()));
    carsItems[car] = pixmapItem;
}

void Scene::updateTrafficLights() {
    std::vector<Intersection*> intersections = world->getIntersections();
    int currentTrafficLight = 0;
    for (const auto &intersection : intersections) {
        for (int i = 0; i < 4; i++) {
            std::string s = intersection->getTrafficLight()->getState(i);
            QColor color = Qt::red;
            for (int j = 0; j < 3; j++) {
                if (s[2 - j] == '1') {
                    color = Qt::green;
                }
                else {
                    color = Qt::red;
                }
                trafficLightsItems[currentTrafficLight]->setPen(QPen(color));
                trafficLightsItems[currentTrafficLight++]->setBrush(QBrush(color));
            }
        }
    }
}

void Scene::updateCars() {
    std::vector<Car*> cars = world->getCars();
    std::set<Car*> carsSet(cars.begin(), cars.end());
    for (const auto &car : cars) {
        if (!carsItems.count(car)) {
            addCar(car);
        }
        Point<double> coordinates = car->getCoordinates();
        QGraphicsItem *rect = carsItems[car];
        rect->setPos(coordinates.toQPoint());
        rect->setRotation(qRadiansToDegrees(car->getDirection()));
    }
    std::vector<Car*> toRemoveCars;
    for (const auto &carItem : carsItems) {
        if (!carsSet.count(carItem.first)) {
            toRemoveCars.push_back(carItem.first);
        }
    }
    for (const auto &car : toRemoveCars) {
        removeItem(carsItems[car]);
        carsItems.erase(car);
    }
}