#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;

out vec3 vs_normal;
out vec3 vs_frag_position;
out vec3 vs_vertex_position;
out vec3 vs_view;

uniform vec3 view_position;
uniform mat4 transform_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main()
{
    vs_frag_position = vec3(transform_mat * vec4(position, 1.0f));
    vs_vertex_position = (view_mat * transform_mat * vec4(position, 1.0f)).xyz;
    vs_normal = mat3(transpose(inverse(transform_mat))) * normal;
    vs_view = view_position;

    gl_Position = projection_mat * view_mat * transform_mat * vec4(position, 1.0f);
}