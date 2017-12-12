#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "input.h"
#include "shaders.h"
#include "render.h"
#include "polygon.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MATH_3D_IMPLEMENTATION
#include "math_3d.h"

int main() {
    GLFWwindow *window = create_window();
    if (window == NULL) {
        return -1;
    }
    print_debug_output();

    GLuint shaderProgram = load_program("../../shaders/basic.vert", "../../shaders/basic.frag");

    polygon *p = polygon_new();
    GLuint texture = load_texture("../../textures/container.jpg");

    glUseProgram(shaderProgram);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double timeValue = glfwGetTime();

        double greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "baseColor");
        glUniform4f(vertexColorLocation, 0.0f, (GLfloat) greenValue, 0.0f, 1.0f);

        mat4_t trans = m4_rotation_z(sin(timeValue));

        GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (const GLfloat *)&trans);

        // seeing as we only have a single VAO there's no need to bind it every time,
        // but we'll do so to keep things a bit more organized
        glBindVertexArray(p->vao);
        glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0); // technically no need to unbind it every time

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    polygon_free(p);
    glfwTerminate();
    return 0;
}