#version 330
layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;

out vec2 fTexCoords;

void main()
{
	gl_Position = mvpMatrix * vPosition;
    fTexCoords = vTexCoords;
}
