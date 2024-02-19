#include "../headers/engine/model.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <iterator>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

// TODO: Mudar isto para ficarmos a usar um super() nos dois construtores em baixo do primeiro!

Model::Model(std::string filename) {

	std::ifstream file(filename);
	std::string line;
    std::vector<float> vbo;

	while(std::getline(file, line)){
		std::stringstream p(line);
		float x,y,z;
	    p >> x >> y >> z;
		vertices.push_back(std::move(Point(x,y,z)));
        vbo.push_back(x);
        vbo.push_back(y);
        vbo.push_back(z);
	}

    vertice_num = vbo.size() / 3;
    glEnableClientState(GL_VERTEX_ARRAY);
    glGenBuffers(2, buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, vbo.size() * sizeof(float), vbo.data(), GL_STATIC_DRAW);
}

Model::Model(std::string filename, GLfloat d[4], GLfloat a[4], GLfloat s[4], GLfloat e[4], GLfloat shiny) {

	std::ifstream file(filename);
	std::string line;
    std::vector<float> vbo;
    std::vector<float> normals;

	while(std::getline(file, line)){
		std::stringstream p(line);
		float x,y,z;
		float nx,ny,nz;
		float tx,ty,tz;
	    p >> x >> y >> z >> nx >> ny >> nz >> tx >> ty >> tz;
		vertices.push_back(std::move(Point(x,y,z)));
        vbo.push_back(x);
        vbo.push_back(y);
        vbo.push_back(z);
        normals.push_back(nx);
        normals.push_back(ny);
        normals.push_back(nz);
	}

    std::memcpy(diffusive, d, 4 * sizeof(GLfloat));
    std::memcpy(ambient, a, 4 * sizeof(GLfloat));
    std::memcpy(specular, s, 4 * sizeof(GLfloat));
    std::memcpy(emissive, e, 4 * sizeof(GLfloat));
    shininess = shiny;

    vertice_num = vbo.size() / 3;

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glGenBuffers(2, buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, vbo.size() * sizeof(float), vbo.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
}

Model::Model(std::string filename, GLfloat d[4], GLfloat a[4], GLfloat s[4], GLfloat e[4], GLfloat shiny, std::string texture_file) {

	std::ifstream file(filename);
	std::string line;
    std::vector<float> vbo;
    std::vector<float> normals;
    std::vector<float> tex;
    unsigned int t, tw, th;
    unsigned char* texData;

    has_texture = true;

	while(std::getline(file, line)){
		std::stringstream p(line);
		float x,y,z;
		float nx,ny,nz;
		float tx,ty,tz;
	    p >> x >> y >> z >> nx >> ny >> nz >> tx >> ty >> tz;
		vertices.push_back(std::move(Point(x,y,z)));
        vbo.push_back(x);
        vbo.push_back(y);
        vbo.push_back(z);
        normals.push_back(nx);
        normals.push_back(ny);
        normals.push_back(nz);
        tex.push_back(tx);
        tex.push_back(ty);
	}

    std::memcpy(diffusive, d, 4 * sizeof(GLfloat));
    std::memcpy(ambient, a, 4 * sizeof(GLfloat));
    std::memcpy(specular, s, 4 * sizeof(GLfloat));
    std::memcpy(emissive, e, 4 * sizeof(GLfloat));
    shininess = shiny;

    vertice_num = vbo.size() / 3;

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glGenBuffers(3, buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, vbo.size() * sizeof(float), vbo.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    glBufferData(GL_ARRAY_BUFFER, tex.size() * sizeof(float), tex.data(), GL_STATIC_DRAW);

    ilGenImages(1, &t);
    texture_file = "../xml/" + texture_file;
    ilLoadImage((ILstring)texture_file.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);
}

std::vector<Point> const &Model::get_vertices() const{
    return vertices;
}

void Model::draw() {

    // Ciclo que percorre o vetor de pontos do Modelo e desenha os triangulos correspondentes
    // é usado um iterator em vez de um "forEach" loop de modo a conseguirmos avançar 3 posições de cada vez (nº pontos num triângulo)
//	for (std::vector<Point>::iterator i = vertices.begin(); i != vertices.end(); i += 3) {
//        Point p1 = *i;
//        Point p2 = *(i + 1);
//        Point p3 = *(i + 2);
//
//        glColor3f(1,1,1);
//        glBegin(GL_TRIANGLES);
//        glVertex3f(p1.getX(),p1.getY(),p1.getZ());
//        glVertex3f(p2.getX(),p2.getY(),p2.getZ());
//        glVertex3f(p3.getX(),p3.getY(),p3.getZ());
//        glEnd();
//	}
    glColor3f(1,1,1);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffusive);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glNormalPointer(GL_FLOAT, 0, 0);

    if (has_texture) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
    }

    glDrawArrays(GL_TRIANGLES, 0, vertice_num);

    if (has_texture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}