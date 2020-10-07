#version 330 core

out vec4 position;

varying lowp vec4 frag_col;

void main()
{
    position = frag_col;
}