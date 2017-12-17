//
// Created by James Hiew on 12/12/2017.
//
#include <cstddef>
#include <cstdlib>
#include <glad/glad.h>
#include <memory.h>
#include <random>

#include "polygon.hpp"

const size_t VERTEX_SIZE = 5 * sizeof(float);

Polygon *abc(VERTEX_TYPE vertexType) {
    auto *p = (Polygon *) malloc(sizeof(Polygon));
    p->vertexType = vertexType;

    p->numberOfVertices = 24;
    size_t v = p->numberOfVertices * VERTEX_SIZE;
    p->vertices = (float *) malloc(v);
    float vertices[] = {
            // south
            0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            // east
            1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            // north
            1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            // west
            0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            // down
            0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            // up
            0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    };
    memcpy(p->vertices, vertices, v);

    p->numberOfTriangles = 12;
    size_t t = p->numberOfTriangles * VERTEX_SIZE;
    p->indices = (unsigned int *) malloc(t);
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 2,  // first Triangle
            0, 2, 3,  // second Triangle
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void *) 0);
    glEnableVertexAttribArray(0);
    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void *) (3 * sizeof(float)));
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

void Polygon_free(Polygon *polygon) {
    free(polygon->vertices);
    free(polygon->indices);
    free(polygon);
    // TODO: free on GPU as well!
}

DrawInstruction *test() {
    auto draw = (DrawInstruction *)malloc(sizeof(DrawInstruction));
    glGenVertexArrays(1, &(draw->vao));
    glBindVertexArray(draw->vao);
//    glGenBuffers(1, &(draw->ebo));
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, draw->ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, t, p->indices, GL_STATIC_DRAW);

    draw->vertexSize = 6 * sizeof(float);
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    glGenBuffers(1, &(draw->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, draw->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, draw->vertexSize, nullptr);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, draw->vertexSize, (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    draw->mode = GL_TRIANGLES;
    draw->count = 36;
    draw->numberOfOffsets = 100;
    draw->offsets = (glm::vec3 *)(malloc(sizeof(glm::vec3) * draw->numberOfOffsets));

    std::default_random_engine prng;
    std::uniform_real_distribution<float> distribution(-100.f,100.f);
    for (int i = 0; i < draw->numberOfOffsets; i++) {
        draw->offsets[i] = glm::vec3(distribution(prng), distribution(prng), distribution(prng));
    }
    return draw;
}

Polygon *Cube_new(ShaderProgram *shaderProgram) {
    auto *p = (Polygon *)malloc(sizeof(Polygon));
    switch (shaderProgram->type) {
        case SHADER_PROGRAM_COLORED_PHONG:
            break;
        default:
            break;
    }
    return p;
}
