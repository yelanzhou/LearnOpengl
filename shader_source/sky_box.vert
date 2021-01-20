#version 330 core

layout(location=0) in vec3 aPos;

out Block
{
    out vec3 texCoord;
}vs_out;

uniform mat4 projection;
uniform mat4 view;



void main()
{
    vs_out.texCoord = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}