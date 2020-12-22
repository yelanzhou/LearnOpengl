#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambientColor = ambientStrength * lightColor;
    
    vec3 lightDir = normalize(lightPos-FragPos);
    vec3 nor = normalize(Normal);
    float diffuseStrength = max(dot(lightDir,nor),0.0);
    vec3 diffuseColor = diffuseStrength * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflect = reflect(-lightDir,nor);
    float specular = max(dot(viewDir,reflect),0.0);
    vec3 specularColor = specularStrength * specular * lightColor;


    vec3 result = (ambientColor + diffuseColor + specularColor) * objectColor;
    FragColor = vec4(result, 1.0);

}

