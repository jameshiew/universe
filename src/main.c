#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "input.h"
#include "shaders.h"
#include "render.h"
#include "polygon.h"
#include "window.h"
#include "main.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MATH_3D_IMPLEMENTATION
#include "math_3d.h"

int main() {
    GLFWwindow *window = initWindow();
    if (window == NULL) {
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    print_debug_output();

    if (FT_Init_FreeType(&library)) {
        fprintf(stderr, "Could not init freetype library\n");
        return 1;
    }
    if (FT_New_Face(library, "../../fonts/FreeSans.ttf", 0, &face)) {
        fprintf(stderr, "Could not open font\n");
        return 1;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);

    GLuint polygonShader = load_program("../../shaders/basic.vert", "../../shaders/basic.frag");

    polygon *p = polygon_new();
    GLuint texture = load_texture("../../textures/container.jpg");

    mat4_t model, view, projection;

    vec3_t cubePositions[] = {
        vec3( 0.0f,  0.0f,  0.0f),
        vec3( 2.0f,  5.0f, -15.0f),
        vec3(-1.5f, -2.2f, -2.5f),
        vec3(-3.8f, -2.0f, -12.3f),
        vec3( 2.4f, -0.4f, -3.5f),
        vec3(-1.7f,  3.0f, -7.5f),
        vec3( 1.3f, -2.0f, -2.5f),
        vec3( 1.5f,  2.0f, -2.5f),
        vec3( 1.5f,  0.2f, -1.5f),
        vec3(-1.3f,  1.0f, -1.5f),
    };

    glUseProgram(polygonShader);
    WINDOW.camera = Camera_new();
    glfwSetCursorPos(window, WINDOW.camera->lastX, WINDOW.camera->lastY);
    glfwSetCursorPosCallback(window, mouse_callback);
    double deltaTime, timeOfLastFrame = 0.0f;
    Camera_debug(WINDOW.camera);
    while (!glfwWindowShouldClose(window)) {
        // INPUT PROCESSING
        double timeValue = glfwGetTime();
        deltaTime = timeValue - timeOfLastFrame;
        timeOfLastFrame = timeValue;
        processInput(window, WINDOW.camera, deltaTime);

        // MATRICES
        projection = m4_perspective(45.0f, WINDOW.width / WINDOW.height, 0.1f, 100.0f);
        GLint projectionUniformLocation = glGetUniformLocation(polygonShader, "projection");
        glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, (const GLfloat *)&projection);

        view = m4_look_at(WINDOW.camera->position, v3_add(WINDOW.camera->position, WINDOW.camera->front), WINDOW.camera->up);
        GLint viewUniformLocation = glGetUniformLocation(polygonShader, "view");
        glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, (const GLfloat *)&view);

        // DRAW
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // polygons
        glBindVertexArray(p->vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        for (unsigned int i = 0; i < 10; i++) {
            model = m4_translation(cubePositions[i]);
            model = m4_mul(model, m4_rotation(sinf(timeValue), vec3(1.0f, 0.3f, 0.5f)));
            GLint modelUniformLocation = glGetUniformLocation(polygonShader, "model");
            glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, (const GLfloat *)&model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    polygon_free(p);
    glfwTerminate();
    return 0;
}