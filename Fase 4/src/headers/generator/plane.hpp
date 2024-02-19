#ifndef PLANE_HEADER
#define PLANE_HEADER
#include "../common/point.hpp"
#include "primitive.hpp"

using namespace std;

class Plane : public Primitive {
    private:
        float length;
        int grid;

    public:
        Plane(float, int);
        std::tuple<std::vector<Point>, std::vector<Point>, std::vector<Point>> point_generator();
};

#endif