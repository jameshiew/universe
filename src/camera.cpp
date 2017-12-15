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
#include "window.hpp"

Camera *Camera_new() {
    auto *camera = (Camera *) malloc(sizeof(Camera));
    camera->position = glm::vec3(0.0f, 2.0f, 2.0f);
    camera->behind = glm::normalize(camera->position);
    camera->right = glm::normalize(glm::cross(UP, camera->behind));
    camera->up = glm::cross(camera->behind, camera->right);
    camera->front = -camera->position;
    camera->speed = 2.5f;
    camera->pitch = 0.0f;
    camera->yaw = -90.0f;
    camera->roll = 0.0f;
    camera->sensitivity = 0.1f;
    camera->lastX = (float) DEFAULT_WINDOW_WIDTH / 2.f;
    camera->lastY = (float) DEFAULT_WINDOW_HEIGHT / 2.f;
    return camera;
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
