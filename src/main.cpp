#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cmath>

#include "input.hpp"
#include "shaders.hpp"
#include "polygon.hpp"
#include "window.hpp"
#include "font.hpp"
#include "spdlog.h"

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
    auto logger = spdlog::stdout_color_mt(APPLICATION_NAME);
    auto glfwLogger = spdlog::stdout_color_mt("logger");
    A.window = initWindow();
    if (A.window == nullptr) {
        return -1;
    }
    A.camera = Camera_new();
    glfwSetWindowUserPointer(A.window, &A);
    initFont();

    GLuint polygonShader = load_program("../../shaders/polygon/colored_phong.vert", "../../shaders/polygon/colored_phong.frag");
    GLuint textShader = load_program("../../shaders/text.vert", "../../shaders/text.frag");

//    GLuint texture = load_texture("../../textures/container.jpg");

    double deltaTime, timeOfLastFrame = 0.0f;
    while (!glfwWindowShouldClose(A.window)) {
        double timeValue = glfwGetTime();
        deltaTime = timeValue - timeOfLastFrame;
        timeOfLastFrame = timeValue;

        // DEBUG COUNTERS
        auto frame = Frame_new();

        // INPUT PROCESSING
        processInput(A.window, deltaTime);
        int width, height;
        glfwGetFramebufferSize(A.window, &width, &height);

        // DRAW
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, A.camera->wireframe ? GL_LINE : GL_FILL);

        glUseProgram(polygonShader);
        auto projective = glm::perspective(70.0f, (float) width / (float) height, 0.1f, 1000.0f);
        glUniformMatrix4fv(
                glGetUniformLocation(polygonShader, "projection"),
                1, GL_FALSE, glm::value_ptr(projective)
        );

        auto view = glm::lookAt(A.camera->position, A.camera->position + A.camera->front, A.camera->up);
        glUniformMatrix4fv(
                glGetUniformLocation(polygonShader, "view"),
                1, GL_FALSE, glm::value_ptr(view)
        );

        auto color = glm::vec3(0.4f, 0.3f, 1.0f);
        glUniform3fv(
                glGetUniformLocation(polygonShader, "color"),
                1, glm::value_ptr(color)
        );

        auto lightPosition = A.camera->position;
        glUniform3fv(
                glGetUniformLocation(polygonShader, "lightPosition"),
                1, glm::value_ptr(lightPosition)
        );
        auto drawInstruction = test();
        Frame_add_draw_instruction(frame, drawInstruction);

        render(polygonShader, drawInstruction, (float) width, (float) height);
        renderUI(textShader, frame, (float) deltaTime, (float) width, (float) height);

        // next!
        glfwSwapBuffers(A.window);
        glfwPollEvents();
        Frame_free(frame);
    }
    glfwTerminate();
    return 0;
}