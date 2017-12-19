//
// Created by James Hiew on 15/12/2017.
//

#include <random>
#include <spdlog.h>
#include "space.hpp"
#include "shaders.hpp"

const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 DOWN = -UP;
const glm::vec3 NORTH = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 WEST = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 EAST = -WEST;
const glm::vec3 SOUTH = -NORTH;

const glm::mat4 IDENTITY = glm::mat4();

void World::generate(World *world, glm::ivec3 coords) {
    auto chunk = world->chunks->operator[](coords);
    if (coords.y == 0) {
        for (int _x = 0; _x < 32; _x++) {  // ground
            for (int _z = 0; _z < 32; _z++) {
                chunk.add(glm::ivec3(_x, 0, _z), { .id = 'g' });
            }
        }
        for (int h = 1; h < 10; h++) {  // tree
            chunk.add(glm::ivec3(16, h, 16), { .id = 'w' });
        }
    }
    world->chunks->operator[](coords) = chunk;
    spdlog::get("worldgen")->debug("Generated chunk: {}, {}, {}", coords.x, coords.y, coords.z);
}

World *World_new() {
    auto world = (World *)malloc(sizeof(World));
    world->chunks = new std::unordered_map<glm::ivec3, Chunk>();
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
    delete world->chunks;
    free(world);
}

GLuint grassTexture = 0, woodTexture = 0, leavesTexture = 0;

std::list<DrawInstruction *> *World_get_draw_instructions(World *world, glm::vec3 position, int range) {
    if (grassTexture == 0) {
        grassTexture = load_texture("../../textures/grass.png");
        woodTexture = load_texture("../../textures/wood.png");
        leavesTexture = load_texture("../../textures/leaves.png");
    }
    auto drawInstructions = new std::list<DrawInstruction *>();
    auto px = (int) round(position.x / 32.f);
    auto py = (int) round(position.y / 32.f);
    auto pz = (int) round(position.z / 32.f);
    for (int x = px - range; x < px + range + 1; x++) {
        for (int y = py - range; y < py + range + 1; y++) {
            for (int z = pz - range; z < pz + range + 1; z++) {
                if (world->chunks->find(glm::ivec3(x, y, z)) == world->chunks->end()) {
                    world->generate(world, glm::ivec3(x, y, z));
                };
                auto chunk = world->chunks->operator[](glm::ivec3(x, y, z));
                auto origin = glm::vec3(x * 32.f, y * 32.f, z * 32.f);
                auto grass = DrawInstruction_cube();
                grass->texture = grassTexture;
                auto wood = DrawInstruction_cube();
                wood->texture = woodTexture;
                auto leaves = DrawInstruction_cube();
                leaves->texture = leavesTexture;
                for (int _x = 0; _x < 32; _x++) {
                    for (int _y = 0; _y < 32; _y++) {
                        for (int _z = 0; _z < 32; _z++) {
                            switch (chunk.get(_x, _y, _z)->id) {
                                case 'g': {
                                    auto nposition = glm::vec3((float) _x, (float) _y, (float) _z);
                                    nposition += origin;
                                    grass->positions->push_back(nposition);
                                    break;
                                }
                                case 'w': {
                                    auto nposition = glm::vec3((float) _x, (float) _y, (float) _z);
                                    nposition += origin;
                                    wood->positions->push_back(nposition);
                                    break;
                                }
                                case 'l': {
                                    auto nposition = glm::vec3((float) _x, (float) _y, (float) _z);
                                    nposition += origin;
                                    leaves->positions->push_back(nposition);
                                    break;
                                }
                                default: {
                                    break;
                                }
                            }
                        }
                    }
                }
                drawInstructions->push_back(grass);
                drawInstructions->push_back(wood);
                drawInstructions->push_back(leaves);
            }
        }
    }
    return drawInstructions;
}

void Chunk::add(glm::ivec3 coords, Block block) {
    this->blocks[coords.x][coords.y][coords.z] = block;
}

void Chunk::remove(glm::ivec3 coords) {
    this->blocks[coords.x][coords.y][coords.z] = { .id = 0 };
}

Block *Chunk::get(int x, int y, int z) {
    return &this->blocks[x][y][z];
}
