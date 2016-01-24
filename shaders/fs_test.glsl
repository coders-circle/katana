#version 330

in vec4 fPosition;

layout (location = 0) out vec4 fColor;

uniform vec4 color;

void main()
{
    fColor = color;
}
