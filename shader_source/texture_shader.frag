#version 330 core
out vec4 FragColor;
in vec3 oColor;
in vec2 oTexCord;
uniform sampler2D texture1;

void main()
{
   FragColor = texture(texture1,oTexCord);
   //FragColor = vec4(oColor,1);
}