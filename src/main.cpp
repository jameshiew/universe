#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cmath>

#include "input.hpp"
#include "shaders.hpp"
#include "polygon.hpp"
#include "window.hpp"
#include "font.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <random>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "render.hpp"

Application A = {
    .paused = false,
};

int main(int argc, char *argv[]) {
    A.window = initWindow();
    if (A.window == nullptr) {
        return -1;
    }
    A.camera = Camera_new();
    glfwSetWindowUserPointer(A.window, &A);
    initFont();

    GLuint polygonShader = load_program("../../shaders/phong.vert", "../../shaders/phong.frag");
    GLuint textShader = load_program("../../shaders/text.vert", "../../shaders/text.frag");

    Polygon *p = Cube_new(VERTEX_TYPE_TEXTURED);
    std::default_random_engine prng;
    std::uniform_real_distribution<float> distribution(-100.f,100.f);

    GLuint texture = load_texture("../../textures/container.jpg");
    glm::vec3 positions[100];
    for (int i = 0; i < 100; i++) {
        positions[i] = glm::vec3(distribution(prng), distribution(prng), distribution(prng));
    }
    double deltaTime, timeOfLastFrame = 0.0f;
    while (!glfwWindowShouldClose(A.window)) {
        double timeValue = glfwGetTime();
        deltaTime = timeValue - timeOfLastFrame;
        timeOfLastFrame = timeValue;

        // INPUT PROCESSING
        processInput(A.window, deltaTime);
        int width, height;
        glfwGetFramebufferSize(A.window, &width, &height);

        // DRAW
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 3D
        {
            glUseProgram(polygonShader);
            auto projective = glm::perspective(70.0f, static_cast<GLfloat>(width) / static_cast<GLfloat>(height), 0.1f, 1000.0f);
            glUniformMatrix4fv(
                    glGetUniformLocation(polygonShader, "projection"),
                    1, GL_FALSE, glm::value_ptr(projective)
            );

            auto view = glm::lookAt(A.camera->position, A.camera->position + A.camera->front, A.camera->up);
            glUniformMatrix4fv(
                    glGetUniformLocation(polygonShader, "view"),
                    1, GL_FALSE, glm::value_ptr(view)
            );

            auto lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
            glUniform3fv(
                    glGetUniformLocation(polygonShader, "lightColor"),
                    1, glm::value_ptr(lightColor)
            );

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            // other
            glBindVertexArray(p->vao);
            glm::mat4 model;
            for (int i = 0; i < 100; i++) {
                model = glm::translate(glm::mat4(), positions[i]);
                glUniformMatrix4fv(
                        glGetUniformLocation(polygonShader, "model"),
                        1, GL_FALSE, glm::value_ptr(model)
                );
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
            }
        }
        renderUI(textShader, deltaTime, (float) width, (float) height);

        // next!
        glfwSwapBuffers(A.window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}