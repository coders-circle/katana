#version 330

in vec4 fPosition;
in vec2 fTexCoords;

layout (location = 0) out vec4 fColor;

uniform vec4 color;
uniform sampler2D diffuseTexture;

void main()
{
    fColor = color * texture(diffuseTexture, fTexCoords);
}
