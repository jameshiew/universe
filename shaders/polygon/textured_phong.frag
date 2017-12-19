#version 330 core
in vec3 Normal;
in vec3 WorldPosition;
in vec2 TextureCoordinates;

uniform vec3 lightPosition;
uniform sampler2D u_texture;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

out vec4 Color;

void main(){
    float ambientStrength = 0.9f;
    vec3 ambientLight = ambientStrength * lightColor;

    vec3 diffuseLightDirection = normalize(lightPosition - WorldPosition);

    float diffuseStrength = max(dot(normalize(Normal), diffuseLightDirection), 0.0);
    vec3 diffuseLight = diffuseStrength * lightColor;

    Color = vec4(ambientLight + diffuseLight, 1.0f) * texture(u_texture, TextureCoordinates);
}