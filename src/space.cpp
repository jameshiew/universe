//
// Created by James Hiew on 15/12/2017.
//

#include <random>
#include <spdlog.h>
#include "space.hpp"

const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 DOWN = -UP;
const glm::vec3 NORTH = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 WEST = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 EAST = -WEST;
const glm::vec3 SOUTH = -NORTH;

const glm::mat4 IDENTITY = glm::mat4();

Chunk *Chunk_new() {
    return (Chunk *)calloc(1, sizeof(Chunk));
}

void Chunk_free(Chunk *chunk) {
    free(chunk->blocks);
    free(chunk);
}

void World::generate(World *world, glm::ivec3 coords) {
    auto chunk = Chunk_new();
    world->chunks->[coords] = chunk;
    for (int _x = 0; _x < 32; _x++) {
        for (int _y = 0; _y < 32; _y++) {
            chunk->blocks[_x][_y][0] = 'a';
        }
    }
    spdlog::get("worldgen")->debug("Generated chunk: {0:d}, {1:d}, {2:d}", coords.x, coords.y, coords.z);
}

World *World_new() {
    auto world = (World *)malloc(sizeof(World));
    world->chunks = new std::map<glm::ivec3, Chunk>();
    // pregenerate origin
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            for (int z = -1; z < 2; z++) {
                world->generate(world, glm::ivec3(x, y, z));
            }
        }
    }
    return world;
}

void World_free(World *world) {
    free(world->chunks);
    free(world);
}

std::list<DrawInstruction *> *World_get_draw_instructions(World *world, glm::vec3 position) {
    auto drawInstructions = new std::list<DrawInstruction *>();
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            for (int z = -1; z < 2; z++) {
                auto origin = glm::vec3(x * 32.f, y * 32.f, z * 32.f);
                auto draw = DrawInstruction_cube();
                draw->positions = new std::list<glm::vec3>();

                auto chunk = world->chunks->[glm::ivec3(x, y, z)];
                for (int _x = 0; _x < 32; _x++) {
                    for (int _y = 0; _y < 32; _y++) {
                        for (int _z = 0; _z < 32; _z++) {
                            auto coords = glm::ivec3(_x, _y, _z);
                            if (chunk->blocks[_x][_y][_z] == 'a') {
                                auto nposition = glm::vec3((float) x, (float) y, (float) z);
                                nposition += origin;
                                draw->positions->push_back(nposition);
                            }
                        }
                    }
                }
                drawInstructions->push_back(draw);
            }
        }
    }
    return drawInstructions;
}
