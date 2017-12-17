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

void renderUI(GLuint shaderProgram, Frame* frame, Camera* camera, float deltaTime, float width, float height) {
    glUseProgram(shaderProgram);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // we don't render text in wireframe
    auto orthographic = glm::ortho(0.0f, width, 0.0f, height);
    glUniformMatrix4fv(
            glGetUniformLocation(shaderProgram, "projection"),
            1, GL_FALSE, glm::value_ptr(orthographic)
    );

    std::ostringstream s_frame;
    s_frame << "NV: " << frame->vertices << " NT: " << frame->triangles << " ND: " << frame->draws;
    std::string fr = s_frame.str();

    std::ostringstream s_frametime;
    s_frametime << "F: " << (unsigned int) (deltaTime * 1000) << "ms";
    std::string frametime = s_frametime.str();

    std::ostringstream s_coords;
    s_coords << "P: (" << round(camera->position.x) << ", " << round(camera->position.y) << ", " << round(camera->position.z) << ")";
    std::string coords = s_coords.str();

    std::ostringstream s_viewport;
    s_viewport << "V: " << width << "x" << height << " M: " << camera->lastX << ", " << camera->lastY;
    std::string viewport = s_viewport.str();

    render_text(shaderProgram, frametime, 25.0f, 25.0f, .5f, glm::vec3(1.f, 1.f, 1.f));
    render_text(shaderProgram, coords, 25.0f, 50.0f, .5f, glm::vec3(1.f, 1.f, 1.f));
    render_text(shaderProgram, viewport, 25.0f, 75.0f, .5f, glm::vec3(1.f, 1.f, 1.f));
    render_text(shaderProgram, fr, 25.0f, 100.0f, .5f, glm::vec3(1.f, 1.f, 1.f));
}

Frame *Frame_new() {
    return (Frame *)calloc(1, sizeof(Frame));
}

void Frame_free(Frame *frame) {
    free(frame);
}

void Frame_draw(Frame *frame, GLuint shaderProgram, DrawInstruction *drawInstruction) {
    switch (drawInstruction->mode) {
        case GL_TRIANGLES:
            frame->triangles += drawInstruction->numberOfOffsets * (drawInstruction->count / 3);
            break;
        case GL_TRIANGLE_STRIP:
            frame->triangles += drawInstruction->numberOfOffsets * (drawInstruction->count - 2);
            break;
        default:
            break;
    }
    frame->vertices += drawInstruction->numberOfOffsets * drawInstruction->count;
    frame->draws += drawInstruction->numberOfOffsets;

    glUseProgram(shaderProgram);
    glBindVertexArray(drawInstruction->vao);
    for (int i = 0; i < drawInstruction->numberOfOffsets; i++) {
        auto model = glm::translate(glm::mat4(), drawInstruction->offsets[i]);
        glUniformMatrix4fv(
            glGetUniformLocation(shaderProgram, "model"),
            1, GL_FALSE, glm::value_ptr(model)
        );
        glDrawArrays(drawInstruction->mode, 0, drawInstruction->count);
    }
}
