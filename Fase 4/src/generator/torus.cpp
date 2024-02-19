#include "../headers/generator/torus.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

Torus::Torus(float rad1, float rad2, int slice, int stack) {
    radius1 = rad1;
    radius2 = rad2;
    slices = slice;
    stacks = stack;
}

std::tuple<std::vector<Point>, std::vector<Point>, std::vector<Point>> Torus::point_generator() {

    vector<Point> points;
    vector<Point> normals;
    vector<Point> tex_coords;

    float deltaAlpha = (M_PI * 2) / slices;
    float deltaBeta = (M_PI * 2) / stacks;
    float alpha = 0.0f;
    float beta = 0.0f;

    for (int i = 0; i < slices; i++) {
        alpha = i * deltaAlpha;

        for (int j = 0; j < stacks; j++) {
            beta = j * deltaBeta;

            float t1 = i / (float)slices;
            float t2 = (i+1) / (float)slices;
            float t3 = j / (float)stacks;
            float t4 = (j+1) / (float)stacks;

            points.push_back(Point((radius1 + radius2 * cos(beta + deltaBeta)) * cos(alpha + deltaAlpha),
                radius2 * sin(beta + deltaBeta),
                (radius1 + radius2 * cos(beta + deltaBeta)) * sin(alpha + deltaAlpha)));
            points.push_back(Point((radius1 + radius2 * cos(beta)) * cos(alpha + deltaAlpha), 
                radius2 * sin(beta),
                (radius1 + radius2 * cos(beta)) * sin(alpha + deltaAlpha)));
            points.push_back(Point((radius1 + radius2 * cos(beta)) * cos(alpha),
                radius2 * sin(beta),
                (radius1 + radius2 * cos(beta)) * sin(alpha)));

            normals.push_back(normalize(Point((radius1 + radius2 * cos(beta + deltaBeta)) * cos(alpha + deltaAlpha),
                radius2 * sin(beta + deltaBeta),
                (radius1 + radius2 * cos(beta + deltaBeta)) * sin(alpha + deltaAlpha))));
            normals.push_back(normalize(Point((radius1 + radius2 * cos(beta)) * cos(alpha + deltaAlpha), 
                radius2 * sin(beta),
                (radius1 + radius2 * cos(beta)) * sin(alpha + deltaAlpha))));
            normals.push_back(normalize(Point((radius1 + radius2 * cos(beta)) * cos(alpha),
                radius2 * sin(beta),
                (radius1 + radius2 * cos(beta)) * sin(alpha))));

            tex_coords.push_back(Point(t2, t4, 0));
            tex_coords.push_back(Point(t2, t3, 0));
            tex_coords.push_back(Point(t1, t3, 0));

            points.push_back(Point((radius1 + radius2 * cos(beta)) * cos(alpha),
                radius2 * sin(beta),
                (radius1 + radius2 * cos(beta)) * sin(alpha)));
            points.push_back(Point((radius1 + radius2 * cos(beta + deltaBeta)) * cos(alpha), 
                radius2 * sin(beta + deltaBeta),
                (radius1 + radius2 * cos(beta + deltaBeta)) * sin(alpha)));
            points.push_back(Point((radius1 + radius2 * cos(beta + deltaBeta)) * cos(alpha + deltaAlpha),
                radius2 * sin(beta + deltaBeta),
                (radius1 + radius2 * cos(beta + deltaBeta)) * sin(alpha + deltaAlpha)));

            normals.push_back(normalize(Point((radius1 + radius2 * cos(beta)) * cos(alpha),
                radius2 * sin(beta),
                (radius1 + radius2 * cos(beta)) * sin(alpha))));
            normals.push_back(normalize(Point((radius1 + radius2 * cos(beta + deltaBeta)) * cos(alpha), 
                radius2 * sin(beta + deltaBeta),
                (radius1 + radius2 * cos(beta + deltaBeta)) * sin(alpha))));
            normals.push_back(normalize(Point((radius1 + radius2 * cos(beta + deltaBeta)) * cos(alpha + deltaAlpha),
                radius2 * sin(beta + deltaBeta),
                (radius1 + radius2 * cos(beta + deltaBeta)) * sin(alpha + deltaAlpha))));

            tex_coords.push_back(Point(t1, t3, 0));
            tex_coords.push_back(Point(t1, t4, 0));
            tex_coords.push_back(Point(t2, t4, 0));
        }
    }
    
	

    return std::make_tuple(points, normals, tex_coords);
}
