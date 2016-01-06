#version 330 compatibility 

//uncharted 2 tone mapping Used from: http://frictionalgames.blogspot.ca/2012/09/tech-feature-hdr-lightning.html

in vec2 texture_coordinate;
uniform sampler2D myTextureSampler;

//Exposure is a way to control the intensity of light that gets passed through the camera.
float exposure = 0.5;	

/*
A white point is used to increase the contrast of the image. This is the value that is selected to be the brightest any pixel can be. 
Pixels brighter than the white point will be clamped to 1.0. 
*/
vec3 white_point = vec3(1.0, 1.0, 1.0); 

//This algorithm preserves the saturation of the color in the dark areas and that keeps as much of the contrast as possible.
vec3 Uncharted2Tonemap(vec3 x)
{
	float A = 0.15;
	float B = 0.50;
	float C = 0.10;
	float D = 0.20;
	float E = 0.02;
	float F = 0.30;

	return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

void main()
{
	//BrightPass Filter

	vec4 c = texture2D(myTextureSampler, texture_coordinate).rgba;
	gl_FragColor.rgb = Uncharted2Tonemap(c.rgb * exposure) / white_point;
	gl_FragColor.w = c.w; 
}