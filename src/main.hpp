//
// Created by James Hiew on 13/12/2017.
//

#ifndef UNIVERSE_MAIN_H
#define UNIVERSE_MAIN_H

#include "window.hpp"
#include "font.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>

extern Window WINDOW;
extern FT_Library library;
extern FT_Face face;
extern std::map<GLchar, Character> Characters;

#endif //UNIVERSE_MAIN_H
