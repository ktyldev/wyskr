#version 150 core

in vec2 position;
in vec3 colour;

out vec3 Colour;

uniform mat4 trans;

void main()
{
    Colour = colour;
    gl_Position = trans * vec4(position, 0.0, 1.0);
}
