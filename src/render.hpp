//
// Created by James Hiew on 09/12/2017.
//

#ifndef UNIVERSE_RENDER_H
#define UNIVERSE_RENDER_H
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

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

void render(GLuint polygonShader, DrawInstruction *draw, float width, float height);
void renderUI(GLuint textShader, float deltaTime, float width, float height);
#endif //UNIVERSE_RENDER_H
