#ifndef PRIMITIVE_HEADER
#define PRIMITIVE_HEADER
#include "../common/point.hpp"
#include <vector>
#include <tuple>

class Primitive {
    private:
        std::vector<Point> points;
        std::vector<Point> normals;
        std::vector<Point> tex_coords;

    public:
        virtual std::tuple<std::vector<Point>, std::vector<Point>, std::vector<Point>> point_generator() = 0;
        Point normalize(Point);
        Point cross(Point, Point);
        std::vector<Point> const &getPoints() const;
        void setPoints(std::vector<Point> const &p);
};

#endif