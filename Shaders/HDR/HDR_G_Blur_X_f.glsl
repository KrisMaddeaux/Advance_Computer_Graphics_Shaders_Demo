#version 330 compatibility 

vec2 pixelSize;

in vec2 texture_coordinate;
uniform sampler2D my_color_texture;

vec3 Gaussian1DXBlur(in sampler2D img, in vec2 centerUV, vec2 pixel)
{
	//return texture(img, centerUV).rgb; 

	vec2 offsetUV; 

//*****apply a 2D Gaussian filter*****
	
//current pixel
	vec4 totalSample = (0.383) * texture(img, centerUV);

//NEIGHBORS
	//**Row***
		//1st
		offsetUV =  vec2(-3, 0) * pixel; 
		totalSample += (0.006) * texture(img, centerUV + offsetUV); 

		//2nd
		offsetUV.x += pixel.x; 
		totalSample += (0.061)* texture(img, centerUV + offsetUV); 

		//3rd
		offsetUV.x += pixel.x; 
		totalSample += (0.242)* texture(img, centerUV + offsetUV); 

		//4th
		offsetUV.x = 0; 
		//current pixel, already did this

		//5th
		offsetUV.x += pixel.x; 
		totalSample += (0.242) * texture(img, centerUV + offsetUV); 

		//6th
		offsetUV.x += pixel.x; 
		totalSample += (0.061) * texture(img, centerUV + offsetUV); 

		//7th
		offsetUV.x += pixel.x; 
		totalSample += (0.006) * texture(img, centerUV + offsetUV); 

	return totalSample.rgb; 
}

void main()
{
	pixelSize = 1.0 / vec2(textureSize(my_color_texture, 0));
	gl_FragColor.rgb = Gaussian1DXBlur(my_color_texture, texture_coordinate, pixelSize);
}