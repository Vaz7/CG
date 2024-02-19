#include "../headers/generator/patches.hpp"
#include "../headers/common/point.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>

const std::string _3D_path = "../3DFiles/";

Patches::Patches(std::string filename, int t_level) {

    tesselation = t_level;
    std::ifstream file(_3D_path + filename);

    if(!file) {
        throw std::runtime_error("Failded to load file " + filename);
    }

    std::string line;
    getline(file, line);
    patch_num = std::stoi(line);

    for (int i = 0; i < patch_num; i++) {
        getline(file, line);
        std::stringstream p(line);
        int counter = 0;

        while (p.good()) {
            std::string value;
            getline(p, value, ',');
            patch_indices.push_back(std::stoi(value));
            counter++;
        }

        if (counter != 16) {
            throw std::runtime_error("Invalid patch provided! Line " + std::to_string(i+1) + 
                                     " has incorrect number of indices. (" + std::to_string(counter) +
                                     " instead of 16)");
        }
    }

    getline(file, line);
    ctrl_points_num = std::stoi(line);

    for (int i = 0; i < ctrl_points_num; i++) {
        getline(file, line);
        std::stringstream ss(line);
        char comma;
        float x, y, z;

        ss >> x >> comma >> y >> comma >> z;
        control_points.push_back(std::move(Point(x,y,z)));
    }

    file.close();
}

float M[4][4] = {
    {-1, 3, -3, 1},
    {3, -6, 3, 0},
    {-3, 3, 0, 0},
    {1, 0, 0, 0}
};

void pre_calc_matrices(float M[4][4], Point P[4][4], Point A[4][4]) {

    Point temp[4][4];
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Point r;

            for (int k = 0; k < 4; k++) {
                r = r + P[j][k] * M[i][k];
            }

            temp[i][j] = r;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Point r;

            for (int k = 0; k < 4; k++) {
                r = r + temp[i][k] * M[k][j];
            }

            A[i][j] = r;
        }
    }
}

Point cross_patch(Point a, Point b) {
    return Point(a.getY() * b.getZ() - a.getZ() * b.getY(),
                 a.getZ() * b.getX() - a.getX() * b.getZ(),
                 a.getX() * b.getY() - a.getY() * b.getX()
                );
}

Point normalize_patch(Point a) {

    float l = sqrt(a.getX() * a.getX() + a.getY() * a.getY() + a.getZ() * a.getZ());

    return a / l;
}

Point bezier_surf_point(float u, float v, Point A[4][4]) {

    Point result;

    const float T_u[4] = {u * u * u, u * u, u, 1.0};
    const float T_v[4] = {v * v * v, v * v, v, 1.0};
    Point temp[4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i] = temp[i] + A[j][i] * T_u[j];
        }
    }

    for (int i = 0; i < 4; i++) {
        result = result + temp[i] * T_v[i];
    }
    
    return result;
}

Point computeNormal_patch(float u, float v, Point A[4][4]) {

    Point r_u;
    Point r_v;
    Point res_n;

    const float T_u[4] = {u * u * u, u * u, u, 1.0};
    const float T_v[4] = {v * v * v, v * v, v, 1.0};
    const float dT_u[4] = {3 * u * u, 2 * u, 1.0, 0.0};
    const float dT_v[4] = {3 * v * v, 2 * v, 1.0, 0.0};

    Point temp_u[4];
    Point temp_v[4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp_u[i] = temp_u[i] + A[j][i] * dT_u[j];
            temp_v[i] = temp_v[i] + A[j][i] * T_u[j];
        }
    }

    for (int i = 0; i < 4; i++) {
        r_u = r_u + temp_u[i] * T_v[i];
        r_v = r_v + temp_v[i] * dT_v[i];
    }

    return normalize_patch(cross_patch(r_u, r_v));
}

void Patches::set_up_bezier() {

    Point A[4][4];
    float t_level = 1.0 / tesselation;

    for (int i = 0; i < patch_num; i++) {

        Point P[4][4];  
        int counter = -1;
        
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                counter++;
                
                P[j][k] = control_points[patch_indices[counter + i * 16]];
            }
        }

        pre_calc_matrices(M, P, A);

        for (int u = 0; u < tesselation; u++) {
            for (int v = 0; v < tesselation; v++) {

                Point p0 = bezier_surf_point(u * t_level, v * t_level, A);
                Point p1 = bezier_surf_point(u * t_level, (v+1) * t_level, A);
                Point p2 = bezier_surf_point((u+1) * t_level, v * t_level, A);
                Point p3 = bezier_surf_point((u+1) * t_level, (v+1) * t_level, A);

                Point n0 = computeNormal_patch(u * t_level, v * t_level, A);
                Point n1 = computeNormal_patch(u * t_level, (v+1) * t_level, A);
                Point n2 = computeNormal_patch((u+1) * t_level, v * t_level, A);
                Point n3 = computeNormal_patch((u+1) * t_level, (v+1) * t_level, A);

                float t1 = 1 - (u / (float)tesselation);
                float t2 = 1 - ((u+1) / (float)tesselation);
                float t3 = v / (float)tesselation;
                float t4 = (v+1) / (float)tesselation;

                points.push_back(p2);
                points.push_back(p3);
                points.push_back(p1);

                normals.push_back(n2);
                normals.push_back(n3);
                normals.push_back(n1);

                tex_coords.push_back(Point(t2, t3, 0));
                tex_coords.push_back(Point(t2, t4, 0));
                tex_coords.push_back(Point(t1, t4, 0));

                points.push_back(p1);
                points.push_back(p0);
                points.push_back(p2);

                normals.push_back(n1);
                normals.push_back(n0);
                normals.push_back(n2);

                tex_coords.push_back(Point(t1, t4, 0));
                tex_coords.push_back(Point(t1, t3, 0));
                tex_coords.push_back(Point(t2, t3, 0));
            }
        }
    }  
} 

void Patches::dump_to_3D_file(std::string filename) {

    std::ofstream file(_3D_path + filename);
    for(int i = 0; i < points.size(); i++) {
        file << points[i].toString() + ' ' + normals[i].toString() + ' ' + tex_coords[i].toString() << std::endl;
    }

    file.close();
}
