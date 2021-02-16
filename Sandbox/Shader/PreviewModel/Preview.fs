#version 330 core

out vec4 col;
in vec2 tex;

uniform sampler2D screen_tex;

void main()
{
    col = texture(screen_tex, tex);
}