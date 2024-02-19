#ifndef PRIMITIVE_HEADER
#define PRIMITIVE_HEADER
#include <vector>
#include "point.hpp"

class Primitive {
    private:
        vector<Point> points;
    public:
        virtual vector<Point> point_generator() = 0;
        vector<Point> const &getPoints() const;
        void setPoints(vector<Point> const &p);
};

#endif