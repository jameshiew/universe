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

void renderUI(GLuint textShader, float deltaTime, float width, float height) {
    glUseProgram(textShader);
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
