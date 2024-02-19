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
        GLuint buffer[3];
        size_t vertice_num;
        GLfloat diffusive[4] = {200 / 255.0, 200 / 255.0, 200 / 255.0, 1.0};
        GLfloat ambient[4] = {50 / 255.0, 50 / 255.0, 50 / 255.0, 1.0};
        GLfloat specular[4] = {0, 0, 0, 1.0};
        GLfloat emissive[4] = {0, 0, 0, 1.0};
        GLfloat shininess = 0;
        unsigned int texture;
        bool has_texture = false;
    
    public:
        Model(std::string);
        Model(std::string, GLfloat[4], GLfloat[4], GLfloat[4], GLfloat[4], GLfloat);
        Model(std::string, GLfloat[4], GLfloat[4], GLfloat[4], GLfloat[4], GLfloat, std::string);
        void draw();
        std::vector<Point> const &get_vertices() const;
};

#endif