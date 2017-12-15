#version 330 core
in vec3 Normal;
in vec3 WorldPosition;

uniform vec3 color;
uniform vec3 lightPosition;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

out vec4 Color;

void main(){
    float ambientStrength = 0.3f;
    vec3 ambientLight = ambientStrength * lightColor;

    vec3 lightDirection = normalize(lightPosition - WorldPosition);

    float diffuseStrength = max(dot(normalize(Normal), lightDirection), 0.0);
    vec3 diffuseLight = diffuseStrength * lightColor;

    Color = vec4((ambientLight + diffuseLight) * color, 1.0f);
}