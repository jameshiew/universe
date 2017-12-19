//
// Created by James Hiew on 15/12/2017.
//

#ifndef UNIVERSE_SPACE_HPP
#define UNIVERSE_SPACE_HPP
#include <glm/vec3.hpp>
#include <list>
#include <glm/detail/type_mat.hpp>
#include "render.hpp"
#include <map>
#include <unordered_map>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

extern const glm::vec3 UP;
extern const glm::vec3 DOWN;
extern const glm::vec3 NORTH;
extern const glm::vec3 WEST;
extern const glm::vec3 EAST;
extern const glm::vec3 SOUTH;

extern const glm::mat4 IDENTITY;

struct Block {
    char id;
};

class Chunk {
private:
    Block blocks[32][32][32];
public:
    void add(glm::ivec3 coords, Block block);
    Block *get(int x, int y, int z);
    void remove(glm::ivec3 coords);
};

typedef struct World {
    void generate(World*, glm::ivec3);
    std::unordered_map<glm::ivec3, Chunk> *chunks;
} World;

World *World_new();
void World_free(World *world);
std::list<DrawInstruction *> *World_get_draw_instructions(World *world, glm::vec3 position, int range);

#endif //UNIVERSE_SPACE_HPP
