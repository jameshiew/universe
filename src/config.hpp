//
// Created by James Hiew on 09/12/2017.
//

#ifndef UNIVERSE_CONFIG_H
#define UNIVERSE_CONFIG_H

#import "camera.hpp"

typedef struct Application {
    GLFWwindow *window;
    Camera *camera;
    bool paused;
} Application;
extern Application A;

#define DEFAULT_WINDOW_WIDTH 1024
#define DEFAULT_WINDOW_HEIGHT 768

#endif //UNIVERSE_CONFIG_H
