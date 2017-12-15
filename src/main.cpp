#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cmath>

#include "input.hpp"
#include "shaders.hpp"
#include "render.hpp"
#include "polygon.hpp"
#include "window.hpp"
#include "font.hpp"
#include "main.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char *argv[]) {
    GLFWwindow *window = initWindow();
    if (window == nullptr) {
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    initFont();
    print_debug_output();

    GLuint polygonShader = load_program("../../shaders/phong.vert", "../../shaders/phong.frag");

    Polygon *p = Cube_new(VERTEX_TYPE_TEXTURED);
    GLuint texture = load_texture("../../textures/container.jpg");

    glm::mat4 model, view, projection;

    glUseProgram(polygonShader);
    WINDOW.camera = Camera_new();
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
        projection = glm::perspective(45.0f, (float) (WINDOW.width / WINDOW.height), 0.1f, 100.0f);
        GLint projectionUniformLocation = glGetUniformLocation(polygonShader, "projection");
        glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, (const GLfloat *)&projection);

        view = glm::lookAt(WINDOW.camera->position, WINDOW.camera->position + WINDOW.camera->front, WINDOW.camera->up);
        GLint viewUniformLocation = glGetUniformLocation(polygonShader, "view");
        glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, (const GLfloat *)&view);

        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
        GLint lightColorUniformLocation = glGetUniformLocation(polygonShader, "lightColor");
        glUniform3fv(lightColorUniformLocation, 1, (const GLfloat *)&lightColor);

        // DRAW
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // polygons
        glBindVertexArray(p->vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        model = glm::rotate(glm::mat4(), (float) sin(timeValue), glm::vec3(1.0f, 0.3f, 0.5f));
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