#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 world_pos;
out vec3 world_normal;
out vec2 texCoords;

void main()
{

    world_pos = (model * vec4(aPos,1.0)).xyz;
    world_normal = mat3(transpose(inverse(model))) * aNormal;
    texCoords = aTexCoords;
    gl_Position =  projection * view * vec4(world_pos,1.0); 

}
