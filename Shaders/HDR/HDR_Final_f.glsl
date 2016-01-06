#version 330 compatibility 

in vec2 texture_coordinate;

uniform sampler2D myTextureSampler0;
uniform sampler2D myTextureSampler1;

vec3 add(in sampler2D img0, in sampler2D img1, in vec2 uv)
{
	vec3 colour0 = texture(img0, uv).rgb;
	vec3 colour1 = texture (img1, uv).rgb;
	return  (colour0 + colour1);
}

vec3 multiply(in sampler2D img0, in sampler2D img1, in vec2 uv)
{
	vec3 colour0 = texture(img0, uv).rgb;
	vec3 colour1 = texture (img1, uv).rgb;
	return  (colour0 * colour1);
}

vec3 screen(in sampler2D img0, in sampler2D img1, in vec2 uv)
{
	vec3 colour0 = texture(img0, uv).rgb;
	vec3 colour1 = texture (img1, uv).rgb;

	vec3 product = (1.0 - colour0) * (1.0 - colour1);

	return  (1.0 - product);
}

void main()
{
	gl_FragColor.rgb = (screen(myTextureSampler0, myTextureSampler1, texture_coordinate) + multiply(myTextureSampler0, myTextureSampler1, texture_coordinate));
}