#version 330 core

uniform mat4 projectionMat;
uniform mat4 modelMat;
uniform mat4 viewMat;

layout(location=0) in vec4 position;

void main()
{
	gl_Position = projectionMat * viewMat * modelMat * position;
}