#version 330 core

in vec3 texCoord;

uniform samplerCube skyBox;

out vec4 FragColor;

void main()
{
    FragColor = texture(skyBox, texCoord);
}