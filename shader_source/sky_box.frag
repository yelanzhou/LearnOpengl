#version 330 core


in Block
{
   vec3 texCoord; 
} block_in;

uniform samplerCube skyBox;

out vec4 FragColor;

void main()
{
    FragColor = texture(skyBox, block_in.texCoord);
}