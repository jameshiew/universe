//
// Created by James Hiew on 09/12/2017.
//

#include <glad/glad.h>
#include <cstdio>
#include <cstdlib>
#include <stb_image.h>
#include <spdlog.h>

#include "shaders.hpp"
#include "util.hpp"

GLuint make_shader(GLenum type, const char *source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLsizei length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, (GLint *)&length);
        auto *info = (GLchar *) calloc((size_t) length, sizeof(GLchar));
        glGetShaderInfoLog(shader, length, nullptr, info);
        spdlog::get("glad")->error("glCompileShader failed: {}", info);
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
    program->id = glCreateProgram();
    glAttachShader(program->id, vertexShader);
    glAttachShader(program->id, fragmentShader);
    glLinkProgram(program->id);
    GLint status;
    glGetProgramiv(program->id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        size_t length;
        glGetProgramiv(program->id, GL_INFO_LOG_LENGTH, (GLint *)&length);
        auto *info = (GLchar *) calloc(length, sizeof(GLchar));
        glGetProgramInfoLog(program->id, (GLsizei) length, nullptr, info);
        spdlog::get("glad")->error("glLinkProgram failed: {}", info);
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
        spdlog::get("glad")->error("Failed to load texture from {}", texturePath);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}