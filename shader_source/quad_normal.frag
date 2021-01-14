#version 330 core

in vec2 texCoord;

uniform sampler2D screenTexture;

out vec4 FragColor;



void main()
{
   
    vec3 col = texture(screenTexture, texCoord).rgb;

    float a = (col.r + col.b + col.g)/ 3;

    FragColor = vec4(a,a,a, 1.0);
}