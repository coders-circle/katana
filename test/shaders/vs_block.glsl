#version 330
layout (location = 0) in vec4 vPosition;

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = mvpMatrix * vPosition;
}
