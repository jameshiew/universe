//
// Created by James Hiew on 13/12/2017.
//
#include <stdlib.h>
#include <stdio.h>

#include "camera.hpp"
#include "main.hpp"

Camera *Camera_new() {
    Camera *camera = (Camera *) malloc(sizeof(Camera));
    camera->position = vec3(0.0f, 0.0f, 3.0f);
    camera->behind = v3_norm(v3_sub(camera->position, vec3(0.0f, 0.0f, 0.0f)));
    vec3_t up = vec3(0.0f, 1.0f, 0.0f);
    camera->right = v3_norm(v3_cross(up, camera->behind));
    camera->up = v3_cross(camera->behind, camera->right);
    camera->front = vec3(0.0f, 0.0f, -1.0f);
    camera->speed = 2.5f;
    camera->pitch = 0.0f;
    camera->yaw = -90.0f;
    camera->roll = 0.0f;
    camera->sensitivity = 0.1f;
    camera->lastX = WINDOW.width / 2;
    camera->lastY = WINDOW.height / 2;
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
