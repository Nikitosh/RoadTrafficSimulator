#ifndef ROADTRAFFICSIMULATOR_ROAD_H
#define ROADTRAFFICSIMULATOR_ROAD_H

#include "../geometry/Segment.h"

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

    inline Lane& getLeftmostLane() {
        return *lanes[0];
    }

    inline Lane& getRightmostLane() {
        return *lanes.back();
    }

    inline int getTurnDirection(const Road &road) const {
        return (road.getSourceSideId() - targetSideId - 1 + 8) % 4;
    }

    inline int getSourceSideId() const {
        return sourceSideId;
    }

    inline int getTargetSideId() const {
        return targetSideId;
    }
};

#endif //ROADTRAFFICSIMULATOR_ROAD_H
