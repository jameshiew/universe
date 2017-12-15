//
// Created by James Hiew on 15/12/2017.
//

#ifndef UNIVERSE_FONT_H
#define UNIVERSE_FONT_H

#include <string>

void initFont();

typedef struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
} Character;

void renderText(GLuint shaderProgram, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

#endif //UNIVERSE_FONT_H
