#ifndef ROADTRAFFICSIMULATOR_SEGMENT_H
#define ROADTRAFFICSIMULATOR_SEGMENT_H

#include <c++/vector>
#include <c++/algorithm>
#include "Point.h"

template <typename T>
class Segment {
private:
    Point<T> source, target;

public:
    Segment(): source(Point<T>()), target(Point<T>()) {
    }

    Segment(Point<T> source, Point<T> target): source(source), target(target) {
    }

    inline Point<T> getVector() const {
        return target - source;
    }

    inline T getLength() const {
        return getVector().getLength();
    }

    inline double getDirection() const {
        return getVector().getDirection();
    }

    inline Point<T> getPoint(T ratio) const {
        return source * (1 - ratio) + target * ratio;
    }

    inline Point<T> getCenter() const {
        return getPoint(0.5);
    }

    inline Segment getSubsegment(T ratioL, T ratioR) const {
        return Segment(getPoint(ratioL), getPoint(ratioR));
    }

    std::vector<Segment<T>> getSplittedSubsegments(int number, bool reverse) const {
        std::vector<Segment<T>> splittedSubsegments(number);
        for (int i = 0; i < number; i++) {
            splittedSubsegments[i] = getSubsegment(i * 1.0 / number, (i + 1) * 1.0 / number);
        }
        if (reverse) {
            std::reverse(splittedSubsegments.begin(), splittedSubsegments.end());
        }
        return splittedSubsegments;
    }

    inline Point<T> getSource() const {
        return source;
    }

    inline Point<T> getTarget() const {
        return target;
    }
};

#endif //ROADTRAFFICSIMULATOR_SEGMENT_H
