#version 150 core

in vec3 position;
in vec3 colour;

out vec3 Colour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Colour = colour;
    gl_Position = projection * view * model * vec4(position, 1.0);
}
