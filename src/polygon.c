//
// Created by James Hiew on 12/12/2017.
//
#include <stddef.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <memory.h>

#include "polygon.h"

polygon *polygon_new() {
    polygon *p = malloc(sizeof(polygon));

    p->numberOfVertices = 3;
    size_t v = p->numberOfVertices * 6 * sizeof(float);
    p->vertices = malloc(v);
    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };
    memcpy(p->vertices, vertices, v);

    p->numberOfTriangles = 1;
    size_t t = p->numberOfTriangles * 6 * sizeof(float);
    p->indices = malloc(t);
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 2,  // first Triangle
    };
    memcpy(p->indices, indices, t);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glGenVertexArrays(1, &(p->vao));
    glBindVertexArray(p->vao);
    glGenBuffers(1, &(p->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, p->vbo);
    glGenBuffers(1, &(p->ebo));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p->ebo);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);


    glBufferData(GL_ARRAY_BUFFER, v, p->vertices, GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, t, p->indices, GL_STATIC_DRAW);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the
    // vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active
    // as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    return p;
}

void polygon_free(polygon *polygon) {
    free(polygon->vertices);
    free(polygon->indices);
    free(polygon);
    // TODO: free on GPU as well!
}