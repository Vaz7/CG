#include "../headers/generator/primitive.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

std::vector<Point> const &Primitive::getPoints() const{
    return points;
}

void Primitive::setPoints(std::vector<Point> const &p) {
    points = p;
}

Point Primitive::cross(Point a, Point b) {
        
    float x = a.getY() * b.getZ() - a.getZ() * b.getY();
    float y = a.getZ() * b.getX() - a.getX() * b.getZ();
    float z = a.getX() * b.getY() - a.getY() * b.getX();

    if (x == -0) x = 0;
    if (y == -0) y = 0;
    if (z == -0) z = 0;

    return Point(x, y, z);
}

Point Primitive::normalize(Point a) {

    float l = sqrt(a.getX() * a.getX() + a.getY() * a.getY() + a.getZ() * a.getZ());

    if (l == 0 || l == -NAN || l == NAN) {
        return Point();
    }

    return a / l;
}