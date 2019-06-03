#version 150 core

in vec3 position;
in vec3 normal;
in vec3 colour;

out vec3 Colour;

uniform vec3 ambient;
uniform vec3 lightVector;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 complete = projection * view;

    vec4 reverseLight = vec4(-lightVector, 1.0);
    vec4 adjustedNormal = normalize(model * vec4(normal, 1.0));
    float diffuseBrightness = clamp(dot(adjustedNormal, reverseLight), 0.0, 1.0);

    Colour = clamp(ambient + colour * diffuseBrightness, 0.0, 1.0);
    gl_Position = complete * model * vec4(position, 1.0);
}
