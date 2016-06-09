#ifndef ROADTRAFFICSIMULATOR_LANE_H
#define ROADTRAFFICSIMULATOR_LANE_H

#include <c++/map>
#include "src/geometry/Segment.h"
#include "Road.h"

class LanePosition;

class Lane {
private:
    Road *road;
    Segment<double> sourceSegment;
    Segment<double> targetSegment;
    Segment<double> middleLine;
    Lane* leftAdjacent;
    Lane* rightAdjacent;
    Lane* leftmostAdjacent;
    Lane* rightmostAdjacent;
    std::map<int, LanePosition> carsPositions;

public:
    Lane(const Segment<double> &sourceSegment, const Segment<double> &targetSegment, Road &road);
    Lane();
    void update();
    void setAdjacents(Lane *leftAdjacent, Lane *rightAdjacent, Lane *leftmostAdjacent, Lane *rightmostAdjacent);
    void addCarPosition(LanePosition &carPosition);
    void removeCarPosition(LanePosition &carPosition);
    LanePosition* getNext(const LanePosition &carPosition);

    inline int getSourceSideId() const {
        return road->getSourceSideId();
    }

    inline int getTargetSideId() const {
        return road->getSourceSideId();
    }

    inline Segment<double> getMiddleLine() const {
        return middleLine;
    }

    inline bool isRightmost() const {
        return !rightAdjacent;
    }

    inline bool isLeftmost() const {
        return !leftAdjacent;
    }

    inline Segment<double> getLeftBorder() const {
        return Segment<double>(sourceSegment.getSource(), targetSegment.getTarget());
    }

    inline Segment<double> getRightBorder() const {
        return Segment<double>(sourceSegment.getTarget(), targetSegment.getSource());
    }

    inline double getLength() const {
        return middleLine.getLength();
    }

    inline double getDirection() const {
        return middleLine.getDirection();
    }

    inline Point<double> getPoint(double ratio) const {
        return middleLine.getPoint(ratio);
    }

    inline int getTurnDirection(const Lane &lane) const {
        return road->getTurnDirection(lane.getRoad());
    }

    inline Road* getRoad() const {
        return road;
    }

    inline Lane* getLeftmostAdjacent() const {
        return leftmostAdjacent;
    }

    inline Lane* getRightmostAdjacent() const {
        return rightmostAdjacent;
    }
};

#endif //ROADTRAFFICSIMULATOR_LANE_H
