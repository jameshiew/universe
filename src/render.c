//
// Created by James Hiew on 09/12/2017.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stb_image.h>

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

void print_debug_output() {
    GLint numberOfAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numberOfAttributes);
    fprintf(stdout, "Maximum vertex attributes: %d\n", numberOfAttributes);
}

GLuint load_texture(const char *texturePath) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_uc *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        fputs("Failed to load texture", stderr);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}
