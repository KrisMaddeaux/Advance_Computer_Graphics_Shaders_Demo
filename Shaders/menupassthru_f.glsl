#version 330 compatibility 

in vec3 P;
in vec3 N;
in vec2 texture_coordinate;
uniform sampler2D my_color_texture;

void main()
{
	vec4 texColour = texture2D(my_color_texture, texture_coordinate).rgba;
	

	gl_FragColor =  texColour;
}