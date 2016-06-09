#include "View.h"

View::View() {
    world = new World;
    world->read("C:/Jetbrains/RoadTrafficSimulator/resources/map.txt");
    //printf("%d\n", world->getCars().size());
}

void View::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(viewport());
    QPen solidLinePen(Qt::SolidLine);
    solidLinePen.setColor(Qt::white);
    QPen dashedLinePen(Qt::DashLine);
    dashedLinePen.setColor(Qt::white);
    painter.setPen(solidLinePen);

    std::vector<Intersection*> intersections = world->getIntersections();
    for (const auto &intersection : intersections) {
        painter.fillRect(QRect(intersection->getRectangle().toQRect()), Qt::gray);
        painter.drawRect(QRect(intersection->getRectangle().toQRect()));
    }

    for (const auto &intersection : intersections) {
        int roadsNumber = intersection->getRoadsNumber();
        for (int i = 0; i < roadsNumber; i++) {
            Road *road = intersection->getRoad(i);
            painter.fillRect(road->getQRect(), Qt::gray);
            painter.drawRect(road->getQRect());
            int lanesNumber = road->getLanesNumber();
            painter.setPen(dashedLinePen);
            for (int j = 1; j < lanesNumber; j++) {
                painter.drawLine(QLine(road->getSourceSide().getPoint(j * 1. / lanesNumber).toQPoint(),
                                       road->getTargetSide().getPoint((lanesNumber - j) * 1. / lanesNumber).toQPoint()));
            }
            painter.setPen(solidLinePen);
        }

        int width = (int) intersection->getRectangle().getWidth();
        for (int i = 0; i < 4; i++) {
            std::string s = intersection->getControlSignals()->getState(i);
            QColor color = Qt::red;
            for (int j = 0; j < 3; j++) {
                if (s[2 - j] == '1') {
                    color = Qt::green;
                }
                else {
                    color = Qt::red;
                }
                painter.fillRect(
                        QRect(intersection->getRectangle().getLeft() + OFFSET_X[i][j] * width,
                              intersection->getRectangle().getBottom() + OFFSET_Y[i][j] * width,
                              width * 0.05, width * 0.05), color);
            }
        }
    }

    std::vector<Car*> cars = world->getCars();
    for (const auto &car : cars) {
        Point<double> coordinates = car->getCoordinates();
        painter.resetTransform();
        painter.translate(coordinates.getX(), coordinates.getY());
        painter.rotate(qRadiansToDegrees(car->getDirection()));
        painter.fillRect(QRect(-car->getLength() / 2, -car->getWidth() / 2, car->getLength(), car->getWidth()),
        Settings::getInstance().getColor(car->getColor()));
    }
    painter.end();
}

void View::updateState() {
    world->onTick(0.15);
    viewport()->repaint();
    viewport()->update();
}