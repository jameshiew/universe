//
// Created by James Hiew on 13/12/2017.
//

#ifndef UNIVERSE_CAMERA_H
#define UNIVERSE_CAMERA_H

#include <glm/glm.hpp>

typedef struct Camera {
    glm::vec3 position;
    glm::vec3 behind;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 front;
    float yaw;
    float pitch;
    float roll;

    float speed;
    float sensitivity;

    float lastX;
    float lastY;

    // rendering options
    bool wireframe;
} Camera;

Camera *Camera_new();
void Camera_debug(Camera *camera);

#endif //UNIVERSE_CAMERA_H
