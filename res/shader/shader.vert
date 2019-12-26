#version 150 core

uniform vec3 ambient;
uniform vec3 lightVector;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 position;
in vec3 normal;
in vec3 colour;

out vec3 fragVert;
out vec3 fragNormal;
out vec3 fragColour;

void main()
{
    mat4 camera = projection * view;

    //vec4 surfaceToLight = normalize(vec4(-lightVector, 1.0));
    //vec4 adjustedNormal = normalize(model * vec4(normal, 1.0));

    //float diffuseBrightness = clamp(dot(adjustedNormal, surfaceToLight), 0.0, 1.0);

    //fragColour = clamp(ambient + colour * diffuseBrightness, 0.0, 1.0);
    //Colour = clamp(ambient + colour, 0, 1);

    fragColour = colour;
    fragNormal = normal;
    fragVert = position;

    gl_Position = camera * model * vec4(position, 1.0);
}
