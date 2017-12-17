//
// Created by James Hiew on 09/12/2017.
//

#include "render.hpp"
#include <glad/glad.h>
#include <cstdio>
#include <cstdlib>
#include <stb_image.h>

#include "shaders.hpp"
#include "util.hpp"

GLuint make_shader(GLenum type, const char *source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        size_t length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, (GLint *)&length);
        GLchar *info = (GLchar *) calloc(length, sizeof(GLchar));
        glGetShaderInfoLog(shader, (GLsizei) length, NULL, info);
        fprintf(stderr, "glCompileShader failed:\n%s\n", info);
        free(info);
    }
    return shader;
}

GLuint load_shader(GLenum type, const char *path) {
    char *data = load_file(path);
    GLuint result = make_shader(type, data);
    free(data);
    return result;
}

ShaderProgram *ShaderProgram_load(const char *vertexShaderPath, const char *fragmentShaderPath) {
    GLuint vertexShader = load_shader(GL_VERTEX_SHADER, vertexShaderPath);
    GLuint fragmentShader = load_shader(GL_FRAGMENT_SHADER, fragmentShaderPath);
    return ShaderProgram_new(vertexShader, fragmentShader);
}

ShaderProgram *ShaderProgram_new(GLuint vertexShader, GLuint fragmentShader) {
    auto program = (ShaderProgram *)malloc(sizeof(ShaderProgram));
    program->type = SHADER_PROGRAM_COLORED_PHONG;
    program->id = glCreateProgram();
    glAttachShader(program->id, vertexShader);
    glAttachShader(program->id, fragmentShader);
    glLinkProgram(program->id);
    GLint status;
    glGetProgramiv(program->id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        size_t length;
        glGetProgramiv(program->id, GL_INFO_LOG_LENGTH, (GLint *)&length);
        GLchar *info = (GLchar *) calloc(length, sizeof(GLchar));
        glGetProgramInfoLog(program->id, (GLsizei) length, NULL, info);
        fprintf(stderr, "glLinkProgram failed: %s\n", info);
        free(info);
    }
    glDetachShader(program->id, vertexShader);
    glDetachShader(program->id, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

GLuint load_texture(const char *texturePath) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        fputs("Failed to load texture", stderr);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}