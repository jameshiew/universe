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
#include "space.hpp"
#include "shaders.hpp"

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
            frame->triangles += drawInstruction->positions->size() * (drawInstruction->vertexCount / 3);
            break;
        case GL_TRIANGLE_STRIP:
            frame->triangles += drawInstruction->positions->size() * (drawInstruction->vertexCount - 2);
            break;
        default:
            break;
    }
    frame->vertices += drawInstruction->positions->size() * drawInstruction->vertexCount;
    frame->draws += drawInstruction->positions->size();

    glUseProgram(shaderProgram);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, drawInstruction->texture);
    glBindVertexArray(drawInstruction->vao);
    for (auto &position: *drawInstruction->positions) {
        auto model = glm::translate(IDENTITY, position);
        glUniformMatrix4fv(
            glGetUniformLocation(shaderProgram, "model"),
            1, GL_FALSE, glm::value_ptr(model)
        );
        glDrawArrays(drawInstruction->mode, 0, drawInstruction->vertexCount);
    }
}

void Frame_clear(Frame *frame) {
    frame->draws = 0;
    frame->vertices = 0;
    frame->triangles = 0;
}

const float CUBE_STRIP_VERTICES[] = {
        // south          // normal         // texture
        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        // east
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        // north
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        // west
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        // down
        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        // up
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
};

GLuint cubeTexture = 0;

DrawInstruction *DrawInstruction_cube() {
    auto draw = (DrawInstruction *)malloc(sizeof(DrawInstruction));
    glGenVertexArrays(1, &(draw->vao));
    glBindVertexArray(draw->vao);
    if (!cubeTexture) {
        cubeTexture = load_texture("../../textures/container.jpg");
    }

    draw->vertexSize = 8 * sizeof(float);
    draw->vertexCount = 24;
    draw->mode = GL_TRIANGLE_STRIP;
    draw->texture = cubeTexture;

    glGenBuffers(1, &(draw->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, draw->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_STRIP_VERTICES), CUBE_STRIP_VERTICES, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, draw->vertexSize, nullptr);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, draw->vertexSize, (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // uv attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, draw->vertexSize, (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    return draw;
}
