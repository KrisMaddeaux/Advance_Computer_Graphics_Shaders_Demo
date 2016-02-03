#version 330 core
#extension GL_EXT_gpu_shader4 : enable

uniform vec4 globalAmbient; //cameraPosition; //, lightColor, lightPosition;
uniform vec4 farDist; //far distance of every split
uniform mat4 lightProjectionMat[4];	//used for shadows

//////////////////////////////////////
struct Light
{
	vec4 position;
	vec4 color;

	//for spot lights
	float spotCutoff;
	float spotExponent;
	vec3 spotDirection; //determines the axis of the cone of light (where the light is pointing
	float linearConstant;
	float quadraticConstant; 
};

const int MAX_LIGHTS = 9; //+1 for directed light
uniform Light gameLights[MAX_LIGHTS]; 
///////////////////////////////////////////

//varying vec2 texture_coordinate;
in vec2 texture_coordinate;
uniform sampler2D my_color_texture;
uniform sampler2D normalMapTexture;

uniform sampler3D jitter; //jitter map

//shadow maps
uniform sampler2DShadow shadowMap1;
uniform sampler2DShadow shadowMap2;
uniform sampler2DShadow shadowMap3;
uniform sampler2DShadow shadowMap4;

uniform int numLights; 

in vec3 P;
in vec3 N;
in vec4 lightP;

in vec4 currentPosition;
in vec4 previousPosition;

uniform float enableLight;

layout (location=0) out vec4 fragColour0; //the color of the scene
layout (location=1) out vec4 fragColour1;	//verlocity buffer							//linear depth of the scene
layout (location=2) out vec4 fragColour2;	//black sceen								//for light rays
//layout (location=2) out vec4 fragColour2; //verlocity buffer of the scene

float lookup(in sampler2DShadow img, in vec4 centerUV, vec2 offSet)
{
	// Values are multiplied by ShadowCoord.w because shadow2DProj does a W division for us.
	vec2 texelSize = 1.0 / vec2(textureSize(img, 0));
	return textureProj(img, centerUV + 
		                            vec4(offSet.x * texelSize.x * centerUV.w, 
		                                offSet.y * texelSize.y * centerUV.w, 
		                                0.0, 
		                                0.0));
}



float ShadowBlur(in sampler2DShadow img, in vec4 centerUV, vec2 pixel, int samples, float width)
{
	float shadow = 0.0;
	float counter = 0.0;
	float x,y;

	//take cheap test samples first
	shadow += lookup(img, centerUV, vec2(-3.0,-3.0));
	shadow += lookup(img, centerUV, vec2(3.0,-3.0));
	shadow += lookup(img, centerUV, vec2(3.0,3.0));
	shadow += lookup(img, centerUV, vec2(-3.0,3.0));

	shadow += lookup(img, centerUV, vec2(-3.0,0.0));
	shadow += lookup(img, centerUV, vec2(0.0,-3.0));
	shadow += lookup(img, centerUV, vec2(3.0,0.0));
	shadow += lookup(img, centerUV, vec2(0.0,3.0));

	shadow /= 8.0;

	if((shadow - 1) * shadow == 0)
	{
		return shadow;
	}

	
	//expensive blurring	
	for (y = -3.0 ; y <=3.0 ; y+=1.0)
	{
		for (x = -3.0 ; x <=3.0 ; x+=1.0)
		{
			shadow += lookup(img, centerUV, vec2(x,y));
			counter++;
		}
	}
			
	shadow /= counter;

	return shadow;
}

float ShadowNoBlur(in sampler2DShadow img, in vec4 centerUV, vec2 pixel)
{
	vec3 UV = centerUV.xyz;
	float totalSample = texture(img, UV);
	return totalSample;
}

vec3 Normal;
//varying in mat3 normalMatrix;
in mat3 normalMatrix;
uniform float useNormalMap; 

void main()
{	
	//set the color to the global ambient color
	vec4 color = globalAmbient;
	float shininess = 10.0;
	float att, dist;
	float shadow_coef = 1.0;
	float shadow_ambient = 1.0;

	vec3 emissive = vec3(0.0, 0.0, 0.0);

	//if(useNormalMap == 1.0f)
	//{
	//	Normal = texture2D(normalMapTexture, texture_coordinate).rgb; 
	//	Normal = normalize(normalMatrix * (Normal * 2.0f - 1.0f));
	//}
	//else
	//{
		Normal = N; 
	//}
	 
	//***PER PIXEL LIGHTS***
	//compute the emissive term
	int max_lights;
	if(numLights <= MAX_LIGHTS)
	{
		max_lights = numLights;
	}
	else
	{
		max_lights = MAX_LIGHTS;
	}

	if(enableLight == 1.0)
	{
		//FOR SHADOWS
		//////////////////////////////////////////
		int index = 3;

		// find the appropriate depth map to look up in based on the depth of this fragment
		if(gl_FragCoord.z < farDist.x)
		{
			index = 0;
		}
		else if(gl_FragCoord.z < farDist.y)
		{
			index = 1;
		}
		else if(gl_FragCoord.z < farDist.z)
		{
			index = 2;
		}

		// transform this fragment's position from view space to scaled light clip space
		// such that the xy coordinates are in [0;1]
		// note there is no need to divide by w for othogonal light sources
		vec4 positionLightNDC = lightProjectionMat[index] * lightP; 

		// serialize for screen space (to make sure values are between 0 and 1 so we can sample texture properly)
		////////////////////////////////////////////
		vec4 positionLightScreen = vec4(positionLightNDC.xyz * 0.5 + 0.5, positionLightNDC.w);
		//vec3 positionLightScreen = positionLightNDC.xyz;

		//sample from shadow map which came from the lights perspective from the first pass
		//vec2 shadowTexcoord;
		vec4 shadowTexcoord;
		shadowTexcoord = positionLightScreen;
		
		float fragmentDepth = positionLightScreen.z;

		// get the stored depth
		float shadowDepth;
		vec2 texelSize;
		if(index == 0)
		{
			////get the size of on pixel (texel)
			texelSize = 1.0 / vec2(textureSize(shadowMap1, 0));
			//shadowDepth = ShadowBlur(shadowMap1, shadowTexcoord, texelSize, 64, 0.003);
			shadowDepth = ShadowNoBlur(shadowMap1, shadowTexcoord, texelSize);

		}
		else if(index == 1)
		{
			//get the size of on pixel (texel)
			texelSize = 1.0 / vec2(textureSize(shadowMap2, 0));
			//shadowDepth = ShadowBlur(shadowMap2, shadowTexcoord, texelSize, 32, 0.0015f);
			shadowDepth = ShadowNoBlur(shadowMap2, shadowTexcoord, texelSize);
		}
		else if(index == 2)
		{
			//get the size of on pixel (texel)
			texelSize = 1.0 / vec2(textureSize(shadowMap3, 0));
			//shadowDepth = ShadowBlur(shadowMap3, shadowTexcoord, texelSize, 16, 0.00075f); 
			shadowDepth = ShadowNoBlur(shadowMap3, shadowTexcoord, texelSize); 
		}
		else
		{
			//get the size of on pixel (texel)
			texelSize = 1.0 / vec2(textureSize(shadowMap4, 0));
			//shadowDepth = ShadowBlur(shadowMap4, shadowTexcoord, texelSize);
			shadowDepth = ShadowNoBlur(shadowMap4, shadowTexcoord, texelSize);
		}

		shadow_coef = shadowDepth;
		shadow_ambient = 0.55;

		///////////////////////////
		//LIGHTS
		for(int index = 0; index < max_lights; index++)
		{
			//bring the light's position into eye coordinates
			//vec3 lightPos = (gl_ModelViewMatrix * vec4(gameLights[index].position.xyz, 1.0f)).xyz;
			vec3 lightPos =  gameLights[index].position.xyz; 

			//compute the diffuse term
			vec3 L = normalize(lightPos - P); //inceident light ray
	
			float diffuseLight = max(dot(Normal,L),0);

			//vec3 diffuse = lightColor.xyz * diffuseLight; 
			vec3 diffuse = gameLights[index].color.xyz * diffuseLight; 

			//compute the specular term
			vec3 V = normalize(-P); //eye or viewer vector (we are in eye corrdinates, so eyePos is 0,0,0)
			vec3 H = normalize(L + V); //halfway vector
	
			//so that there is not specular highlights in shadow areas
			float specularLight;
			if(shadow_coef > 0.9)
			{
				specularLight = pow(max(dot(Normal,H),0),shininess);
			}
			else
			{
				specularLight = 0.0;
			}

			vec3 specular = gameLights[index].color.xyz * specularLight;
	
			//compute the distance to the light source
			dist = length(lightPos - P);  

			//if the light is a directional light
			if(gameLights[index].position.w == 0.0)
			{
				att = 1.0;
				color.xyz += att * (emissive + diffuse + specular);
			}
			//if the light is a spotlight
			else if(gameLights[index].spotCutoff <= 90.0)
			{
				float spotEffect = dot(normalize(gameLights[index].spotDirection), normalize(-L));
				if (spotEffect > cos((3.141592654 / 180.0) * gameLights[index].spotCutoff)) //the cos function only takes radians
				{
					spotEffect = pow(spotEffect, gameLights[index].spotExponent);
					att = spotEffect / (0.5 + 0.0001 * dist + 0.0002 * dist * dist); 
        
					color.xyz += att * (emissive + diffuse  + specular);
				}
			}
			//else the light is a point light
			else
			{
				att = 1.0 / (0.5 + gameLights[index].linearConstant * dist + gameLights[index].quadraticConstant * dist * dist); //linearConstant = 0.0001f and quadraticConstant = 0.0002f

				color.xyz += att * (emissive + diffuse + specular); 
			}
		}
	}
	else
	{
		color = vec4(1.0, 1.0, 1.0, 1.0); 
	}

	//FOG
	/////////////////////////////////
	float fogEnd = 500.0;
	float fogStart = 400.0;
	float fogScale = 1.0 / (fogEnd - fogStart);
	vec4 fogColor = vec4(0.2588, 0.42352, 0.6509, 1.0);
	float fogCoef = clamp(fogScale * (fogEnd + P.z), 0.0, 1.0); 
	/////////////////////////////////
	

	//FINAL RESULTs
	///////////////////////////////
	vec4 colorTex;
	if(enableLight == 1.0)
	{
		colorTex = /*texture2D(my_color_texture, texture_coordinate).rgba*/ vec4(0.7, 0.7, 0.7, 1.0) * color; 
		fragColour0 = mix(fogColor, shadow_ambient * shadow_coef * colorTex + (1.0 - shadow_ambient) * colorTex, fogCoef); 
		//fragColour0.rgb = texture(jitter, vec3(gl_FragCoord.xy * vec2(8.0f, 8.0f), 0.0f)).rgb;
		//fragColour0.rgb = texture(jitter, vec3(texture_coordinate, 0.0f)).rgb;
	}
	//the sky
	else
	{
		//colorTex = texture2D(my_color_texture, texture_coordinate).rgba; 
		fragColour0 = fogColor;
	}
	//fragColour0 = mix(fogColor, shadow_ambient * shadow_coef * colorTex + (1.0f - shadow_ambient) * colorTex, fogCoef); 
	
	/////////////////////////////////////////////////
	//create verlocity buffer
	vec2 a = (currentPosition.xy / currentPosition.w) * 0.5 + 0.5;
	vec2 b = (previousPosition.xy / previousPosition.w) * 0.5 + 0.5;
	fragColour1.xy = (a-b) * 0.5 + 0.5;

	/////////////////////////////////////////////////
	//for light rays
	fragColour2 = vec4(0.0, 0.0, 0.0, 1.0);
}