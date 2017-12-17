//
// Created by James Hiew on 09/12/2017.
//

#ifndef UNIVERSE_SHADERS_H
#define UNIVERSE_SHADERS_H

typedef enum SHADER_PROGRAM {
    SHADER_PROGRAM_COLORED_PHONG,
} SHADER_PROGRAM;

typedef struct ShaderProgram {
    SHADER_PROGRAM type;
    GLuint id;
} ShaderProgram;

GLuint make_shader(GLenum type, const char *source);
GLuint load_shader(GLenum type, const char *path);
ShaderProgram *ShaderProgram_load(const char *vertexShaderPath, const char *fragmentShaderPath);
ShaderProgram *ShaderProgram_new(GLuint vertexShader, GLuint fragmentShader);

GLuint load_texture(const char* texturePath);

#endif //UNIVERSE_SHADERS_H