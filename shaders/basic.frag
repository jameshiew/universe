#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

uniform vec4 baseColor;

void main()
{
    FragColor = baseColor + vec4(ourColor, 1.0);
}