#version 150 core

uniform mat4 model;
uniform vec3 cameraPosition;
uniform vec3 ambient;
uniform vec3 lightColour;
uniform vec4 lightPosition;

in vec3 fragVert;
in vec3 fragNormal;
in vec3 fragColour;

out vec4 outColour;

vec3 applyLight(vec3 surfaceColour, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera)
{
    // directional light
    vec3 surfaceToLight = normalize(lightPosition.xyz);
    float attenuation = 1.0;

    // diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColour.rgb * lightColour;

    return ambient + diffuse;
}

void main()
{
    vec3 normal = normalize(transpose(inverse(mat3(model))) * fragNormal);
    vec3 surfacePos = vec3(model * vec4(fragVert, 1));
    vec4 surfaceColour = vec4(fragColour, 1);
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);

    vec3 linearColour = applyLight(surfaceColour.rgb, normal, surfacePos, surfaceToCamera);

    outColour = vec4(linearColour, 1.0);
    //outColour = vec4(fragColour, 1.0);
}
