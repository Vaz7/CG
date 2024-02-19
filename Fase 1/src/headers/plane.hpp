#ifndef PLANE_HEADER
#define PLANE_HEADER
#include "point.hpp"
#include "primitive.hpp"

using namespace std;

class Plane : public Primitive {
    private:
        float length;
        int grid;

    public:
        Plane(float, int);
        vector<Point> point_generator();
};

#endif