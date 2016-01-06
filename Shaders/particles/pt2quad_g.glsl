 #version 330 core

uniform mat4 projectionMat;
uniform mat4 modelViewMat;

 //this shader turns a single point into 4 points to make a quad

 layout (points) in;
 layout (triangle_strip, max_vertices=4) out;

out vertex
{
	vec2 texcoord;
}data;

uniform float size;

void main()
{
	vec4 positionObj = gl_in[0].gl_Position;
	vec4 positionEye = modelViewMat * positionObj; 

	float squareSize = size;

	vec4 offset = vec4(0.0); 

	//create billboard
	offset.x = -squareSize;
	offset.y = -squareSize;
	gl_Position = projectionMat * (positionEye + offset);
	data.texcoord = vec2(0.0);
	EmitVertex();

	offset.x = squareSize;
	gl_Position = projectionMat * (positionEye + offset);
	data.texcoord.x = 1.0; 
	EmitVertex();

	offset.x = -squareSize;
	offset.y = +squareSize;
	gl_Position = projectionMat * (positionEye + offset);
	data.texcoord = vec2(0.0, 1.0); 
	EmitVertex();

	offset.x = squareSize;
	gl_Position = projectionMat * (positionEye + offset);
	data.texcoord.x = 1.0; 
	EmitVertex();

	EndPrimitive();
}