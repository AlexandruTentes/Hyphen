#version 330 core

out vec4 FragColor;
in vec2 texcoord;
uniform sampler2D filtertex;

void main()
{
    FragColor = texture(filtertex, texcoord);
}