#version 330 core

in vec2 texCoord;

uniform sampler2D depthMap;

out vec4 FragColor;

void main()
{
    float val = texture(depthMap,texCoord).r;
    FragColor = vec4(vec3(val),1.0);
}