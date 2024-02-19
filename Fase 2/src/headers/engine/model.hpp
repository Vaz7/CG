#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "../common/point.hpp"
#include "../../tinyxml/tinyxml.h"
#include <vector>

class Model{
    
    private:
        std::vector<Point> vertices;
    
    public:
        Model(std::string);
        void draw();
        std::vector<Point> const &get_vertices() const;
};

#endif