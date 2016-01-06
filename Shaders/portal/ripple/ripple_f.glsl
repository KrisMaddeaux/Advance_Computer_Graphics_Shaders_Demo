#version 330 compatibility 

// 'time' contains seconds since the program was linked.
uniform float time;
uniform float offsetRipple;

in vec2 texture_coordinate;
uniform sampler2D my_color_texture;

void main()
{
	
	float t = clamp(time, 0.0, 1.0);

	vec2 dir = texture_coordinate - vec2(0.5);

	float dist = distance(texture_coordinate, vec2(0.5));
	vec2 offset = dir * (sin(dist * 80.0 - time * 15.0) + 0.5) / 30.0;
	//offset = offsetRipple * offset;

	vec2 texCoord = texture_coordinate + offset;

	vec4 mixin = texture2D(my_color_texture, texCoord).rgba;
	vec4 diffuse = vec4(0.0, 0.5, 0.5, 1.0);

	gl_FragColor =  mixin * t + diffuse * (1.0  - t);
}