#version 330 compatibility 

varying vec2 texture_coordinate;

varying out vec3 P;
varying out vec3 N;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	texture_coordinate = vec2(gl_MultiTexCoord0); 
}