#ifndef BOX_HEADER
#define BOX_HEADER
#include "point.hpp"
#include "primitive.hpp"

using namespace std;

class Box : public Primitive {
    private:
        float length;
        int grid;

    public:
        Box(float, int);
        vector<Point> point_generator();
};

#endif