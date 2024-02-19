#include "../headers/generator/box.hpp"

using namespace std;

Box::Box(float len, int g) {
    length = len;
    grid = g;
}

std::tuple<std::vector<Point>, std::vector<Point>, std::vector<Point>> Box::point_generator() {

    std::vector<Point> points;
    std::vector<Point> normals;
    std::vector<Point> tex_coords;

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

            // Base superior
            points.push_back(Point(px, h_size, pz2));
            points.push_back(Point(px, h_size, pz));
            points.push_back(Point(px2, h_size, pz));

            for (int i = 0; i < 3; i++) normals.push_back(Point(0,1,0));

            tex_coords.push_back(Point(t3, t2, 0));
            tex_coords.push_back(Point(t3, t1, 0));
            tex_coords.push_back(Point(t4, t1, 0));

            points.push_back(Point(px2, h_size, pz));
            points.push_back(Point(px2, h_size, pz2));
            points.push_back(Point(px, h_size, pz2));

            for (int i = 0; i < 3; i++) normals.push_back(Point(0,1,0));

            tex_coords.push_back(Point(t4, t1, 0));
            tex_coords.push_back(Point(t4, t2, 0));
            tex_coords.push_back(Point(t3, t2, 0));

            // Base inferior
            points.push_back(Point(px2, -h_size, pz));
            points.push_back(Point(px, -h_size, pz));
            points.push_back(Point(px, -h_size, pz2));

            for (int i = 0; i < 3; i++) normals.push_back(Point(0,-1,0));

            tex_coords.push_back(Point(t4, t1, 0));
            tex_coords.push_back(Point(t3, t1, 0));
            tex_coords.push_back(Point(t3, t2, 0));

            points.push_back(Point(px, -h_size, pz2));
            points.push_back(Point(px2, -h_size, pz2));
            points.push_back(Point(px2, -h_size, pz));

            for (int i = 0; i < 3; i++) normals.push_back(Point(0,-1,0));

            tex_coords.push_back(Point(t3, t2, 0));
            tex_coords.push_back(Point(t4, t2, 0));
            tex_coords.push_back(Point(t4, t1, 0));

            // Lateral 1 - virada para a trás
            points.push_back(Point(-h_size, px, pz2));
            points.push_back(Point(-h_size, px, pz));
            points.push_back(Point(-h_size, px2, pz));

            for (int i = 0; i < 3; i++) normals.push_back(Point(-1,0,0));

            tex_coords.push_back(Point(1-t2, 1-t3, 0));
            tex_coords.push_back(Point(1-t1, 1-t3, 0));
            tex_coords.push_back(Point(1-t1, 1-t4, 0));

            points.push_back(Point(-h_size, px2, pz));
            points.push_back(Point(-h_size, px2, pz2));
            points.push_back(Point(-h_size, px, pz2));

            for (int i = 0; i < 3; i++) normals.push_back(Point(-1,0,0));

            tex_coords.push_back(Point(1-t1, 1-t4, 0));
            tex_coords.push_back(Point(1-t2, 1-t4, 0));
            tex_coords.push_back(Point(1-t2, 1-t3, 0));

            // Lateral 2 - virada para a frente
            points.push_back(Point(h_size, px2, pz));
            points.push_back(Point(h_size, px, pz));
            points.push_back(Point(h_size, px, pz2));

            for (int i = 0; i < 3; i++) normals.push_back(Point(1,0,0));

            tex_coords.push_back(Point(1-t1, 1-t4, 0));
            tex_coords.push_back(Point(1-t1, 1-t3, 0));
            tex_coords.push_back(Point(1-t2, 1-t3, 0));

            points.push_back(Point(h_size, px, pz2));
            points.push_back(Point(h_size, px2, pz2));
            points.push_back(Point(h_size, px2, pz));

            for (int i = 0; i < 3; i++) normals.push_back(Point(1,0,0));

            tex_coords.push_back(Point(1-t2, 1-t3, 0));
            tex_coords.push_back(Point(1-t2, 1-t4, 0));
            tex_coords.push_back(Point(1-t1, 1-t4, 0));

            // Lateral 3 - virada para a esquerda
            points.push_back(Point(px, pz2, -h_size));
            points.push_back(Point(px, pz, -h_size));
            points.push_back(Point(px2, pz, -h_size));

            for (int i = 0; i < 3; i++) normals.push_back(Point(0,0,-1));

            tex_coords.push_back(Point(t3, t2, 0));
            tex_coords.push_back(Point(t3, t1, 0));
            tex_coords.push_back(Point(t4, t1, 0));

            points.push_back(Point(px2, pz, -h_size));
            points.push_back(Point(px2, pz2, -h_size));
            points.push_back(Point(px, pz2, -h_size));

            for (int i = 0; i < 3; i++) normals.push_back(Point(0,0,-1));

            tex_coords.push_back(Point(t4, t1, 0));
            tex_coords.push_back(Point(t4, t2, 0));
            tex_coords.push_back(Point(t3, t2, 0));

            // Lateral 4 - virada para a direita
            points.push_back(Point(px2, pz, h_size));
            points.push_back(Point(px, pz, h_size));
            points.push_back(Point(px, pz2, h_size));

            for (int i = 0; i < 3; i++) normals.push_back(Point(0,0,1));

            tex_coords.push_back(Point(t4, t1, 0));
            tex_coords.push_back(Point(t3, t1, 0));
            tex_coords.push_back(Point(t3, t2, 0));

            points.push_back(Point(px, pz2, h_size));
            points.push_back(Point(px2, pz2, h_size));
            points.push_back(Point(px2, pz, h_size));

            for (int i = 0; i < 3; i++) normals.push_back(Point(0,0,1));

            tex_coords.push_back(Point(t3, t2, 0));
            tex_coords.push_back(Point(t4, t2, 0));
            tex_coords.push_back(Point(t4, t1, 0));
        }
    }

    return std::make_tuple(points, normals, tex_coords);
}