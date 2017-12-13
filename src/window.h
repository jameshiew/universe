//
// Created by James Hiew on 13/12/2017.
//

#ifndef UNIVERSE_WINDOW_H
#define UNIVERSE_WINDOW_H

#include <GLFW/glfw3.h>
#include "config.h"
#include "camera.h"


typedef struct Window {
    GLFWwindow *_glfw;
    int width;
    int height;
    Camera *camera;
} Window;

GLFWwindow *initWindow();

#endif //UNIVERSE_WINDOW_H
