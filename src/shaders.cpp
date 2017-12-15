//
// Created by James Hiew on 09/12/2017.
//

#include <glad/glad.h>
#include <cstdio>
#include <cstdlib>

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

GLuint load_program(const char *vertexShaderPath, const char *fragmentShaderPath) {
    GLuint vertexShader = load_shader(GL_VERTEX_SHADER, vertexShaderPath);
    GLuint fragmentShader = load_shader(GL_FRAGMENT_SHADER, fragmentShaderPath);
    GLuint program = make_program(vertexShader, fragmentShader);
    return program;
}

GLuint make_program(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        size_t length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, (GLint *)&length);
        GLchar *info = (GLchar *) calloc(length, sizeof(GLchar));
        glGetProgramInfoLog(program, (GLsizei) length, NULL, info);
        fprintf(stderr, "glLinkProgram failed: %s\n", info);
        free(info);
    }
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}
