//
// Created by James Hiew on 08/12/2017.
//

#ifndef UNIVERSE_INPUT_H
#define UNIVERSE_INPUT_H

#include <GLFW/glfw3.h>
#include "camera.hpp"

void process_input(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

#endif //UNIVERSE_INPUT_H
