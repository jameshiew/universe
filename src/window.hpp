//
// Created by James Hiew on 13/12/2017.
//

#ifndef UNIVERSE_WINDOW_H
#define UNIVERSE_WINDOW_H

#include <GLFW/glfw3.h>
#include "config.hpp"
#include "camera.hpp"


typedef struct Window {
    GLFWwindow *_glfw;
    int width;
    int height;
    Camera *camera;
    bool paused;
} Window;

GLFWwindow *initWindow();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

extern Window WINDOW;

#endif //UNIVERSE_WINDOW_H
