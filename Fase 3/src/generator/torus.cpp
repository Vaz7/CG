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

vector<Point> Torus::point_generator() {

    vector<Point> points;

    float deltaAlpha = (M_PI * 2) / slices;
    float deltaBeta = (M_PI * 2) / stacks;
    float alpha = 0.0f;
    float beta = 0.0f;
    Point* p1, * p2, * p3, * p4;

    for (int i = 0; i < slices; i++) {
        alpha = i * deltaAlpha;

        for (int j = 0; j < stacks; j++) {
            beta = j * deltaBeta;

            points.push_back(Point((radius1 + radius2 * cos(beta + deltaBeta)) * cos(alpha + deltaAlpha),
                radius2 * sin(beta + deltaBeta),
                (radius1 + radius2 * cos(beta + deltaBeta)) * sin(alpha + deltaAlpha)));
            points.push_back(Point((radius1 + radius2 * cos(beta)) * cos(alpha + deltaAlpha), 
                radius2 * sin(beta),
                (radius1 + radius2 * cos(beta)) * sin(alpha + deltaAlpha)));
            points.push_back(Point((radius1 + radius2 * cos(beta)) * cos(alpha),
                radius2 * sin(beta),
                (radius1 + radius2 * cos(beta)) * sin(alpha)));

            points.push_back(Point((radius1 + radius2 * cos(beta)) * cos(alpha),
                radius2 * sin(beta),
                (radius1 + radius2 * cos(beta)) * sin(alpha)));
            points.push_back(Point((radius1 + radius2 * cos(beta + deltaBeta)) * cos(alpha), 
                radius2 * sin(beta + deltaBeta),
                (radius1 + radius2 * cos(beta + deltaBeta)) * sin(alpha)));
            points.push_back(Point((radius1 + radius2 * cos(beta + deltaBeta)) * cos(alpha + deltaAlpha),
                radius2 * sin(beta + deltaBeta),
                (radius1 + radius2 * cos(beta + deltaBeta)) * sin(alpha + deltaAlpha)));
        }
    }
    
	

    return points;
}
