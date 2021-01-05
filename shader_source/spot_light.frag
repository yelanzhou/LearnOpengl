#version 330 core

struct Material
{
    sampler2D  diffuse;
    sampler2D  specular;
    float      shininess;
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



in vec3 FragPos;
in vec3 FragNormal;
in vec2 FragTexCoord;

uniform vec3 viewPos;
uniform Material material;
uniform SpotLight spotLight;

out vec4 FragColor;

void main()
{
    vec3 lightDir=normalize(spotLight.pos - FragPos);
    float theta = dot(-lightDir,spotLight.direction);

 

    float epsilon = spotLight.cutOff - spotLight.outterCutOff;
    float intensity =  clamp((theta - spotLight.outterCutOff)/ epsilon,0.0,1.0);

    vec3 ambient = spotLight.ambient * (texture(material.diffuse,FragTexCoord)).rgb;  

    vec3 normal = normalize(FragNormal);
    float diff = max(dot(lightDir,normal),0);
    vec3 diffuse = intensity * diff * spotLight.diffuse * (texture(material.diffuse,FragTexCoord)).rgb;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(reflectDir,viewDir),0.0),material.shininess);
    vec3 specular = intensity * spec * spotLight.specular * (texture(material.specular,FragTexCoord)).rgb;

    float distance = length(spotLight.pos - FragPos);
    float attenuation = 1 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * distance * distance);

    vec3 result = ambient + diffuse * attenuation+ specular * attenuation;
    //result *= attenuation;
    FragColor = vec4(result,1.0);


}


