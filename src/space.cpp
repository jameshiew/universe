//
// Created by James Hiew on 15/12/2017.
//

#include "space.hpp"

glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 DOWN = -UP;
glm::vec3 NORTH = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 WEST = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 EAST = -WEST;
glm::vec3 SOUTH = -NORTH;

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

