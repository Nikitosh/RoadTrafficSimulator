#ifndef ROADTRAFFICSIMULATOR_POINT_H
#define ROADTRAFFICSIMULATOR_POINT_H

#include <c++/cmath>

template <typename T>
class Point {
private:
    T x, y;

public:
    Point(T x, T y): x(x), y(y) {
    }

    inline Point operator+(const Point &point) const {
        return Point(x + point.x, y + point.y);
    }

    inline Point operator-(const Point &point) const {
        return Point(x - point.x, y - point.y);
    }

    inline Point operator*(T k) const {
        return Point(x * k, y * k);
    }

    inline Point operator/(T k) const {
        return Point(x / k, y / k);
    }

    inline T getLength() const {
        return sqrt(x * x + y * y);
    }

    inline double getDirection() const {
        return atan2(y, x);
    }

    inline Point getNormalizedPoint() const {
        T length = length();
        return Point(x / length, y / length);
    }

    inline T getX() const {
        return x;
    }

    inline T getY() const {
        return y;
    }
};

#endif //ROADTRAFFICSIMULATOR_POINT_H
