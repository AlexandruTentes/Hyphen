#version 330 core

layout(location = 0) out vec4 col;

in vec3 vs_normal;
in vec3 vs_frag_position;
in vec3 vs_vertex_position;
in vec3 vs_view;

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
uniform Light light;
uniform Material material;

vec3 light_math(Light l, Material m, vec3 normal, vec3 view_dir)
{
    float dist = 6.0f;
    float att = 1.0f;//clamp(10.0f / dist, 0.0f, 1.0f);
   
    //Ambient
    vec3 ambient = l.ambient * m.ambient * att;
   
    //Diffuse
    vec3 light_dir = normalize(l.position - vs_frag_position);
    float diff = max(dot(normal, light_dir), 0.1);
    vec3 diffuse = l.diffuse * diff * m.diffuse * att;

    //Specular
    vec3 reflect_dir = normalize(reflect(-view_dir, normal));
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), m.shininess) * att;
    vec3 specular = l.specular * spec * m.specular;

    return ambient + diffuse + specular;
};

void main()
{
    vec3 norm = normalize(vs_normal);
    vec3 view_dir = normalize(vs_view - vs_frag_position);

    //Final lighting
    vec3 result = light_math(light, material, norm, view_dir);
    col = vec4(result, opacity);
}