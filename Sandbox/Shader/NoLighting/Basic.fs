#version 330 core

layout(location = 0) out vec4 col;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform float opacity;
uniform Material material;

void main()
{
    //Final lighting
    col = vec4(material.ambient, opacity);
}