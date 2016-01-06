#version 330 core

//varying vec2 texture_coordinate;
out vec2 texture_coordinate;

uniform mat4 projectionMat;
uniform mat4 modelMat;
uniform mat4 viewMat;

uniform mat4 prevModelMat;
uniform mat4 prevViewMat;
uniform mat4 prevProjectionMat; 

uniform mat4 lightViewMat;

//varying out vec3 P;
//varying out vec3 N;
//varying out vec4 lightP;

out vec3 P;
out vec3 N;
out vec4 lightP;


//varying out float depth; //the z value of the current position in clip space

layout(location=0) in vec4 position;
layout(location=2) in vec3 normal; 
layout(location=8) in vec2 texcoord;

//varying out vec4 currentPosition;
//varying out vec4 previousPosition;

//varying out mat3 normalMatrix; 

out vec4 currentPosition;
out vec4 previousPosition;

out mat3 normalMatrix; 

void main()
{
	//set the position of the current vertex
	P = (viewMat * modelMat  * position).xyz;

	gl_Position = currentPosition = projectionMat * viewMat * modelMat * position;
    previousPosition = prevProjectionMat * prevViewMat * prevModelMat * position;

	//transform the normal into eye space and normalize the result
	normalMatrix = transpose(inverse(mat3(viewMat * modelMat )));
	N = normalize(normalMatrix * normal);

	texture_coordinate = texcoord; 

	lightP = lightViewMat * modelMat * position;
	//lightP = viewMat * modelMat  * position; 
}