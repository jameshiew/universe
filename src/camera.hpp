//
// Created by James Hiew on 13/12/2017.
//

#ifndef UNIVERSE_CAMERA_H
#define UNIVERSE_CAMERA_H

#include <glm/glm.hpp>

typedef struct Camera {
    glm::vec3 position;
    glm::vec3 behind;  // actually a vector pointing opposite to what we are looking at...
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 front;
    float yaw;
    float pitch;
    float roll;
    float speed;
    float sensitivity;
    double lastX;
    double lastY;
} Camera;

Camera *Camera_new();
void Camera_debug(Camera *camera);

#endif //UNIVERSE_CAMERA_H
