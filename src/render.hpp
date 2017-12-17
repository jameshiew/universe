//
// Created by James Hiew on 09/12/2017.
//

#ifndef UNIVERSE_RENDER_H
#define UNIVERSE_RENDER_H
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"

typedef struct DrawInstruction {
    GLenum mode;
    glm::vec3 *positions;
    size_t count;

    GLuint vao;
    GLuint vbo;
    GLsizei vertexSize;
    GLsizei vertexCount;
    bool useIndices;
    GLuint ebo;
    GLsizei indexCount;
} DrawInstruction;

// Represents debug information about a frame drawn
typedef struct Frame {
    unsigned int triangles;
    unsigned int vertices;
    unsigned int draws;
} Frame;

Frame *Frame_new();
void Frame_free(Frame* frame);
void Frame_clear(Frame* frame);
void Frame_draw(Frame *frame, GLuint shaderProgram, DrawInstruction *drawInstruction);

void renderUI(GLuint shaderProgram, Frame *frame, Camera *camera, float deltaTime, float width, float height);
#endif //UNIVERSE_RENDER_H
