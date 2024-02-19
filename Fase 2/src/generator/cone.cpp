#include "../headers/generator/cone.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

Cone::Cone(float r, float h, int slice, int stack) {
    radius = r;
    height = h;
    slices = slice;
    stacks = stack;
}

vector<Point> Cone::point_generator() {

    vector<Point> points;


    float stack_height = height/stacks; 

    float angle = (2 * M_PI) / slices;
    float px = 0, pz = 0;
    float p2x = 0, p2z = 0;
    float p3x = 0, p3z = 0;
    float p4x = 0, p4z = 0;

    for (int i = 0; i < slices; i++) {//ciclo para desenhar a base e os lados
        
        px = radius * sin(angle * i);
        pz = radius * cos(angle * i);
        p2x = radius * sin(angle * (i+1));
        p2z = radius * cos(angle * (i+1));
        
        
        //base 
        points.push_back(Point(p2x,0.0f,p2z));
        points.push_back(Point(px,0.0f,pz));
        points.push_back(Point(0.0f,0.0f,0.0f));
    }

    for(int i = 0; i < stacks; i++){//ciclo para desenhar as stacks
        for(int j = 0; j < slices; j++){
            
            px = (radius - (radius/stacks) * i) * sin(angle * j);
            pz = (radius - (radius/stacks) * i) * cos(angle * j);
            p2x = (radius - (radius/stacks) * i) * sin(angle * (j+1));
            p2z = (radius - (radius/stacks) * i) * cos(angle * (j+1));

            p3x = (radius - (radius/stacks) * (i+1)) * sin(angle * j);
            p3z = (radius - (radius/stacks) * (i+1)) * cos(angle * j);
            p4x = (radius - (radius/stacks) * (i+1)) * sin(angle * (j+1));
            p4z = (radius - (radius/stacks) * (i+1)) * cos(angle * (j+1));

            points.push_back(Point(px,stack_height*i,pz));
            points.push_back(Point(p2x,stack_height*i,p2z));
            points.push_back(Point(p3x,stack_height*(i+1),p3z));
  
            points.push_back(Point(p4x,stack_height*(i+1),p4z));
            points.push_back(Point(p3x,stack_height*(i+1),p3z));
            points.push_back(Point(p2x,stack_height*i,p2z));

        }
        
    }

    return points;
}