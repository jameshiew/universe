//
// Created by James Hiew on 09/12/2017.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "config.h"
#include "render.h"

// GLFWwindow argument is because this function can be provided as a callback to
// glfwSetFramebufferSizeCallback()
void resize_viewport(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow *create_window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        fputs("Failed to create GLFW window", stderr);
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize_viewport);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fputs("Failed to initialize GLAD", stderr);
        return NULL;
    }
    return window;
}
