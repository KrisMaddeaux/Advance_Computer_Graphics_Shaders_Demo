#version 330 compatibility


out vec3 P;
out vec3 N;

out vec2 texture_coordinate;

void main()
{
	//set the position of the current vertex
	P = (gl_ModelViewMatrix * gl_Vertex).xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	//transform the normal into eye space and normalize the result
	N =  normalize(gl_NormalMatrix * gl_Normal); 

	texture_coordinate = vec2(gl_MultiTexCoord0); 
}