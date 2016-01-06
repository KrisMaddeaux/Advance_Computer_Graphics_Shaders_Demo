#version 330 compatibility 

vec2 pixelSize; 

in vec2 texture_coordinate;
uniform sampler2D my_color_texture;

vec3 boxBlur(in sampler2D img, in vec2 centerUV, vec2 pixel)
{
	//return texture(img, centerUV).rgb; 

	vec2 offsetUV; 

//*****apply a box filter*****
	
//current pixel
	vec4 totalSample = 1.0 * texture(img, centerUV);

//neighbors
	//bottom left
	offsetUV = -pixel; 
	totalSample += 1.0 * texture(img, centerUV + offsetUV); 

	//bottom
	offsetUV.x = 0.0; 
	totalSample += 1.0 * texture(img, centerUV + offsetUV);

	//bottom right
	offsetUV.x = +pixel.x;
	totalSample += 1.0 * texture(img, centerUV + offsetUV);
	
	//right
	offsetUV.y = 0.0;		
	totalSample += 1.0 * texture(img, centerUV + offsetUV);
		
	//left
	offsetUV.x = -pixel.x;		
	totalSample += 1.0 * texture(img, centerUV + offsetUV);
	
	//top left
	offsetUV.y = +pixel.y;				
	totalSample += 1.0 * texture(img, centerUV + offsetUV);
		
	//top
	offsetUV.x = 0.0;				
	totalSample += 1.0 * texture(img, centerUV + offsetUV);
				
	//top right
	offsetUV.x = +pixel.x;			
	totalSample += 1.0 * texture(img, centerUV + offsetUV);

	//average
	totalSample /= 9.0; 

	return totalSample.rgb; 
}

void main()
{
	pixelSize = 1.0 / vec2(textureSize(my_color_texture, 0));
	gl_FragColor.rgb = boxBlur(my_color_texture, texture_coordinate, pixelSize);
}