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
#include <sstream>

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

    glfwWindowHint(GLFW_SAMPLES, 16);
    glEnable(GL_MULTISAMPLE);

    GLuint polygonShader = load_program("../../shaders/phong.vert", "../../shaders/phong.frag");
    GLuint textShader = load_program("../../shaders/text.vert", "../../shaders/text.frag");

    Polygon *p = Cube_new(VERTEX_TYPE_TEXTURED);
    GLuint texture = load_texture("../../textures/container.jpg");

    WINDOW.camera = Camera_new();
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);
    double deltaTime, timeOfLastFrame = 0.0f;

    float quadDim = pow(2.f, 8.f);
    float floor[] = {
            -quadDim, 0.0f, -quadDim, 64.0f, 64.0f,
            -quadDim, 0.0f, quadDim, 64.0f, 0.0f,
            quadDim, 0.0f, quadDim, 0.0f, 64.0f,
            quadDim, 0.0f, -quadDim, 0.0f, 0.0f,
    };
    GLuint a, b;
    glGenVertexArrays(1, &a);
    glGenBuffers(1, &b);
    glBindVertexArray(a);
    glBindBuffer(GL_ARRAY_BUFFER, b);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBufferData(GL_ARRAY_BUFFER, 4 * 5 * sizeof(float), &floor, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window, deltaTime);
        // INPUT PROCESSING
        double timeValue = glfwGetTime();
        deltaTime = timeValue - timeOfLastFrame;
        timeOfLastFrame = timeValue;

        // DRAW
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 3D
        {
            glUseProgram(polygonShader);
            auto projective = glm::perspective(70.0f, static_cast<GLfloat>(WINDOW.width) / static_cast<GLfloat>(WINDOW.height), 0.1f, 1000.0f);
            glUniformMatrix4fv(
                    glGetUniformLocation(polygonShader, "projection"),
                    1, GL_FALSE, glm::value_ptr(projective)
            );

            auto view = glm::lookAt(WINDOW.camera->position, WINDOW.camera->position + WINDOW.camera->front, WINDOW.camera->up);
            glUniformMatrix4fv(
                    glGetUniformLocation(polygonShader, "view"),
                    1, GL_FALSE, glm::value_ptr(view)
            );

            auto model = glm::mat4();
            glUniformMatrix4fv(
                    glGetUniformLocation(polygonShader, "model"),
                    1, GL_FALSE, glm::value_ptr(model)
            );

            auto lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
            glUniform3fv(
                    glGetUniformLocation(polygonShader, "lightColor"),
                    1, glm::value_ptr(lightColor)
            );


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            // floor
            glBindVertexArray(a);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            // other
            glBindVertexArray(p->vao);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
        }

        // 2D UI
        {
            glUseProgram(textShader);
            auto orthographic = glm::ortho(0.0f, static_cast<GLfloat>(WINDOW.width), 0.0f, static_cast<GLfloat>(WINDOW.height));
            glUniformMatrix4fv(
                    glGetUniformLocation(textShader, "projection"),
                    1, GL_FALSE, glm::value_ptr(orthographic)
            );

            std::ostringstream s_frametime;
            s_frametime << "Frametime: " << (unsigned int) (deltaTime * 1000) << "ms";
            std::string frametime = s_frametime.str();

            std::ostringstream s_coords;
            s_coords << "Position: (" << round(WINDOW.camera->position.x) << ", " << round(WINDOW.camera->position.y) << ", " << round(WINDOW.camera->position.z) << ")";
            std::string coords = s_coords.str();

            std::ostringstream s_viewport;
            s_viewport << "Viewport: " << WINDOW.width << "x" << WINDOW.height;
            std::string viewport = s_viewport.str();

            renderText(textShader, frametime, 25.0f, 25.0f, .5f, glm::vec3(1.f, 1.f, 1.f));
            renderText(textShader, coords, 25.0f, 50.0f, .5f, glm::vec3(1.f, 1.f, 1.f));
            renderText(textShader, viewport, 25.0f, 75.0f, .5f, glm::vec3(1.f, 1.f, 1.f));
        }

        // next!
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    Polygon_free(p);
    glfwTerminate();
    return 0;
}