#version 330 compatibility 

out vec2 texture_coordinate;

void main()
{
	//set the position of the current vertex
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	texture_coordinate = vec2(gl_MultiTexCoord0); 
}