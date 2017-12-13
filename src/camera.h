//
// Created by James Hiew on 13/12/2017.
//

#ifndef UNIVERSE_CAMERA_H
#define UNIVERSE_CAMERA_H

#include <math_3d.h>

typedef struct Camera {
    vec3_t position;
    vec3_t direction;  // actually a vector pointing opposite to what we are looking at...
    vec3_t right;
    vec3_t up;
    float speed;
} Camera;

Camera *Camera_new();
#endif //UNIVERSE_CAMERA_H
