#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 FragNormal;
out vec2 FragTexCoord;

void main()
{
    FragTexCoord = aTexCoord;
    FragPos = vec3(model * vec4(aPos,1.0));
    FragNormal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * vec4(FragPos,1.0);
    
}
