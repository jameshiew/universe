//
// Created by James Hiew on 15/12/2017.
//

#include "main.hpp"
#include "font.hpp"

FT_Library library;
FT_Face face;

void initFont() {
    if (FT_Init_FreeType(&library)) {
        fprintf(stderr, "Could not init freetype library\n");
    }
    if (FT_New_Face(library, "../../fonts/FreeSans.ttf", 0, &face)) {
        fprintf(stderr, "Could not open font\n");
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        fprintf(stderr, "ERROR::FREETYTPE: Failed to load Glyph");
    }
}
