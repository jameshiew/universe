//
// Created by James Hiew on 13/12/2017.
//
#include <stdlib.h>

#include "camera.h"

Camera *Camera_new() {
    Camera *camera = malloc(sizeof(Camera));
    camera->position = vec3(0.0f, 0.0f, 3.0f);
    camera->direction = v3_norm(v3_sub(camera->position, vec3(0.0f, 0.0f, 0.0f)));
    vec3_t up = vec3(0.0f, 1.0f, 0.0f);
    camera->right = v3_norm(v3_cross(up, camera->direction));
    camera->up = v3_cross(camera->direction, camera->right);
    camera->speed = 2.5f;
    return camera;
}