//
// Created by James Hiew on 15/12/2017.
//

#include <random>
#include "space.hpp"
#include "polygon.hpp"

const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 DOWN = -UP;
const glm::vec3 NORTH = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 WEST = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 EAST = -WEST;
const glm::vec3 SOUTH = -NORTH;

const glm::mat4 IDENTITY = glm::mat4();

Chunk *Chunk_new() {
    return (Chunk *)malloc(sizeof(Chunk));
}

void Chunk_free(Chunk *chunk) {
    free(chunk);
}

void *World::generate(World *world, int x, int y, int z) {
    world->chunks[x][y][z] = Chunk_new();
    std::default_random_engine prng;
    std::uniform_real_distribution<float> distribution(0.f, 100.f);
    for (int _x = 0; _x < 32; _x++) {
        for (int _y = -1; _y < 32; _y++) {
            for (int _z = -1; _z < 32; _z++) {
                world->chunks[x][y][z]->blocks[_x][_y][_z] = reinterpret_cast<bool *>(distribution(prng) > 90.f);
            }
        }
    }
}

World *World_new() {
    auto world = (World *)malloc(sizeof(World));
    // pregenerate origin
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            for (int z = -1; z < 2; z++) {
                world->generate(world, x, y, z);
            }
        }
    }
}

void World_free(World *world) {
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            for (int z = 0; z < 16; z++) {
                free(world->chunks[x][y][z]);
            }
        }
    }
    free(world);
}

std::list<DrawInstruction *> *World_get_draw_instructions(World *world, glm::vec3 position) {
    auto drawInstructions = new std::list<DrawInstruction *>();
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            for (int z = -1; z < 2; z++) {
                auto chunk = world->chunks[x][y][z];
                auto origin = glm::vec3(x * 32.f, y * 32.f, z * 32.f);

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

                draw->count = 1024;
                draw->positions = (glm::vec3 *)(malloc(sizeof(glm::vec3) * draw->count));
                std::default_random_engine prng;
                std::uniform_real_distribution<float> distribution(-100.f,100.f);
                for (int i = 0; i < draw->count; i++) {
                    draw->positions[i] = glm::vec3(distribution(prng), distribution(prng), distribution(prng));
                    draw->positions[i] += origin;
                }
                drawInstructions->push_back(draw);
            }
        }
    }
    return drawInstructions;
}
