#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>

#include "input.h"
#include "util.h"
#include "window.h"

void processInput(GLFWwindow *window, Camera *camera, double deltaTime) {
    double speed = camera->speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->position = v3_add(camera->position, v3_muls(camera->front, speed));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->position = v3_sub(camera->position, v3_muls(camera->front, speed));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->position = v3_sub(camera->position, v3_muls(v3_norm(v3_cross(camera->front, camera->up)), speed));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->position = v3_add(camera->position, v3_muls(v3_norm(v3_cross(camera->front, camera->up)), speed));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera->position = v3_add(camera->position, v3_muls(camera->up, speed));
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        camera->position = v3_sub(camera->position, v3_muls(camera->up, speed));
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    Window *WINDOW = glfwGetWindowUserPointer(window);
    Camera *camera = WINDOW->camera;

    float xoffset = xpos - camera->lastX;
    float yoffset = camera->lastY - ypos; // reversed since y-coordinates range from bottom to top
    camera->lastX = xpos;
    camera->lastY = ypos;

    xoffset *= camera->sensitivity;
    yoffset *= camera->sensitivity;

    camera->yaw   += xoffset;
    camera->pitch += yoffset;
    if (camera->pitch > 89.0f) {
        camera->pitch = 89.0f;
    }
    if (camera->pitch < -89.0f) {
        camera->pitch = -89.0f;
    }

    vec3_t front = {0.0f, 0.0f, 0.0f};
    front.x = cosf(radians(camera->pitch)) * cosf(radians(camera->yaw));
    front.y = sinf(radians(camera->pitch));
    front.z = cosf(radians(camera->pitch)) * sinf(radians(camera->yaw));
    camera->front = v3_norm(front);
    camera->right = v3_norm(v3_cross(camera->front, vec3(0.0f, 1.0f, 0.0f)));
    camera->up = v3_norm(v3_cross(camera->right, camera->front));
}
