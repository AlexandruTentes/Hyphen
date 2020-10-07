#version 330 core

attribute vec4 position;
attribute vec4 color;

varying lowp vec4 frag_col;

void main()
{
    frag_col = color;
    gl_Position = position;
}