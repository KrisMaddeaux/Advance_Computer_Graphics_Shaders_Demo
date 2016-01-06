#version 330 compatibility 

out vec2 texture_coordinate;

//varying out vec3 P;
//varying out vec3 N;

void main()
{
	//set the position of the current vertex
	//P = (gl_ModelViewMatrix * gl_Vertex).xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	//transform the normal into eye space and normalize the result
	//N =  normalize(gl_NormalMatrix * gl_Normal); 

	texture_coordinate = vec2(gl_MultiTexCoord0); 
}