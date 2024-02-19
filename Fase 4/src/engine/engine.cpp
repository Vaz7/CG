#include "../headers/engine/render.hpp"
#include <iostream>

int main(int argc, char** argv) {

    if (argc == 2) {
        render(argc, argv);
    }
    else {
        std::cout << "Invalid number of arguments provided!" << std::endl;
    }

    return 1;
}