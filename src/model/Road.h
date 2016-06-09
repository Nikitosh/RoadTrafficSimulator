#ifndef ROADTRAFFICSIMULATOR_ROAD_H
#define ROADTRAFFICSIMULATOR_ROAD_H

#include <QtCore/QRect>
#include <QtCore/QDebug>
#include "src/geometry/Segment.h"

class Intersection;
class Lane;

class Road {
private:
    Intersection &source;
    Intersection &target;
    std::vector<Lane*> lanes;
    Segment<double> sourceSide;
    Segment<double> targetSide;
    int sourceSideId;
    int targetSideId;

public:
    Road(Intersection &source, Intersection &target);
    void update();

    inline double getLength() const {
        return (targetSide.getTarget() - sourceSide.getSource()).getLength();
    }

    inline Lane* getLeftmostLane() {
        return lanes[0];
    }

    inline Lane* getRightmostLane() {
        return lanes.back();
    }

    inline int getTurnDirection(Road *road) const {
        return (road->getSourceSideId() - targetSideId - 1 + 8) % 4;
    }

    inline Segment<double> getSourceSide() const {
        return sourceSide;
    }

    inline Segment<double> getTargetSide() const {
        return targetSide;
    }

    inline int getSourceSideId() const {
        return sourceSideId;
    }

    inline int getTargetSideId() const {
        return targetSideId;
    }

    inline Intersection* getSource() const {
        return &source;
    }

    inline Intersection* getTarget() const {
        return &target;
    }

    inline int getLanesNumber() const {
        return lanes.size();
    }

    inline Lane* getLane(int index) const {
        return lanes[index];
    }

    inline QRect getQRect() const {
        int minX = (int) std::min(sourceSide.getSource().getX(), targetSide.getSource().getX());
        int maxX = (int) std::max(sourceSide.getSource().getX(), targetSide.getSource().getX());
        int minY = (int) std::min(sourceSide.getSource().getY(), targetSide.getSource().getY());
        int maxY = (int) std::max(sourceSide.getSource().getY(), targetSide.getSource().getY());
        return QRect(minX, minY, maxX - minX, maxY - minY);
    }
};

#endif //ROADTRAFFICSIMULATOR_ROAD_H
