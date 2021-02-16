#version 330 core

layout(location = 0) out vec4 col;

uniform vec4 color;

void main()
{
    col = color;
}