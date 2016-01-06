#version 330 core
//Per-Object Motion Blur 

uniform sampler2D uTexInput; // texture we're blurring
uniform sampler2D uTexVelocity; // velocity buffer

in vec2 texture_coordinate;
   
uniform float uVelocityScale; //currentFps / targetFps
 /*
 What's uVelocityScale? It's used to address the following problem: 
 if the framerate is very high, velocity will be very small as the 
 amount of motion in between frames will be low. Correspondingly, if 
 the framerate is very low the motion between frames will be high 
 and velocity will be much larger. This ties the blur size to the 
 framerate, which is technically correct if you equate framrate with 
 shutter speed, however is undesirable for realtime rendering where 
 the framerate can vary. To fix it we need to cancel out the framerate
 */

int  MAX_SAMPLES = 16; //32

layout (location=0) out vec4 result;

void main(void) {
	/*
		vec2 texelSize = 1.0 / vec2(textureSize(uTexInput, 0));
		vec2 screenTexCoords = gl_FragCoord.xy * texelSize;

		vec2 velocity = texture(uTexVelocity, screenTexCoords).rg * 2.0f - 1.0f;
		velocity *= uVelocityScale;

		float speed = length(velocity / texelSize);
		int nSamples = clamp(int(speed), 1, MAX_SAMPLES);
		
		oResult = texture(uTexInput, screenTexCoords);
		for (int i = 1; i < nSamples; ++i) 
		{
			vec2 offset = velocity * (float(i) / float(nSamples - 1) - 0.5);
			oResult += texture(uTexInput, screenTexCoords + offset);
		}
		oResult /= float(nSamples);
	*/
		
		vec2 velocity = texture(uTexVelocity, texture_coordinate).rg * 2.0 - 1.0;
		velocity *= uVelocityScale;
		
		//get the size of on pixel (texel)
		vec2 texelSize = 1.0 / vec2(textureSize(uTexInput, 0));
		//mprove performance by adapting the number of samples according to the velocity
		float speed = length(velocity / texelSize);
		int nSamples = clamp(int(speed), 1, MAX_SAMPLES);
		result = vec4(0.0);
		
		velocity = normalize(velocity) * texelSize;
		float hlim = float(-nSamples) * 0.5 + 0.5;
		//the actual blurring of the current pixel
		vec2 offset;
		for (int i = 0; i < nSamples; ++i) 
		{
			offset = velocity * (hlim + float(i));
			result += texture(uTexInput, texture_coordinate + offset);
		}
		//average the result
		result /= float(nSamples);
  }