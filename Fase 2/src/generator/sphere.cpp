#include "../headers/generator/sphere.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

Sphere::Sphere(float r, int slice, int stack) {
    radius = r;
    slices = slice;
    stacks = stack;
}

vector<Point> Sphere::point_generator() {

    vector<Point> points;


    float new_alfa = (2 * M_PI) / slices , new_beta = M_PI / stacks;
    float x = 0, y = 0, z = 0, x2 = 0, z2 = 0, prev_x = 0, prev_x2 = 0, prev_y = 0, prev_z = 0, prev_z2 = 0;

    for(int i = 0; i < stacks; i++) {
		for(int j = 0; j < slices; j++) {
			x = radius * sin(new_beta * i) * cos(new_alfa * j);
			y = radius * cos(new_beta * i); 
			z = radius * sin(new_beta * i) * sin(new_alfa * j);
			x2 = radius * sin(new_beta * i) * cos(new_alfa * (j+1));
			z2 = radius * sin(new_beta * i) * sin(new_alfa * (j+1));
			prev_x = radius * sin(new_beta * (i+1)) * cos(new_alfa * j);
			prev_y = radius * cos(new_beta * (i+1)); 
			prev_z = radius * sin(new_beta * (i+1)) * sin(new_alfa * j);
			prev_x2 = radius * sin(new_beta * (i+1)) * cos(new_alfa * (j+1));
			prev_z2 = radius * sin(new_beta * (i+1)) * sin(new_alfa * (j+1));

            // Lateral 1
            points.push_back(Point(x2, y, z2));
            points.push_back(Point(prev_x2, prev_y, prev_z2));
            points.push_back(Point(prev_x, prev_y, prev_z));

            points.push_back(Point(prev_x, prev_y, prev_z));
            points.push_back(Point(x, y, z));
            points.push_back(Point(x2, y, z2));
		}
	}

    return points;
}