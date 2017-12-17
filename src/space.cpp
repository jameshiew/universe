//
// Created by James Hiew on 15/12/2017.
//

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

World *World_new() {
    return (World *)malloc(sizeof(World));
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
                drawInstructions->push_back(test(origin));
            }
        }
    }
    return drawInstructions;
}

