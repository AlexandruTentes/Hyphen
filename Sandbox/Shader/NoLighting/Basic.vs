#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;

uniform mat4 transform_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main()
{
    gl_Position = projection_mat * view_mat * transform_mat * vec4(position, 1.0f);
}