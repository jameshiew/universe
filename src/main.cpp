#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>

#include "input.hpp"
#include "shaders.hpp"
#include "polygon.hpp"
#include "window.hpp"
#include "font.hpp"
#include "spdlog.h"

#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "space.hpp"

int main(int argc, char *argv[]) {
    auto logger = spdlog::stdout_color_mt(APPLICATION_NAME);
    Application A = {
        .camera = Camera_new(),
        .paused = false,
    };
    if ((A.window = initialise_window()) == nullptr) {
        return -1;
    }
    glfwSetWindowUserPointer(A.window, &A);
    initialise_font();

    auto polygonShaderProgram = ShaderProgram_load("../../shaders/polygon/colored_phong.vert",
                                              "../../shaders/polygon/colored_phong.frag");
    auto textShaderProgram = ShaderProgram_load("../../shaders/text.vert", "../../shaders/text.frag");

//    GLuint texture = load_texture("../../textures/container.jpg");

    float timeOfLastFrame = 0.0f;
    auto world = World_new();
    while (!glfwWindowShouldClose(A.window)) {
        auto timeValue = (float) glfwGetTime();
        A.deltaTime = timeValue - timeOfLastFrame;
        timeOfLastFrame = timeValue;
        process_input(A.window);

        // DEBUG COUNTERS
        auto frame = Frame_new();

        // DRAW
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, A.camera->wireframe ? GL_LINE : GL_FILL);

        int width, height;
        glfwGetFramebufferSize(A.window, &width, &height);
        auto widthf = (float) width, heightf = (float) height;
        glUseProgram(polygonShaderProgram->id);
        auto projective = glm::perspective(70.0f, widthf / heightf, 0.1f, 1000.0f);
        glUniformMatrix4fv(
                glGetUniformLocation(polygonShaderProgram->id, "projection"),
                1, GL_FALSE, glm::value_ptr(projective)
        );

        auto view = glm::lookAt(A.camera->position, A.camera->position + A.camera->front, A.camera->up);
        glUniformMatrix4fv(
                glGetUniformLocation(polygonShaderProgram->id, "view"),
                1, GL_FALSE, glm::value_ptr(view)
        );

        auto color = glm::vec3(0.4f, 0.3f, 1.0f);
        glUniform3fv(
                glGetUniformLocation(polygonShaderProgram->id, "color"),
                1, glm::value_ptr(color)
        );

        auto lightPosition = A.camera->position;
        glUniform3fv(
                glGetUniformLocation(polygonShaderProgram->id, "lightPosition"),
                1, glm::value_ptr(lightPosition)
        );

        auto drawInstructions = World_get_draw_instructions(world);
        for (auto &drawInstruction: drawInstructions) {
            Frame_draw(frame, polygonShaderProgram->id, (DrawInstruction *)drawInstruction);
        }
        renderUI(textShaderProgram->id, frame, A.camera, A.deltaTime, widthf, heightf);

        // next!
        glfwSwapBuffers(A.window);
        glfwPollEvents();
        Frame_free(frame);
    }
    glfwTerminate();
    return 0;
}