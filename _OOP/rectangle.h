#ifndef UNIVERSITY_RECTANGLE_H
#define UNIVERSITY_RECTANGLE_H

using ld = long double;

class Point {
private:
    ld x{}, y{};

public:
    Point() = default;

    Point(ld xx, ld yy);

    ld getX() const noexcept;

    ld getY() const noexcept;
};

class Rectangle {
private:
    Point topLeft{}, bottomRight{};

public:
    Rectangle(const Point &tl, const Point &br);

    ld getArea() const noexcept;
};

Point::Point(const ld xx, const ld yy) : x(xx), y(yy) {}

ld Point::getX() const noexcept {
    return x;
}

ld Point::getY() const noexcept {
    return y;
}

Rectangle::Rectangle(const Point &tl, const Point &br) : topLeft(tl), bottomRight(br) {}

ld Rectangle::getArea() const noexcept {
    return (bottomRight.getX() - topLeft.getX()) * (topLeft.getY() - bottomRight.getY());
}

#endif
