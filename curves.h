#pragma once

#include <math.h>
#include <iostream>

struct Point {
    Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    double x, y, z;

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

std::ostream& operator<<(std::ostream& os, const Point& p);

class Curve {
public:
    virtual ~Curve() = default;

    virtual Point getPoint(double t) const = 0;
    virtual Point getDerivative(double t) const = 0;
};

class Circle : public Curve {
    double radius;
public:
    Circle(double _radius) : radius(_radius) {}
    Point getPoint(double t) const override;
    Point getDerivative(double t) const override;
    inline double getRadius() const { return radius; }
};

class Ellipse : public Curve {
    double radiusX, radiusY;

public:
    Ellipse(double radX, double radY) : radiusX(radX), radiusY(radY) {}
    Point getPoint(double t) const override;
    Point getDerivative(double t) const override;
};

class Helix : public Curve {
    double radius, step;

public:
    Helix(double _radius, double _step) : radius(_radius), step(_step) {}
    Point getPoint(double t) const override;
    Point getDerivative(double t) const override;
};