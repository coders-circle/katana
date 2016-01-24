#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;

out vec4 fPosition;
out vec3 fNormal;
out vec2 fTexCoord;

void main()
{
	gl_Position = mvpMatrix * vPosition;
	fNormal = normalize(mat3(modelMatrix) * vNormal);
	fTexCoord = vTexCoord;
	fPosition = modelMatrix * vPosition;
}
