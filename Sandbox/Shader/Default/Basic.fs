#version 330 core

#define COLOR_CORRECTION	0.00390625

layout(location = 0) out vec4 col;

in vec3 vs_normal;
in vec3 vs_frag_position;
in vec3 vs_vertex_position;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform float opacity;
uniform vec3 view_position;

uniform Light light;
uniform Material material;

vec3 light_math(Light l, Material m, vec3 normal, vec3 view_dir)
{
    m.ambient *= COLOR_CORRECTION;
    m.diffuse *= COLOR_CORRECTION;
    l.ambient *= COLOR_CORRECTION;
    //l.diffuse *= COLOR_CORRECTION;
    //Ambient
    vec3 ambient = l.ambient * m.ambient;
   
    //Diffuse
    vec3 light_dir = normalize(l.position - vs_frag_position);
    float diff = max(dot(normal, light_dir), 0.1);
    vec3 diffuse = l.diffuse * diff * m.diffuse;

    //Specular
    vec3 reflect_dir = normalize(reflect(-view_dir, normal));
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = l.specular * spec * m.specular;

    vec3 rez = ambient + diffuse + specular;

    return rez;
};

void main()
{
    vec3 norm = normalize(vs_normal);
    vec3 view_dir = normalize(view_position - vs_frag_position);

    //Final lighting
    vec3 result = light_math(light, material, norm, view_dir);
    col = vec4(result, opacity);
}