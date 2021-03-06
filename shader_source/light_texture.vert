#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexcoord;

uniform  mat4 model;
uniform  mat4 view;
uniform  mat4 projection;

out vec3 worldNormal;
out vec3 worldPostion;
out vec2 texCoord;

void main()
{
    texCoord = aTexcoord;
    worldPostion =vec3(model * vec4(aPos,1.0));
    worldNormal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * vec4(worldPostion,1.0);

}

