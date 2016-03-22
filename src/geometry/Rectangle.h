#ifndef ROADTRAFFICSIMULATOR_RECTANGLE_H
#define ROADTRAFFICSIMULATOR_RECTANGLE_H

#define _USE_MATH_DEFINES
#include <c++/vector>
#include <c++/cmath>
#include "Point.h"
#include "Segment.h"

template <typename T>
class Rectangle {
private:
    T left, bottom, width, height;
    const double RIGHT_BOUNDS[5] = {-0.75 * M_PI, -0.25 * M_PI, 0.25 * M_PI, 0.75 * M_PI, 1.25 * M_PI};
    const int SECTORS[5] = {3, 0, 1, 2, 3};

public:
    Rectangle(T left, T bottom): left(left), bottom(bottom), width(0), height(0) {
    }

    Rectangle(T left, T bottom, T width, T height): left(left), bottom(bottom), width(width), height(height) {
    }

    T getArea() const {
        return width * height;
    }

    Point<T> getCenter() const {
        return Point<T>(left + width / 2, bottom + height / 2);
    }

    bool containsPoint(const Point<T> &point) const {
        return point.getX() >= left && point.getX() <= left + width
               && point.getY() >= bottom && point.getY() <= bottom + height;
    }

    bool containsRectangle(const Rectangle &rectangle) const {
        return rectangle.getLeft() >= left && rectangle.getRight() <= left + width
               && rectangle.getBottom() >= bottom && rectangle.getTop() <= bottom + height;
    }

    std::vector<Point<T>> getVertices() const {
        return std::vector<Point<T>>({Point<T>(left, bottom + height),
                            Point<T>(left + width, bottom + height),
                            Point<T>(left + width, bottom),
                            Point<T>(left, bottom)});
    }

    Segment<T> getSide(int index) const {
        std::vector<Point<T>> vertices = getVertices();
        return Segment<T>(vertices[index], vertices[(index + 1) % vertices.size()]);
    }

    int getSectorId(const Point<T> &point) const {
        double angle = (point - getCenter()).getDirection();
        for (int i = 0; i < 5; i++) {
            if (angle <= RIGHT_BOUNDS[i]) {
                return SECTORS[i];
            }
        }
    }

    T getLeft() const {
        return left;
    }

    T getRight() const {
        return left + width;
    }

    T getBottom() const {
        return bottom;
    }

    T getTop() const {
        return bottom + height;
    }

    T getWidth() const {
        return width;
    }

    T getHeight() const {
        return height;
    }
};

#endif //ROADTRAFFICSIMULATOR_RECTANGLE_H
