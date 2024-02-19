#include "../headers/generator/plane.hpp"

using namespace std;

Plane::Plane(float len, int g) {
    length = len;
    grid = g;
}

vector<Point> Plane::point_generator() {

    vector<Point> points;

    float size = length / (float)grid;
    float h_size = length / 2.0;
    float px = 0, pz = 0, px2 = 0, pz2 = 0;

    for(int i = 0; i < grid; i++) {
        for(int j = 0; j < grid; j++) {

            px = -h_size + (size * j);      // x à esquerda <- num plano 2D
            pz = h_size - (size * i);       // z a baixo    <- num plano 2D
            px2 = -h_size + (size * (j+1)); // x à direita  <- num plano 2D
            pz2 = h_size - (size * (i+1));  // z a cima     <- num plano 2D

            // Face superior do plano
            points.push_back(Point(px, 0, pz2));
            points.push_back(Point(px, 0, pz));
            points.push_back(Point(px2, 0, pz));

            points.push_back(Point(px2, 0, pz));
            points.push_back(Point(px2, 0, pz2));
            points.push_back(Point(px, 0, pz2));

            // Face inferior do plano
            points.push_back(Point(px2, 0, pz));
            points.push_back(Point(px, 0, pz));
            points.push_back(Point(px, 0, pz2));

            points.push_back(Point(px, 0, pz2));
            points.push_back(Point(px2, 0, pz2));
            points.push_back(Point(px2, 0, pz));
        }
    }

    return points;
}