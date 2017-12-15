#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 lightColor;

void main()
{
    float ambientStrength = 0.7;
    vec4 ambient = vec4(ambientStrength * lightColor, 1.0);
    FragColor = ambient * texture(ourTexture, TexCoord);
}
