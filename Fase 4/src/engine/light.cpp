#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../headers/engine/light.hpp"
#include <iostream>

int lights[8] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

PointLight::PointLight(Point p) {
    pos = p;
    glEnable(lights[l_number++]);
}

DirectionalLight::DirectionalLight(Point d) {
    dir = d;
    glEnable(lights[l_number++]);
}

SpotLight::SpotLight(Point p, Point d, size_t c) {
    pos = p;
    dir = d;
    cutoff = c;
    glEnable(lights[l_number++]);
}

void PointLight::turn_on(int light_index) const {

    float p[4] = {pos.getX(), pos.getY(), pos.getZ(), 1.0};
    float quad_att = 0.0f;
    GLfloat dark[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat white[4] = {1.0, 1.0, 1.0, 1.0};
    
    glLightfv(lights[light_index], GL_AMBIENT, dark);
    glLightfv(lights[light_index], GL_DIFFUSE, white);
    glLightfv(lights[light_index], GL_SPECULAR, white);

    glLightfv(lights[light_index], GL_POSITION, p);
    glLightf(lights[light_index], GL_QUADRATIC_ATTENUATION, quad_att);
}

void DirectionalLight::turn_on(int light_index) const {
        
    GLfloat d[4] = {dir.getX(), dir.getY(), dir.getZ(), 0.0};
    GLfloat dark[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat white[4] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(lights[light_index], GL_DIFFUSE, white);
    glLightfv(lights[light_index], GL_SPECULAR, white);

    glLightfv(lights[light_index], GL_POSITION, d);
}

void SpotLight::turn_on(int light_index) const {

    GLfloat diff[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat p[4] = {pos.getX(), pos.getY(), pos.getZ(), 1.0};
    GLfloat spotDir[3] = {dir.getX(), dir.getY(), dir.getZ()};
    GLfloat dark[4] = {0.2, 0.2, 0.2, 0.2};
    GLfloat white[4] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(lights[light_index], GL_AMBIENT, dark);
    glLightfv(lights[light_index], GL_DIFFUSE, white);
    glLightfv(lights[light_index], GL_SPECULAR, white);

    glLightfv(lights[light_index], GL_POSITION, p);
    glLightfv(lights[light_index], GL_SPOT_DIRECTION, spotDir);
    glLightf(lights[light_index], GL_SPOT_CUTOFF, cutoff);
    glLightf(lights[light_index], GL_SPOT_EXPONENT, 0.0);
}