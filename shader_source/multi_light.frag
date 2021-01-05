#version 330 core

struct Material
{
    sampler2D  diffuse;
    sampler2D  specular;
    float      shininess;
};

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 pos;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float cutOff;
    float outterCutOff;

    float constant;
    float linear;
    float quadratic;
};

#define NR_POINT_LIGHTS  4

in vec3 FragPos;
in vec3 FragNormal;
in vec2 FragTexCoord;

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

out vec4 FragColor;


vec3 calcDirLight(DirLight light,vec3 normal,vec3 viewDir);
vec3 calcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir);


void main()
{

    vec3 norm = normalize(FragNormal);
    vec3 viewDir = normalize(viewPos - FragPos);
    

    vec3 result = calcDirLight(dirLight, norm, viewDir);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += calcPointLight(pointLights[i], norm, FragPos, viewDir);    
    
    // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}


vec3 calcDirLight(DirLight light,vec3 normal,vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    vec3 ambient = light.ambient * (texture(material.diffuse,FragTexCoord)).rgb;

    float diff = max(dot(normal,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * (texture(material.diffuse,FragTexCoord)).rgb;

   
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    vec3 specular = light.specular * spec * (texture(material.specular,FragTexCoord)).rgb;

    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir)
{
    vec3 ambient = light.ambient * (texture(material.diffuse,FragTexCoord)).rgb;

    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * (texture(material.diffuse,FragTexCoord)).rgb;
  
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    vec3 specular = light.specular * spec * (texture(material.specular,FragTexCoord)).rgb;

    float distance = length(light.position - FragPos);
    float attenuation = 1 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    return (ambient + diffuse + specular)* attenuation;
     
}