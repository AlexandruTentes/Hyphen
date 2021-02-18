#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 transform_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main()
{
    gl_Position = projection_mat * view_mat * transform_mat * position;
}