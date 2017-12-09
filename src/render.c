//
// Created by James Hiew on 09/12/2017.
//

#include "render.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}