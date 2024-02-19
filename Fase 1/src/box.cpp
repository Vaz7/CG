#include "./headers/box.hpp"

using namespace std;

Box::Box(float len, int g) {
    length = len;
    grid = g;
}

vector<Point> Box::point_generator() {

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

            // Base superior
            points.push_back(Point(px, h_size, pz2));
            points.push_back(Point(px, h_size, pz));
            points.push_back(Point(px2, h_size, pz));

            points.push_back(Point(px2, h_size, pz));
            points.push_back(Point(px2, h_size, pz2));
            points.push_back(Point(px, h_size, pz2));

            // Base inferior
            points.push_back(Point(px2, -h_size, pz));
            points.push_back(Point(px, -h_size, pz));
            points.push_back(Point(px, -h_size, pz2));

            points.push_back(Point(px, -h_size, pz2));
            points.push_back(Point(px2, -h_size, pz2));
            points.push_back(Point(px2, -h_size, pz));

            // Lateral 1 - virada para a frente
            points.push_back(Point(-h_size, px, pz2));
            points.push_back(Point(-h_size, px, pz));
            points.push_back(Point(-h_size, px2, pz));

            points.push_back(Point(-h_size, px2, pz));
            points.push_back(Point(-h_size, px2, pz2));
            points.push_back(Point(-h_size, px, pz2));

            // Lateral 2 - virada para trás
            points.push_back(Point(h_size, px2, pz));
            points.push_back(Point(h_size, px, pz));
            points.push_back(Point(h_size, px, pz2));

            points.push_back(Point(h_size, px, pz2));
            points.push_back(Point(h_size, px2, pz2));
            points.push_back(Point(h_size, px2, pz));

            // Lateral 3 - virada para a esquerda
            points.push_back(Point(px, pz2, -h_size));
            points.push_back(Point(px, pz, -h_size));
            points.push_back(Point(px2, pz, -h_size));

            points.push_back(Point(px2, pz, -h_size));
            points.push_back(Point(px2, pz2, -h_size));
            points.push_back(Point(px, pz2, -h_size));

            // Lateral 4 - virada para a direita
            points.push_back(Point(px2, pz, h_size));
            points.push_back(Point(px, pz, h_size));
            points.push_back(Point(px, pz2, h_size));

            points.push_back(Point(px, pz2, h_size));
            points.push_back(Point(px2, pz2, h_size));
            points.push_back(Point(px2, pz, h_size));
        }
    }

    return points;
}