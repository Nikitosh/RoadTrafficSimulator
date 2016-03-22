#ifndef ROADTRAFFICSIMULATOR_SEGMENT_H
#define ROADTRAFFICSIMULATOR_SEGMENT_H

#include <vector>
#include "Point.h"

template <typename T>
class Segment {
private:
    Point<T> source, target;

public:
    Segment(Point<T> source, Point<T> target): source(source), target(target) {
    }

    inline Point getVector() const {
        return target - source;
    }

    inline T getLength() const {
        return getVector().getLength();
    }

    inline double getDirection() const {
        return getVector().getDirection();
    }

    inline Point getPoint(double ratio) {
        return target * ratio + source * (1 - ratio);
    }

    inline Point getCenter() {
        return getPoint(0.5);
    }

    inline Segment getSubsegment(double ratioL, double ratioR) {
        return Segment(getPoint(ratioL), getPoint(ratioR));
    }

    std::vector<Segment> getSplittedSubsegments(int number, bool reverse) {
        std::vector<Segment> splittedSubsegments(number);
        for (int i = 0; i < number; i++) {
            splittedSubsegments[i] = getSubsegment(i * 1.0 / number, (i + 1) * 1.0 / number);
        }
        return splittedSubsegments;
    }
};

#endif //ROADTRAFFICSIMULATOR_SEGMENT_H
