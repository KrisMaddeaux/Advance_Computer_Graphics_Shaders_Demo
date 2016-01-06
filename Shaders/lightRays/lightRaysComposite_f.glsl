#version 330 core

in vec2 texture_coordinate;

uniform sampler2D texture0;
uniform sampler2D texture1;

layout (location=0) out vec4 fragColour0; //the color of the scene

void main()
{
	fragColour0 = texture2D(texture0, texture_coordinate) + texture2D(texture1, texture_coordinate);
}
