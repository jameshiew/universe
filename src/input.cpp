#include <GLFW/glfw3.h>

#include "input.hpp"
#include "util.hpp"
#include "window.hpp"

void processInput(GLFWwindow *window, double deltaTime) {
    auto *WINDOW = (Window *) glfwGetWindowUserPointer(window);
    Camera *camera = WINDOW->camera;
    float speed = camera->speed * (float) deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed *= 2.f;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->position = camera->position + camera->front * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->position = camera->position - camera->front * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->position = camera->position - glm::normalize(glm::cross(camera->front, camera->up)) * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->position = camera->position + glm::normalize(glm::cross(camera->front, camera->up)) * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera->position = camera->position + camera->up * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        camera->position = camera->position - camera->up * speed;
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto *WINDOW = (Window *) glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        if (WINDOW->paused) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        WINDOW->paused = !WINDOW->paused;
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    auto *WINDOW = (Window *) glfwGetWindowUserPointer(window);
    if (WINDOW->paused) {
        return;
    }
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

    glm::vec3 front = {0.0f, 0.0f, 0.0f};
    front.x = cosf(radians(camera->pitch)) * cosf(radians(camera->yaw));
    front.y = sinf(radians(camera->pitch));
    front.z = cosf(radians(camera->pitch)) * sinf(radians(camera->yaw));
    camera->front = glm::normalize(front);
    camera->right = glm::normalize(glm::cross(camera->front, glm::vec3(0.0f, 1.0f, 0.0f)));
    camera->up = glm::normalize(glm::cross(camera->right, camera->front));
}
