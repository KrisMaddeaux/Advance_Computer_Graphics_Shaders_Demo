#version 330 core

in vec2 texture_coordinate;

const float exposure = 0.025; //0.02f
const float decay	 = 0.99; //0.99f
const float density	 = 1.0;  //1.0f
const float weight   = 1.0;  //1.0f
uniform vec4 lightPositionOnScreen;
uniform sampler2D firstPass;
const int NUM_SAMPLES = 100;

vec4 result; 

layout (location=0) out vec4 fragColour0; //the color of the scene

void main()
{
	// Calculate vector from pixel to light source in screen space.
	// Homogeneous divide
	vec4 lightPosOnScreen = lightPositionOnScreen; 
	lightPosOnScreen /= lightPosOnScreen.w;
	//make sure value is between 0 and 1 range
	lightPosOnScreen = lightPosOnScreen * 0.5 + 0.5; 
	vec2 deltaTextCoord = vec2( texture_coordinate - lightPosOnScreen.xy);		
	vec2 textCoord = texture_coordinate;
		// Divide by number of samples and scale by control factor. 
	deltaTextCoord *= 1.0 /  float(NUM_SAMPLES) * density;
	//Store initial sample
	result = texture2D(firstPass, textCoord);
	// Set up illumination decay factor. 
	float illuminationDecay = 1.0;
	
	vec4 sampleTex;
	// Evaluate for NUM_SAMPLES iterations. 
	for(int i=0; i < NUM_SAMPLES ; i++)
	{
		// Step sample location along ray.
		textCoord -= deltaTextCoord;
			// Retrieve sample at new location.  
		sampleTex = texture2D(firstPass, textCoord);
			// Apply sample attenuation scale/decay factors. 
		sampleTex *= illuminationDecay * weight;
			// Accumulate combined color.
		result += sampleTex;
		// Update exponential decay factor.  
		illuminationDecay *= decay;
	}
	// Output final color with a further scale control factor.  
	result *= exposure;
	fragColour0 = result;
	fragColour0.a = 1.0f;
}
