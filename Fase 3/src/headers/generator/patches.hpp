#ifndef PATCHES_HEADER
#define PATCHES_HEADER

#include <vector>
#include <string>
#include "../common/point.hpp"

class Patches{

    private:
        int patch_num;
        std::vector<int> patch_indices;
        int ctrl_points_num;
        std::vector<Point> control_points;
        int tesselation;
        std::vector<Point> points;

    public:
        Patches(std::string, int);
        void set_up_bezier();
        void dump_to_3D_file(std::string);
};

#endif