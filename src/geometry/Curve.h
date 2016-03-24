#ifndef ROADTRAFFICSIMULATOR_CURVE_H
#define ROADTRAFFICSIMULATOR_CURVE_H

#include "Point.h"

template <typename T>
class Curve {
private:
    Point<T> a, b, c, d;
    const int POINTS_NUMBER = 10;

public:
    Curve(Point<T> a, Point<T> b, Point<T> c, Point<T> d): a(a), b(b), c(c), d(d) {
    }

    Point<T> getPoint(T ratio) const {
        return a * pow(1 - ratio, 3) + b * 3 * pow(1 - ratio, 2) * ratio
               + c * 3 * (1 - ratio) * pow(ratio, 2) + d * pow(ratio, 3);
    }

    T getLength() const {
        Point<T> lastPoint;
        T length = 0;
        for (int i = 0; i <= POINTS_NUMBER; i++) {
            Point<T> point = getPoint(i * 1.0 / POINTS_NUMBER);
            if (i > 0) {
                length += (point - lastPoint).getLength();
            }
            lastPoint = point;
        }
        return length;
    }
};

#endif //ROADTRAFFICSIMULATOR_CURVE_H
