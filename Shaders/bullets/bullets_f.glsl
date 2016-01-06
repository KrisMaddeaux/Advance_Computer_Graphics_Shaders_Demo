#version 330 compatibility 

varying vec2 texture_coordinate;
uniform sampler2D my_color_texture;

void main()
{
	gl_FragColor =  texture2D(my_color_texture, texture_coordinate).rgba * vec4(1.0, 1.0, 1.0, 1.0);
}