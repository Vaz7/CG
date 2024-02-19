#include "../headers/generator/box.hpp"
#include "../headers/generator/plane.hpp"
#include "../headers/generator/sphere.hpp"
#include "../headers/generator/cone.hpp"
#include "../headers/generator/torus.hpp"
#include "../headers/generator/primitive.hpp"
#include "../headers/generator/patches.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;
// TODO: Mudar diagonais no Cone para ficar igual às do stor! Mudar angulo da Esfera para ficar igual ao do stor!

const std::string _3D_path = "../3DFiles/";

void create_3D_file(Primitive* primitive, string filename) {
    
    ofstream file(_3D_path + filename);
    auto [points, normals, tex_coords] = (*primitive).point_generator();
    for(int i = 0; i < points.size(); i++) {
        file << points[i].toString() + ' ' + normals[i].toString() + ' ' + tex_coords[i].toString() << std::endl;
    }
}

void primitive_handler(int arg_numb, char** data) {
    string primitive_name = data[1];

    if (primitive_name == "box" && arg_numb == 5) {
        
        float length = stof(data[2]);
        int grid = stoi(data[3]);
        Box box(length, grid);

        create_3D_file(&box, data[4]);
    }
    else if (primitive_name == "sphere" && arg_numb == 6) {

        float radius = stof(data[2]);
        int slices = stoi(data[3]);
        int stacks = stoi(data[4]);
        Sphere sphere(radius, slices, stacks);

        create_3D_file(&sphere, data[5]);
    }
    else if (primitive_name == "plane" && arg_numb == 5) {

        float length = stof(data[2]);
        int grid = stoi(data[3]);
        Plane plane(length, grid);

        create_3D_file(&plane, data[4]);
    }
    else if (primitive_name == "cone" && arg_numb == 7) {

        float radius = stof(data[2]);
        float height = stof(data[3]);
        int slices = stoi(data[4]);
        int stacks = stoi(data[5]);
        Cone cone(radius,height, slices, stacks);

        create_3D_file(&cone, data[6]);
    }
    else if (primitive_name == "torus" && arg_numb == 7){

        float radius1 = stof(data[2]);
        float radius2 = stof(data[3]);
        int slices = stoi(data[4]);
        int stacks = stoi(data[5]);
        Torus torus(radius1,radius2,slices,stacks);

        create_3D_file(&torus, data[6]);
    }
    else {
        cout << primitive_name + " is not a valid solid name!" << endl;
    }
}

void patch_handler(int arg_num, char** data) {
    if (arg_num != 5) {
        std::cout << "Invalid number of arguments provided!" << std::endl;
        return;
    }
    
    std::string input_file = data[0];
    std::string output_file = data[2];
    int t_level = stoi(data[1]);

    try {
        Patches patches = Patches(input_file, t_level);
        patches.set_up_bezier();
        patches.dump_to_3D_file(output_file);
    }
    catch(std::runtime_error e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
}

int main(int argc, char** argv) {

    if (argc > 1) {
        std::string primitive_name = argv[1];
        if (primitive_name == "patch") {
            patch_handler(argc, argv+2);
        }
        else {
            primitive_handler(argc, argv);
        }
    }
    else {
        cout << "Not enough arguments provided!" << endl;
    }

    return 1;
}
