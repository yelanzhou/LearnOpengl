#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 worldPosition;
in vec3 worldNormal;

uniform Material material;
uniform Light light;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;
void main()
{

    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPos - worldPosition);
    float diff = max(dot(lightDir,normal),0.0);
    

    vec3 viewDir = normalize(viewPos - worldPosition);
    vec3 reflectDir = reflect(-lightDir,normal);
    float specular = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    FragColor = vec4(light.ambient * material.ambient + diff * light.diffuse * material.diffuse + specular* light.specular*material.specular,1.0);

}