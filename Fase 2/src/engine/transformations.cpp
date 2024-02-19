#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../headers/engine/transformations.hpp"

void Translate::transform() const {
    glTranslatef(x, y, z);
}

void Rotate::transform() const {
    glRotatef(angle, x, y, z);
}

void Scale::transform() const {
    glScalef(x, y, z);
}