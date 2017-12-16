//
// Created by James Hiew on 09/12/2017.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <string>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "font.hpp"
#include "config.hpp"
#include "render.hpp"

void render(GLuint polygonShader, DrawInstruction *draw, float width, float height) {
    glUseProgram(polygonShader);
    auto projective = glm::perspective(70.0f, width / height, 0.1f, 1000.0f);
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

    glBindVertexArray(draw->vao);
    for (int i = 0; i < draw->numberOfOffsets; i++) {
        auto model = glm::translate(glm::mat4(), draw->offsets[i]);
        glUniformMatrix4fv(
                glGetUniformLocation(polygonShader, "model"),
                1, GL_FALSE, glm::value_ptr(model)
        );
        glDrawArrays(draw->mode, 0, draw->count);
    }
}

void renderUI(GLuint textShader, float deltaTime, float width, float height) {
    glUseProgram(textShader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // we don't render text in wireframe
    auto orthographic = glm::ortho(0.0f, width, 0.0f, height);
    glUniformMatrix4fv(
            glGetUniformLocation(textShader, "projection"),
            1, GL_FALSE, glm::value_ptr(orthographic)
    );

    std::ostringstream s_frametime;
    s_frametime << "F: " << (unsigned int) (deltaTime * 1000) << "ms";
    std::string frametime = s_frametime.str();

    std::ostringstream s_coords;
    s_coords << "P: (" << round(A.camera->position.x) << ", " << round(A.camera->position.y) << ", " << round(A.camera->position.z) << ")";
    std::string coords = s_coords.str();

    std::ostringstream s_viewport;
    s_viewport << "V: " << width << "x" << height << " M: " << A.camera->lastX << ", " << A.camera->lastY;
    std::string viewport = s_viewport.str();

    renderText(textShader, frametime, 25.0f, 25.0f, .5f, glm::vec3(1.f, 1.f, 1.f));
    renderText(textShader, coords, 25.0f, 50.0f, .5f, glm::vec3(1.f, 1.f, 1.f));
    renderText(textShader, viewport, 25.0f, 75.0f, .5f, glm::vec3(1.f, 1.f, 1.f));
}
