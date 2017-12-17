//
// Created by James Hiew on 12/12/2017.
//

#ifndef UNIVERSE_POLYGON_H
#define UNIVERSE_POLYGON_H

#include <glm/glm.hpp>
#include "render.hpp"
#include "shaders.hpp"

typedef enum POLYGON_TYPE {
    POLYGON_TYPE_CUBE,
} POLYGON_TYPE;

typedef enum VERTEX_TYPE {
    VERTEX_TYPE_POINT,
    VERTEX_TYPE_COLORED,
    VERTEX_TYPE_TEXTURED,
    VERTEX_TYPE_COLORED_WITH_NORMAL,
    VERTEX_TYPE_TEXTURED_WITH_NORMAL,
} VERTEX_TYPE;

typedef struct Polygon {
    VERTEX_TYPE vertexType;
    GLsizeiptr numberOfVertices;
    float *vertices;
    GLsizeiptr numberOfTriangles;
    unsigned int *indices;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
} Polygon;

DrawInstruction *test();
Polygon *Cube_new(ShaderProgram *shaderProgram);

#endif //UNIVERSE_POLYGON_H
