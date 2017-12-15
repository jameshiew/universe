//
// Created by James Hiew on 12/12/2017.
//

#ifndef UNIVERSE_POLYGON_H
#define UNIVERSE_POLYGON_H

#include <math_3d.h>

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

Polygon *Rect_new(VERTEX_TYPE vertexType, vec3_t *corner);
Polygon *Cube_new(VERTEX_TYPE vertexType);
void Polygon_free(Polygon *polygon);

#endif //UNIVERSE_POLYGON_H
