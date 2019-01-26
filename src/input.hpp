#ifndef UNIVERSE_INPUT_H
#define UNIVERSE_INPUT_H

#include <GLFW/glfw3.h>
#include "camera.hpp"

void process_input(GLFWwindow *window, Camera *camera, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

#endif //UNIVERSE_INPUT_H
