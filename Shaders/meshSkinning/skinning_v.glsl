/*
	Skinning VS

	GLSL vertex shader that performs vertex skinning.
*/

#version 330 compatibility

#define MAX_BONES 64

out vec2 texture_coordinate;

out vec3 P;
out vec3 N;
out vec4 colorTest; 

//for mesh skinning
//vec 4 because there are a max of 4 weights per vertex
layout (location=14) in vec4 weight;
layout (location=15) in vec4 index; 


uniform mat4 Joints[MAX_BONES];	//our whole skeleton


void skinVertex(in vec4 vertexPos, in vec3 vertexNormal,
				out vec4 newPosition, out vec3 newNormal,
				in vec4 vertexWeight, in vec4 vertexIndex)
{
	vec4 weightedPosition = vec4(0.0);
	vec4 weightedNormal = vec4(0.0);

	vec4 normal = vec4(vertexNormal, 0.0);

	//first influence
	float currentWeight = vertexWeight[0];
	int currentIndex = int(vertexIndex[0]); //int(...) converts variable to int
	mat4 currentJoint = Joints[0];
	//formula
	weightedPosition += currentWeight * (currentJoint * vertexPos);
	weightedNormal += currentWeight * (currentJoint * normal);

	////second influence
	//currentWeight = vertexWeight[1];
	//currentIndex = int(vertexIndex[1]); //int(...) converts variable to int
	//currentJoint = Joints[currentIndex];
	////formula
	//weightedPosition += currentWeight * (currentJoint * vertexPos);
	//weightedNormal += currentWeight * (currentJoint * normal);

	////third influence
	//currentWeight = vertexWeight[2];
	//currentIndex = int(vertexIndex[2]); //int(...) converts variable to int
	//currentJoint = Joints[currentIndex];
	////formula
	//weightedPosition += currentWeight * (currentJoint * vertexPos);
	//weightedNormal += currentWeight * (currentJoint * normal);

	////fourth influence
	//currentWeight = vertexWeight[3];
	//currentIndex = int(vertexIndex[3]); //int(...) converts variable to int
	//currentJoint = Joints[currentIndex];
	////formula
	//weightedPosition += currentWeight * (currentJoint * vertexPos);
	//weightedNormal += currentWeight * (currentJoint * normal);

	newPosition = weightedPosition; 
	newNormal = weightedNormal.xyz;

}

uniform sampler2D my_color_texture;

vec4 theWeights;
//vec4 theIndices;

void main()
{
	vec4 skinPosition = gl_Vertex;
	vec3 skinNormal = gl_Normal;

	////skinning algorithm
	//skinVertex(gl_Vertex, gl_Normal, skinPosition, skinNormal, weight, index);


	if(index.x == 0)
	{
		colorTest = vec4(0.0, weight.x * 1.0, 0.0, 1.0); 
	}
	else if(index.y == 0)
	{
		colorTest = vec4(0.0, weight.y * 1.0, 0.0, 1.0); 
	}
	else if(index.z == 0)
	{
		colorTest = vec4(0.0, weight.z * 1.0, 0.0, 1.0); 
	}
	else if(index.a == 0)
	{
		colorTest = vec4(0.0, weight.a * 1.0, 0.0, 1.0); 
	}
	else
	{
		colorTest = vec4(0.0, 0.0, 0.0, 1.0); 
	}
	
	texture_coordinate = vec2(gl_MultiTexCoord0);

	//colorTest = texture2D(my_color_texture, texture_coordinate).rgba;

	//if(colorTest.r > 0.0f)
	//{
	//	theWeights = vec4(colorTest.r, 0.0 , 0.0, 0.0);
	//}
	//else
	//{
	//	theWeights = vec4(0.001, 0.0, 0.0, 0.0);
	//}

	//skinVertex(gl_Vertex, gl_Normal, skinPosition, skinNormal, theWeights, vec4(0.0));

	gl_Position = gl_ModelViewProjectionMatrix * skinPosition;

	P = (gl_ModelViewMatrix * skinPosition).xyz;
	N = normalize(gl_NormalMatrix * skinNormal);
	
}