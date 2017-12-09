//
// Created by James Hiew on 09/12/2017.
//

#include "render.h"

// GLFWwindow argument is because this function can be provided as a callback to
// glfwSetFramebufferSizeCallback()
void resize_viewport(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}