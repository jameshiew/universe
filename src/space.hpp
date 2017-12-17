//
// Created by James Hiew on 15/12/2017.
//

#ifndef UNIVERSE_SPACE_HPP
#define UNIVERSE_SPACE_HPP

#include <glm/vec3.hpp>

extern glm::vec3 UP;
extern glm::vec3 DOWN;
extern glm::vec3 NORTH;
extern glm::vec3 WEST;
extern glm::vec3 EAST;
extern glm::vec3 SOUTH;

typedef struct Chunk {
    char *blocks[32][32][32];
} Chunk;

Chunk *Chunk_new();
void Chunk_free(Chunk *chunk);

typedef struct World {
    Chunk *chunks[16][16][16];
} World;

World *World_new();
void World_free(World *world);

#endif //UNIVERSE_SPACE_HPP
