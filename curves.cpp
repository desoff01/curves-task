#include "curves.h"

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << p.x << '\t' << p.y << "    " << p.z;
    return os;
}

Point Circle::getPoint(double t) const {
    return Point(radius * std::cos(t), radius * std::sin(t), 0.0);
}

Point Circle::getDerivative(double t) const {
    return Point(-radius * std::sin(t), radius * std::cos(t), 0.0);
}

Point Ellipse::getPoint(double t) const {
    return Point(radiusX * std::cos(t), radiusY * std::sin(t), 0.0);
}

Point Ellipse::getDerivative(double t) const {
    return Point(-radiusX * std::sin(t), radiusY * std::cos(t), 0.0);
}

Point Helix::getPoint(double t) const {
    return Point(radius * std::cos(t), radius * std::sin(t), step * t / (2 * M_PI));
}

Point Helix::getDerivative(double t) const {
    return Point(-radius * std::sin(t), radius * std::cos(t), step / (2 * M_PI));
}