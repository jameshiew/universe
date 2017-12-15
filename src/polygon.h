//
// Created by James Hiew on 12/12/2017.
//

#ifndef UNIVERSE_POLYGON_H
#define UNIVERSE_POLYGON_H

typedef struct polygon {
    GLsizeiptr numberOfVertices;
    float *vertices;
    GLsizeiptr numberOfTriangles;
    unsigned int *indices;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
} Polygon;

Polygon *Cube_new();
void Polygon_free(Polygon *polygon);

#endif //UNIVERSE_POLYGON_H
