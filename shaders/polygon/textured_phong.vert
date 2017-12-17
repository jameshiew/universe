#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 WorldPosition;
out vec3 Normal;
out vec2 TextureCoordinates;

void main() {
    WorldPosition = vec3(model * vec4(position, 1.0f));
    gl_Position = projection * view * vec4(WorldPosition, 1.0f);
    Normal = normal;
    TextureCoordinates = uv;
}