#include "../headers/common/point.hpp"
#include <sstream>

using namespace std;

Point::Point(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
}

Point::Point() {
    x = 0;
    y = 0;
    z = 0;
}

float Point::getX() const { return x; }
float Point::getY() const { return y; }
float Point::getZ() const { return z; }

void Point::setX(float new_x) { x = new_x; }
void Point::setY(float new_y) { y = new_y; }
void Point::setZ(float new_z) { z = new_z; }

string Point::toString() {
    ostringstream point;                // Criação da stream
    point << x << ' ' << y << ' ' << z; // Preenchimento da stream
    return point.str();                 // Extração do conteúdo da stream
}

Point Point::operator*(float c) const {
    return Point( x * c, y * c, z * c );
}

Point Point::operator/(float c) const {
    return Point( x / c, y / c, z / c );
}

Point Point::operator+(Point c) const {
    return Point( x + c.getX(), y + c.getY(), z + c.getZ() );
}


Point Point::operator-(Point c) const {
    return Point( x - c.getX(), y - c.getY(), z - c.getZ() );
}