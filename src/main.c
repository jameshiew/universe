#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "input.h"
#include "shaders.h"
#include "render.h"
#include "Polygon.h"
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
    glEnable(GL_CULL_FACE);
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

    GLuint polygonShader = load_program("../../shaders/phong.vert", "../../shaders/phong.frag");

    Polygon *p = Cube_new(VERTEX_TYPE_TEXTURED);
    GLuint texture = load_texture("../../textures/container.jpg");

    mat4_t model, view, projection;

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
        printf("Frame time: %fms\n", deltaTime * 1000);
        processInput(window, deltaTime);

        // MATRICES
        projection = m4_perspective(45.0f, WINDOW.width / WINDOW.height, 0.1f, 100.0f);
        GLint projectionUniformLocation = glGetUniformLocation(polygonShader, "projection");
        glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, (const GLfloat *)&projection);

        view = m4_look_at(WINDOW.camera->position, v3_add(WINDOW.camera->position, WINDOW.camera->front), WINDOW.camera->up);
        GLint viewUniformLocation = glGetUniformLocation(polygonShader, "view");
        glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, (const GLfloat *)&view);

        vec3_t lightColor = vec3(1.0f, 1.0f, 1.0f);
        GLint lightColorUniformLocation = glGetUniformLocation(polygonShader, "lightColor");
        glUniform3fv(lightColorUniformLocation, 1, (const GLfloat *)&lightColor);

        // DRAW
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // polygons
        glBindVertexArray(p->vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        model = m4_rotation((float) sin(timeValue), vec3(1.0f, 0.3f, 0.5f));
        GLint modelUniformLocation = glGetUniformLocation(polygonShader, "model");
        glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, (const GLfloat *)&model);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    Polygon_free(p);
    glfwTerminate();
    return 0;
}