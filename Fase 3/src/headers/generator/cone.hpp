#ifndef CONE_HEADER
#define CONE_HEADER
#include "../common/point.hpp"
#include "primitive.hpp"

using namespace std;

class Cone : public Primitive {
    private:
        float radius;
        float height;
        int slices;
        int stacks;

    public:
        Cone(float, float, int, int);
        vector<Point> point_generator();

};

#endif