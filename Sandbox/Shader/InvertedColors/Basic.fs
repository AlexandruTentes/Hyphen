#version 330 core

layout(location = 0) out vec4 col;

uniform vec4 color;

void main()
{
    col = vec4(1.0, 1.0, 1.0, 2.0) - color;
}