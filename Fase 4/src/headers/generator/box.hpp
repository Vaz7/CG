#ifndef BOX_HEADER
#define BOX_HEADER
#include "../common/point.hpp"
#include "primitive.hpp"

class Box : public Primitive {
    private:
        float length;
        int grid;

    public:
        Box(float, int);
        std::tuple<std::vector<Point>, std::vector<Point>, std::vector<Point>> point_generator();
};

#endif