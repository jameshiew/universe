//
// Created by James Hiew on 09/12/2017.
//

#ifndef UNIVERSE_RENDER_H
#define UNIVERSE_RENDER_H
#include <glad/glad.h>

typedef struct DrawInstruction {
    GLuint vao;
    GLenum mode;
    GLsizei count;
    glm::vec3 *offsets;
    size_t numberOfOffsets;

    GLuint vbo;
    GLuint ebo;
} DrawInstruction;

void renderUI(GLuint textShader, float deltaTime, float width, float height);
#endif //UNIVERSE_RENDER_H
