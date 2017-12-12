#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "input.h"
#include "shaders.h"
#include "render.h"
#include "config.h"
#include "polygon.h"

int main() {
    GLFWwindow *window = create_window();
    if (window == NULL) {
        return -1;
    }
    print_debug_output();

    GLuint shaderProgram = load_program("../../shaders/basic.glslv", "../../shaders/basic.glslf");
    polygon *p = polygon_new();


    glUseProgram(shaderProgram);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // seeing as we only have a single VAO there's no need to bind it every time,
        // but we'll do so to keep things a bit more organized
        glBindVertexArray(p->vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0); // technically no need to unbind it every time

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}