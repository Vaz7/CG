#ifndef SPHERE_HEADER
#define SPHERE_HEADER
#include "../common/point.hpp"
#include "primitive.hpp"

using namespace std;

class Sphere : public Primitive {
    private:
        float radius;
        int slices;
        int stacks;

    public:
        Sphere(float, int, int);
        vector<Point> point_generator();
};

#endif