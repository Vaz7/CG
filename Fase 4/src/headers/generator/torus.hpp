#ifndef TORUS_HEADER
#define TORUS_HEADER
#include "../common/point.hpp"
#include "primitive.hpp"

using namespace std;

class Torus : public Primitive {
    private:
        float radius1;
        float radius2;
        int slices;
        int stacks;

    public:
        Torus(float,float,int,int);
        std::tuple<std::vector<Point>, std::vector<Point>, std::vector<Point>> point_generator();
};

#endif
