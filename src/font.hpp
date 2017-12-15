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
void renderText(GLuint shaderProgram, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

#endif //UNIVERSE_FONT_H
