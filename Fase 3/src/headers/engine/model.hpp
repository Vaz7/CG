#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "../common/point.hpp"
#include "../../tinyxml/tinyxml.h"
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

class Model{
    
    private:
        std::vector<Point> vertices;
        GLuint buffer;
        size_t vertice_num;
    
    public:
        Model(std::string);
        void draw();
        std::vector<Point> const &get_vertices() const;
};

#endif