//
// Created by James Hiew on 09/12/2017.
//

#ifndef UNIVERSE_SHADERS_H
#define UNIVERSE_SHADERS_H

GLuint get_shader_program();
GLuint make_shader(GLenum type, const char *source);
GLuint load_shader(GLenum type, const char *path);
GLuint load_program(const char *vertexShaderPath, const char *fragmentShaderPath);
GLuint make_program(GLuint vertexShader, GLuint fragmentShader);

#endif //UNIVERSE_SHADERS_H