#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "input.h"

void processInput(GLFWwindow *window, Camera *camera, float deltaTime) {
    float speed = camera->speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    vec3_t cameraFront = vec3(0.0f, 0.0f, -1.0f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->position = v3_add(camera->position, v3_muls(cameraFront, speed));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->position = v3_sub(camera->position, v3_muls(cameraFront, speed));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->position = v3_sub(camera->position, v3_muls(v3_norm(v3_cross(cameraFront, camera->up)), speed));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->position = v3_add(camera->position, v3_muls(v3_norm(v3_cross(cameraFront, camera->up)), speed));
    }
}