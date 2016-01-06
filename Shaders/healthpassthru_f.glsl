#version 330 compatibility 

in vec3 P;
in vec3 N;
uniform float health;
in vec2 texture_coordinate;
uniform sampler2D my_color_texture;

void main()
{
	float H = health /100.0;
	//vec4 color = vec4(1,H,H, (1-H)*0.5);
	 
	vec4 texColor = texture2D(my_color_texture, texture_coordinate).rgba;
	//if(texColor.r > 0.8 && texColor.g > 0.8 && texColor.b > 0.8);
	//{
	//	texColor.rgb == vec3(0,0,0);
	//}
	////texColor.r = 1-H;
	//texColor.a = 0.5;
	//if(texColor.r > 0.8 && texColor.g > 0.8 && texColor.b > 0.8)
	//{
	//	texColor.rgba = vec4(0,0,0,0);
	//}
	//else
	//{
	//	texColor.a = (1-H);
	//}
	texColor.a *= (1-H);
	gl_FragColor =  texColor;
}