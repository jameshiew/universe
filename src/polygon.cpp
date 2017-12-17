//
// Created by James Hiew on 12/12/2017.
//
#include <cstddef>
#include <cstdlib>
#include <glad/glad.h>
#include <memory.h>
#include <random>

#include "polygon.hpp"

DrawInstruction *test() {
    auto draw = (DrawInstruction *)malloc(sizeof(DrawInstruction));
    glGenVertexArrays(1, &(draw->vao));
    glBindVertexArray(draw->vao);

    draw->vertexSize = 8 * sizeof(float);
    draw->vertexCount = 24;
    draw->mode = GL_TRIANGLE_STRIP;

    float CUBE_STRIP_VERTICES[] = {
            // south          // normal         // texture
            0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            // east
            1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            // north
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            // west
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            // down
            0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            // up
            0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    };

    glGenBuffers(1, &(draw->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, draw->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_STRIP_VERTICES), CUBE_STRIP_VERTICES, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, draw->vertexSize, nullptr);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, draw->vertexSize, (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // uv attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, draw->vertexSize, (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    draw->count = 100;
    draw->positions = (glm::vec3 *)(malloc(sizeof(glm::vec3) * draw->count));
    std::default_random_engine prng;
    std::uniform_real_distribution<float> distribution(-100.f,100.f);
    for (int i = 0; i < draw->count; i++) {
        draw->positions[i] = glm::vec3(distribution(prng), distribution(prng), distribution(prng));
    }
    return draw;
}
