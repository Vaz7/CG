#include "../headers/generator/plane.hpp"

using namespace std;

Plane::Plane(float len, int g) {
    length = len;
    grid = g;
}

std::tuple<std::vector<Point>, std::vector<Point>, std::vector<Point>> Plane::point_generator() {

    vector<Point> points;
    vector<Point> normals;
    vector<Point> tex_coords;

    float size = length / (float)grid;
    float h_size = length / 2.0;
    float px = 0, pz = 0, px2 = 0, pz2 = 0;

    for(int i = 0; i < grid; i++) {
        for(int j = 0; j < grid; j++) {

            px = -h_size + (size * j);      // x à esquerda <- num plano 2D
            pz = h_size - (size * i);       // z a baixo    <- num plano 2D
            px2 = -h_size + (size * (j+1)); // x à direita  <- num plano 2D
            pz2 = h_size - (size * (i+1));  // z a cima     <- num plano 2D
            
            float t1 = i / (float)grid;
            float t2 = (i+1) / (float)grid;
            float t3 = j / (float)grid;
            float t4 = (j+1) / (float)grid;

            // Face superior do plano
            points.push_back(Point(px, 0, pz2));
            points.push_back(Point(px, 0, pz));
            points.push_back(Point(px2, 0, pz));
            
            for (int i = 0; i < 3; i++) normals.push_back(Point(0,1,0));

            tex_coords.push_back(Point(t3, t2, 0));
            tex_coords.push_back(Point(t3, t1, 0));
            tex_coords.push_back(Point(t4, t1, 0));

            points.push_back(Point(px2, 0, pz));
            points.push_back(Point(px2, 0, pz2));
            points.push_back(Point(px, 0, pz2));

            for (int i = 0; i < 3; i++) normals.push_back(Point(0,1,0));

            tex_coords.push_back(Point(t4, t1, 0));
            tex_coords.push_back(Point(t4, t2, 0));
            tex_coords.push_back(Point(t3, t2, 0));

            // Face inferior do plano
            points.push_back(Point(px2, 0, pz));
            points.push_back(Point(px, 0, pz));
            points.push_back(Point(px, 0, pz2));

            for (int i = 0; i < 3; i++) normals.push_back(Point(0,-1,0));

            tex_coords.push_back(Point(t4, t1, 0));
            tex_coords.push_back(Point(t3, t1, 0));
            tex_coords.push_back(Point(t3, t2, 0));

            points.push_back(Point(px, 0, pz2));
            points.push_back(Point(px2, 0, pz2));
            points.push_back(Point(px2, 0, pz));

            for (int i = 0; i < 3; i++) normals.push_back(Point(0,-1,0));

            tex_coords.push_back(Point(t3, t2, 0));
            tex_coords.push_back(Point(t4, t2, 0));
            tex_coords.push_back(Point(t4, t1, 0));
        }
    }

    return std::make_tuple(points, normals, tex_coords);
}