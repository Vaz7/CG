#include "../headers/generator/sphere.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

Sphere::Sphere(float r, int slice, int stack) {
    radius = r;
    slices = slice;
    stacks = stack;
}

std::tuple<std::vector<Point>, std::vector<Point>, std::vector<Point>> Sphere::point_generator() {

    vector<Point> points;
    vector<Point> normals;
    vector<Point> tex_coords;

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
            
            float t1 = j / (float)slices;
            float t2 = (j+1) / (float)slices;
            float t3 = i / (float)stacks;
            float t4 = (i+1) / (float)stacks;

            points.push_back(Point(x2, y, z2));
            points.push_back(Point(prev_x2, prev_y, prev_z2));
            points.push_back(Point(prev_x, prev_y, prev_z));

            normals.push_back(normalize(Point(x2, y, z2)));
            normals.push_back(normalize(Point(prev_x2, prev_y, prev_z2)));
            normals.push_back(normalize(Point(prev_x, prev_y, prev_z)));

            tex_coords.push_back(Point(t2, t3, 0));
            tex_coords.push_back(Point(t2, t4, 0));
            tex_coords.push_back(Point(t1, t4, 0));

            points.push_back(Point(prev_x, prev_y, prev_z));
            points.push_back(Point(x, y, z));
            points.push_back(Point(x2, y, z2));

            normals.push_back(normalize(Point(prev_x, prev_y, prev_z)));
            normals.push_back(normalize(Point(x, y, z)));
            normals.push_back(normalize(Point(x2, y, z2)));

            tex_coords.push_back(Point(t1, t4, 0));
            tex_coords.push_back(Point(t1, t3, 0));
            tex_coords.push_back(Point(t2, t3, 0));
		}
	}

    return std::make_tuple(points, normals, tex_coords);
}