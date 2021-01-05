#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 worldPosition;
in vec3 worldNormal;
in vec2 texCoord;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

out vec4 FragColor;
void main()
{
    vec3 ambient = light.ambient * texture(material.diffuse,texCoord).rgb;

    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(light.position - worldPosition);
    float diff = max(dot(lightDir,normal),0.0);
    vec3 diffuse = diff * light.diffuse * texture(material.diffuse,texCoord).rgb;
    

    vec3 viewDir = normalize(viewPos - worldPosition);
    vec3 reflectDir = reflect(-lightDir,normal);
    float spe = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    vec3 specular = spe * light.specular *  texture(material.specular,texCoord).rgb;

    float distance = length(worldPosition-light.position);
    float attenuataion  = 1 / (light.constant + distance * light.linear + distance * distance * light.quadratic);


    FragColor = vec4((ambient + diffuse + specular) * attenuataion,1.0);

}