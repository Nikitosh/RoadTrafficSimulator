#ifndef ROADTRAFFICSIMULATOR_CURVE_H
#define ROADTRAFFICSIMULATOR_CURVE_H

#include "Segment.h"

template <typename T>
class Curve {
private:
    Point<T> a, b, p, q;
    const int POINTS_NUMBER = 10;
    Segment<T> ap, pq, qb;

public:
    Curve(Point<T> a, Point<T> b, Point<T> p, Point<T> q): a(a), b(b), p(p), q(q) {
        ap = Segment<T>(a, p);
        pq = Segment<T>(p, q);
        qb = Segment<T>(q, b);
    }

    Point<T> getPoint(T ratio) const {
        return a * pow(1 - ratio, 3) + p * 3 * pow(1 - ratio, 2) * ratio
               + q * 3 * (1 - ratio) * pow(ratio, 2) + b * pow(ratio, 3);
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

    double getDirection(T ratio) const {
        Point<double> p0 = ap.getPoint(ratio);
        Point<double> p1 = pq.getPoint(ratio);
        Point<double> p2 = qb.getPoint(ratio);
        Point<double> r0 = Segment<T>(p0, p1).getPoint(ratio);
        Point<double> r1 = Segment<T>(p1, p2).getPoint(ratio);
        return Segment<T>(r0, r1).getDirection();
    }
};

#endif //ROADTRAFFICSIMULATOR_CURVE_H
