#version 330

in vec4 fPosition;
in vec2 fTexCoords;
in vec3 fNormal;

layout (location = 0) out vec4 fColor;

uniform vec4 diffuseColor;
uniform sampler2D diffuseTexture;

void main()
{
    fColor = diffuseColor * texture(diffuseTexture, fTexCoords);

    vec3 lightDir = normalize(vec3(1.0,1.0,0.0));
    float diffuse = max(dot(normalize(fNormal), lightDir),0.0);
    float intensity = min(1.0, diffuse+0.2);

    fColor = vec4(vec3(intensity), 1.0) * fColor;
}
