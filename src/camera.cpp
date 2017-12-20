//
// Created by James Hiew on 13/12/2017.
//
#include <cstdlib>
#include <cstdio>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"
#include "space.hpp"
#include "config.hpp"

Camera::Camera() {
    position = glm::vec3(0.0f, 2.0f, 2.0f);
    behind = glm::normalize(position);
    right = glm::normalize(glm::cross(UP, behind));
    up = glm::cross(behind, right);
    front = -position;

    pitch = 0.0f;
    yaw = (float) -M_PI_2;
    roll = 0.0f;

    // TODO: camera controller
    speed = 2.5f;
    sensitivity = 0.01f;

    lastX = (float) DEFAULT_WINDOW_WIDTH / 2.f;
    lastY = (float) DEFAULT_WINDOW_HEIGHT / 2.f;

    wireframe = false;
}

void Camera_debug(Camera *camera) {
    fputs("### CAMERA DETAILS\n", stdout);
    printf("Position: (%f, %f, %f)\n", camera->position.x, camera->position.y, camera->position.z);
    printf("Front: (%f, %f, %f)\n", camera->front.x, camera->front.y, camera->front.z);
    printf("Behind: (%f, %f, %f)\n", camera->behind.x, camera->behind.y, camera->behind.z);
    printf("Up: (%f, %f, %f)\n", camera->up.x, camera->up.y, camera->up.z);
    printf("Right: (%f, %f, %f)\n", camera->right.x, camera->right.y, camera->right.z);
    printf("Last X/Last Y: %f/%f\n", camera->lastX, camera->lastY);
    printf("Pitch/Yaw/Roll: %f/%f/%f\n\n", camera->pitch, camera->yaw, camera->roll);
}
