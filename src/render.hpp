//
// Created by James Hiew on 09/12/2017.
//

#ifndef UNIVERSE_RENDER_H
#define UNIVERSE_RENDER_H
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"

typedef struct DrawInstruction {
    GLsizei vertexSize;
    GLenum mode;
    GLsizei count;
    glm::vec3 *offsets;
    size_t numberOfOffsets;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
} DrawInstruction;

// Represents debug information about a frame drawn
typedef struct Frame {
    unsigned int triangles;
    unsigned int vertices;
    unsigned int draws;
} Frame;

Frame *Frame_new();
void Frame_free(Frame* frame);
void Frame_add_draw_instruction(Frame* frame, DrawInstruction* drawInstruction);
void render(GLuint polygonShader, DrawInstruction *draw, float width, float height);
void renderUI(GLuint textShader, Frame *frame, Camera *camera, float deltaTime, float width, float height);
#endif //UNIVERSE_RENDER_H
