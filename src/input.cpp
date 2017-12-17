#include <GLFW/glfw3.h>

#include "input.hpp"
#include "window.hpp"
#include "space.hpp"

void process_input(GLFWwindow *window, Camera *camera, float deltaTime) {
    float speed = camera->speed * deltaTime;
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
    auto camera = (Camera *)glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glfwSetCursorPos(window, (double) width / 2.f, (double) height / 2.f);
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    } else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera->wireframe = !camera->wireframe;
    }
}

bool firstMouse = true;
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    auto camera = (Camera *)glfwGetWindowUserPointer(window);
    auto xposf = (float) xpos;
    auto yposf = (float) ypos;
    if (firstMouse) {
        camera->lastX = xposf;
        camera->lastY = yposf;
        firstMouse = false;
    }

    float xoffset = xposf - camera->lastX;
    float yoffset = camera->lastY - yposf; // reversed since y-coordinates range from bottom to top
    camera->lastX = xposf;
    camera->lastY = yposf;

    xoffset *= camera->sensitivity;
    yoffset *= camera->sensitivity;

    camera->yaw   += xoffset;
    camera->pitch += yoffset;
    if (camera->pitch > M_PI_2) {
        camera->pitch = (float) M_PI_2;
    } else if (camera->pitch < -M_PI_2) {
        camera->pitch = (float) -M_PI_2;
    }

    camera->front = glm::vec3(
            cosf(camera->pitch) * cosf(camera->yaw),
            sinf(camera->pitch),
            cosf(camera->pitch) * sinf(camera->yaw)
    );
    camera->right = glm::normalize(glm::cross(camera->front, UP));
    camera->up = glm::normalize(glm::cross(camera->right, camera->front));
}
