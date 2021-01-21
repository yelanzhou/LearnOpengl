#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

out Block
{
    vec3 color;
} vs_out;

void main()
{
    vs_out.color = aColor;
    gl_Position = vec4(aPos,0.0,1.0);
}