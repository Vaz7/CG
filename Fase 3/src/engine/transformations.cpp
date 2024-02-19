#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../headers/engine/transformations.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <iterator>
#include <iostream>

float prev_y[3] = {0.0, 1.0, 0.0};

void TranslateStatic::transform(float time_elapsed) const {
    glTranslatef(x, y, z);
}

void buildRotMatrix(float *x, float *y, float *z, float *m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}


void normalize(float *a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
		
	}

}

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

	// catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
			
	for (int i = 0; i < 3; i++) {
		float p[4] = {p0[i], p1[i], p2[i], p3[i]};
		float a[4];

		multMatrixVector(*m, p, a);	
		pos[i] = powf(t, 3.0) * a[0] + powf(t, 2.0) * a[1] + t * a[2] + a[3]; 
		deriv[i] = 3 * powf(t, 2.0) * a[0] + 2 * t * a[1] + a[2];
	}
}

void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, int point_count, std::vector<Point> points) {

	float t = gt * point_count;
	int index = floor(t);
	t = t - index; 

	int indices[4]; 
	indices[0] = (index + point_count-1)%point_count;	
	indices[1] = (indices[0]+1)%point_count;
	indices[2] = (indices[1]+1)%point_count; 
	indices[3] = (indices[2]+1)%point_count;

	float p[4][3] = {
		{points[indices[0]].getX(), points[indices[0]].getY(), points[indices[0]].getZ()},
		{points[indices[1]].getX(), points[indices[1]].getY(), points[indices[1]].getZ()},
		{points[indices[2]].getX(), points[indices[2]].getY(), points[indices[2]].getZ()},
		{points[indices[3]].getX(), points[indices[3]].getY(), points[indices[3]].getZ()}
	};

	getCatmullRomPoint(t, p[0], p[1], p[2], p[3], pos, deriv);
}

void draw_curve_route(int tesselation, int point_count, std::vector<Point> points) {

	float pos[3];
	float deriv[3];
	float gt = 0;

	glBegin(GL_LINE_LOOP);
	for (; gt < 1; gt += 1.0/tesselation) {
		getGlobalCatmullRomPoint(gt, pos, deriv, point_count, points);
		glColor3f(1,1,1);
		glVertex3f(pos[0], pos[1], pos[2]);
	}
	glEnd();
}

void TranslateDynamic::transform(float time_elapsed) const {
    float pos[3], deriv[3];

	// TODO: Perguntar ao professor porque é que a tesselation é calculada desta maneira!
    draw_curve_route(2 * duration/1000, points.size(), points);
    getGlobalCatmullRomPoint(time_elapsed / duration, pos, deriv, points.size(), points);
    glTranslatef(pos[0], pos[1], pos[2]);

    float x[3] = {deriv[0], deriv[1], deriv[2]};
    normalize(x);

    float z[3];
    cross(x, prev_y, z);
    normalize(z);

	if (align) {
		glRotatef(-90, x[0], x[1], x[2]);
	}

    float y[3];
    cross(z, x, y);
    normalize(y);
    std::copy(std::begin(y), std::end(y), std::begin(prev_y));

    float m[16];
    buildRotMatrix(x, y, z, m);
    glMultMatrixf(m);
}

void RotateStatic::transform(float time_elapsed) const {
    glRotatef(angle, x, y, z);
}

void RotateDynamic::transform(float time_elapsed) const {
    float angle = time_elapsed * (360.0 / duration);
    glRotatef(angle, x, y, z);
}

void Scale::transform(float time_elapsed) const {
    glScalef(x, y, z);
}