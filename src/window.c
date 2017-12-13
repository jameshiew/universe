//
// Created by James Hiew on 13/12/2017.
//

#include <glad/glad.h>
#include <stdio.h>
#include "window.h"

Window WINDOW = {
    ._glfw = 0,
    .width = DEFAULT_WINDOW_WIDTH,
    .height = DEFAULT_WINDOW_HEIGHT
};

void resize_viewport(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    WINDOW.width = width;
    WINDOW.height = height;
}

GLFWwindow *initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(WINDOW.width, WINDOW.height, "Universe", NULL, NULL);
    if (window == NULL) {
        fputs("Failed to create GLFW window", stderr);
        glfwTerminate();
    }
    glfwSetWindowUserPointer(window, &WINDOW);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize_viewport);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fputs("Failed to initialize GLAD", stderr);
        glfwTerminate();
    }
    return window;
}
