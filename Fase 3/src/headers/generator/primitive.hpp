#ifndef PRIMITIVE_HEADER
#define PRIMITIVE_HEADER
#include <vector>
#include "../common/point.hpp"

class Primitive {
    private:
        std::vector<Point> points;
    public:
        virtual std::vector<Point> point_generator() = 0;
        std::vector<Point> const &getPoints() const;
        void setPoints(std::vector<Point> const &p);
};

#endif