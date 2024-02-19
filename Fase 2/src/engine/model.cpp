#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../headers/engine/model.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

Model::Model(std::string filename) {

	std::ifstream file(filename);
	std::string line;

	while(std::getline(file, line)){
		std::stringstream p(line);
		float x,y,z;
	    p >> x >> y >> z;
		vertices.push_back(std::move(Point(x,y,z)));
	}
}

std::vector<Point> const &Model::get_vertices() const{
    return vertices;
}

void Model::draw() {

    // Ciclo que percorre o vetor de pontos do Modelo e desenha os triangulos correspondentes
    // é usado um iterator em vez de um "forEach" loop de modo a conseguirmos avançar 3 posições de cada vez (nº pontos num triângulo)
	for (std::vector<Point>::iterator i = vertices.begin(); i != vertices.end(); i += 3) {
        Point p1 = *i;
        Point p2 = *(i + 1);
        Point p3 = *(i + 2);

        glColor3f(1,1,1);
        glBegin(GL_TRIANGLES);
        glVertex3f(p1.getX(),p1.getY(),p1.getZ());
        glVertex3f(p2.getX(),p2.getY(),p2.getZ());
        glVertex3f(p3.getX(),p3.getY(),p3.getZ());
        glEnd();
	}
}