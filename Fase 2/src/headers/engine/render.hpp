#ifndef RENDER_HEADER
#define RENDER_HEADER

#include <string>

// Struct que armazena os valores das dimensões da janela
struct window {
    float w_width;
    float w_height;
};

// Struct com que armazena os valores de todos os elementos da câmera
struct camera {
    float pos_x;
    float pos_y;
    float pos_z;
    float c_radius;
    float look_x;
    float look_y;
    float look_z;
    float up_x;
    float up_y;
    float up_z;
    float fov;
    float near;
    float far;
};

void render(int, char**);

#endif