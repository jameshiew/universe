//
// Created by James Hiew on 15/12/2017.
//

#ifndef UNIVERSE_FONT_H
#define UNIVERSE_FONT_H

#include <string>
#include <map>

#include <ft2build.h>
#include <glm/detail/type_vec.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include FT_FREETYPE_H

void initFont();

typedef struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
} Character;

void renderText(GLuint shaderProgram, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

extern std::map<GLchar, Character> Characters;

extern FT_Library library;
extern FT_Face face;
#endif //UNIVERSE_FONT_H
