#version 330 core

in vec3 world_pos;
in vec3 world_normal;
in vec2 texCoords;

uniform int bling;
uniform vec3 light_pos;
uniform vec3 view_pos;
uniform sampler2D  diffuse1;

out vec4 FragColor;


void main()
{
    vec3 color1 = texture(diffuse1,texCoords).rgb;
    vec3 ambient =0.05 * color1;

    vec3 light_dir = normalize(light_pos - world_pos);
    vec3 normal = normalize(world_normal);

    vec3 diffuse = max(dot(light_dir,normal),0.0) *  color1;

    vec3 view_dir = normalize(view_pos-world_pos);
    float spec = 0;
    if(bling == 0)
    {
        vec3 reflect_dir = normalize(reflect(-light_dir,normal));
        spec = pow(max(dot(reflect_dir,view_dir),0.0),8);

    }else
    {
        vec3 half_dir = normalize(light_dir+view_dir);
        spec = pow(max(dot(half_dir,normal),0.0),32);
    }

    vec3 specular = spec * vec3(0.3);
    FragColor = vec4(ambient + diffuse + specular,1.0);

    FragColor.rgb = pow(FragColor.rgb,vec3(1/2.2));


}