#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gflags/gflags.h>

#include <cmath>

#include "input.hpp"
#include "shaders.hpp"
#include "window.hpp"
#include "font.hpp"
#include "space.hpp"
#include "spdlog.h"
#include "constants.hpp"

#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

DEFINE_bool(debug, false, "whether to enable debug logging or not");

void init_logging(bool debug) {
    spdlog::set_pattern("%H:%M:%S.%e %t %n %L: %v");
    auto logger = spdlog::stdout_color_mt(APPLICATION_NAME);
    auto glfwLogger = spdlog::stdout_color_mt("glfw");
    auto gladLogger = spdlog::stdout_color_mt("glad");
    auto worldgenLogger = spdlog::stdout_color_mt("worldgen");
    if (debug) {
        spdlog::set_level(spdlog::level::debug);
    }
}

int main(int argc, char *argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    init_logging(FLAGS_debug);

    spdlog::get("glfw")->info("Initializing GLFW (version string=\"{}\")", glfwGetVersionString());
    GLFWwindow *window;
    if ((window = initialize_window()) == nullptr) {
        spdlog::get("glfw")->error("Failed to create GLFW window");
        return 1;
    }
    initialize_font();
    auto camera = new Camera();
    glfwSetWindowUserPointer(window, camera);

    auto polygonShaderProgram = ShaderProgram_load("../../shaders/polygon/textured_phong.vert",
                                              "../../shaders/polygon/textured_phong.frag");
    polygonShaderProgram->type = SHADER_PROGRAM_TEXTURED_PHONG;

    auto textShaderProgram = ShaderProgram_load("../../shaders/text.vert", "../../shaders/text.frag");
    textShaderProgram->type = SHADER_PROGRAM_TEXT_SHADER;

    float deltaTime, timeOfLastFrame = 0.0f;
    auto world = World_new();
    auto frame = Frame_new();  // use same frame struct each render to save space

    int width, height;
    while (!glfwWindowShouldClose(window)) {
        auto timeValue = (float) glfwGetTime();
        deltaTime = timeValue - timeOfLastFrame;
        timeOfLastFrame = timeValue;
        process_input(window, camera, deltaTime);

        // DRAW
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, camera->wireframe ? GL_LINE : GL_FILL);

        glfwGetFramebufferSize(window, &width, &height);
        auto widthf = (float) width, heightf = (float) height;
        glUseProgram(polygonShaderProgram->id);
        glUniformMatrix4fv(
                glGetUniformLocation(polygonShaderProgram->id, "projection"),
                1, GL_FALSE, glm::value_ptr(
                        glm::perspective(45.0f, widthf / heightf, 0.1f, 128.0f)
                )
        );

        glUniformMatrix4fv(
                glGetUniformLocation(polygonShaderProgram->id, "view"),
                1, GL_FALSE, glm::value_ptr(
                        glm::lookAt(camera->position, camera->position + camera->front, camera->up)
                )
        );

        glUniform3fv(
                glGetUniformLocation(polygonShaderProgram->id, "lightPosition"),
                1, glm::value_ptr(camera->position)
        );
        auto drawInstructions = World_get_draw_instructions(world, camera->position, 2);
        for (auto &drawInstruction: *drawInstructions) {
            Frame_draw(frame, polygonShaderProgram->id, (DrawInstruction *)drawInstruction);
        }
        renderUI(textShaderProgram->id, frame, camera, deltaTime, widthf, heightf);

        // next!
        glfwSwapBuffers(window);
        glfwPollEvents();
        glFinish();
        Frame_clear(frame);
    }
    Frame_free(frame);
    World_free(world);
    glfwTerminate();
    spdlog::drop_all();
}