#version 330 core 

in vertex	//comes directly from geometry shader
{
	vec2 texcoord;
}data;

uniform sampler2D diffuseMap;
uniform float alpha;

uniform float black;

layout (location=0) out vec4 fragColour0; //the color of the scene
//layout (location=1) out vec4 fragColour1;	//verlocity buffer							//linear depth of the scene
layout (location=2) out vec4 fragColour2;	//black sceen								//for light rays

void main()
{
	vec4 diffuse = texture(diffuseMap, data.texcoord) * vec4(1.0, 1.0, 1.0, alpha);
	fragColour0 = diffuse;

	if(black == 0.0)
	{
		fragColour2 = vec4(0.0, 0.0, 0.0, 1.0);
		return;
	}

	fragColour2 = diffuse; 
	
}