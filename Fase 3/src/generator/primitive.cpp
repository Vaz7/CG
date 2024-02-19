#include "../headers/generator/primitive.hpp"

using namespace std;

vector<Point> const &Primitive::getPoints() const{
    return points;
}

void Primitive::setPoints(vector<Point> const &p) {
    points = p;
}