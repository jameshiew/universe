#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>

#include "input.hpp"
#include "shaders.hpp"
#include "polygon.hpp"
#include "window.hpp"
#include "font.hpp"
#include "space.hpp"
#include "spdlog.h"

#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char *argv[]) {
    auto logger = spdlog::stdout_color_mt(APPLICATION_NAME);
    auto glfwLogger = spdlog::stdout_color_mt("glfw");
    auto gladLogger = spdlog::stdout_color_mt("glad");

    GLFWwindow *window;
    if ((window = initialise_window()) == nullptr) {
        return -1;
    }
    initialise_font();
    auto camera = Camera_new();
    glfwSetWindowUserPointer(window, camera);

    auto polygonShaderProgram = ShaderProgram_load("../../shaders/polygon/textured_phong.vert",
                                              "../../shaders/polygon/textured_phong.frag");
    polygonShaderProgram->type = SHADER_PROGRAM_TEXTURED_PHONG;

    auto textShaderProgram = ShaderProgram_load("../../shaders/text.vert", "../../shaders/text.frag");
    textShaderProgram->type = SHADER_PROGRAM_TEXT_SHADER;

    GLuint texture = load_texture("../../textures/container.jpg");

    float deltaTime, timeOfLastFrame = 0.0f;
    auto world = World_new();
    auto frame = Frame_new();  // use same frame struct each render to save space
    while (!glfwWindowShouldClose(window)) {
        auto timeValue = (float) glfwGetTime();
        deltaTime = timeValue - timeOfLastFrame;
        timeOfLastFrame = timeValue;
        process_input(window, camera, deltaTime);

        // DRAW
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, camera->wireframe ? GL_LINE : GL_FILL);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        auto widthf = (float) width, heightf = (float) height;
        glUseProgram(polygonShaderProgram->id);
        auto projective = glm::perspective(70.0f, widthf / heightf, 0.1f, 1000.0f);
        glUniformMatrix4fv(
                glGetUniformLocation(polygonShaderProgram->id, "projection"),
                1, GL_FALSE, glm::value_ptr(projective)
        );

        auto view = glm::lookAt(camera->position, camera->position + camera->front, camera->up);
        glUniformMatrix4fv(
                glGetUniformLocation(polygonShaderProgram->id, "view"),
                1, GL_FALSE, glm::value_ptr(view)
        );

        auto lightPosition = camera->position;
        glUniform3fv(
                glGetUniformLocation(polygonShaderProgram->id, "lightPosition"),
                1, glm::value_ptr(lightPosition)
        );
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        auto drawInstructions = World_get_draw_instructions(world);
        for (auto &drawInstruction: *drawInstructions) {
            Frame_draw(frame, polygonShaderProgram->id, (DrawInstruction *)drawInstruction);
        }
        renderUI(textShaderProgram->id, frame, camera, deltaTime, widthf, heightf);

        // next!
        glfwSwapBuffers(window);
        glfwPollEvents();
        Frame_clear(frame);
    }
    Frame_free(frame);
    Camera_free(camera);
    World_free(world);
    glfwTerminate();
    return 0;
}