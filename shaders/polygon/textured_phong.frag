#version 330 core
in vec3 Normal;
in vec3 WorldPosition;
in vec2 TextureCoordinates;

uniform vec3 lightPosition;
uniform sampler2D u_texture;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

out vec4 Color;

void main(){
    float ambientStrength = 0.6f;
    vec3 ambientLight = ambientStrength * lightColor;

    vec3 lightDirection = normalize(lightPosition - WorldPosition);

    float diffuseStrength = max(dot(normalize(Normal), lightDirection), 0.0);
    vec3 diffuseLight = diffuseStrength * lightColor;

    Color = vec4((ambientLight + diffuseLight) * texture(u_texture, TexCoord), 1.0f);
}