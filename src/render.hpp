#ifndef UNIVERSE_RENDER_H
#define UNIVERSE_RENDER_H
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <list>

#include "camera.hpp"

typedef struct DrawInstruction {
    GLenum mode;
    std::list<glm::vec3> *positions;
    GLuint texture;

    GLuint vao;
    GLuint vbo;
    GLsizei vertexSize;
    GLsizei vertexCount;
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

DrawInstruction *DrawInstruction_cube();

void renderUI(GLuint shaderProgram, Frame *frame, Camera *camera, float deltaTime, float width, float height);
#endif //UNIVERSE_RENDER_H
