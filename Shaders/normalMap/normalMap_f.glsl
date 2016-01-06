#version 330 compatibility 

in vec2 texture_coordinate;
uniform sampler2D myTextureSampler0;
uniform sampler2D myTextureSampler1;

uniform int numLights;

in vec3 P;

void main()
{
	//set the color to the global ambient color
	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
	float shininess = 10.0;
	float att, dist;

	vec3 emissive = vec3(0.0, 0.0, 0.0);

	vec3 N = texture2D(myTextureSampler1, texture_coordinate).rgb; 
	//N = normalize(N * 2.0f - 1.0f); 
	N = normalize(gl_NormalMatrix * (N * 2.0f - 1.0f));

	vec3 diffuseColor = texture2D(myTextureSampler0, texture_coordinate).rgb; 
	 
	//***PER PIXEL LIGHTS***
	//compute the emissive term
	int MAX_LIGHTS;
	if(numLights <= gl_MaxLights)
	{
		MAX_LIGHTS = numLights;
	}
	else
	{
		MAX_LIGHTS = gl_MaxLights;
	}

	for(int index = 0; index < MAX_LIGHTS; index++)
	{
		////compute the diffuse term
		vec3 L = normalize(gl_LightSource[index].position.xyz - P); //inceident light ray
	
		//float diffuseLight = max(0.0, dot(L,N));

		//vec3 diffuse = (gl_LightSource[index].diffuse.xyz * diffuseLight) * 0.1; 
		vec3 diffuse = vec3(0.0, 0.0, 0.0);

		//compute the specular term
		vec3 V = normalize(-P); //eye or viewer vector (we are in eye corrdinates, so eyePos is 0,0,0)
		vec3 H = normalize(L + V); //halfway vector
	
		float specularLight = pow(max(dot(N,H),0.0),shininess);

		vec3 specular = (gl_LightSource[index].diffuse.xyz * specularLight);
		//vec3 specular = vec3(0, 0, 0);
	
		//compute the distance to the light source
		dist = length(gl_LightSource[index].position.xyz - P);  

		//if the light is a directional light
		if(gl_LightSource[index].position.w == 0.0)
		{
			att = 1.0f;
			color.xyz += att * (emissive + specular + diffuse); 
		}
		//if the light is a spotlight
		else if(gl_LightSource[index].spotCutoff <= 90.0)
		{
			//float NdotL = max(dot(N,L),0.0);

			float spotEffect = dot(normalize(gl_LightSource[0].spotDirection), normalize(-L));
			if (spotEffect > gl_LightSource[0].spotCosCutoff) 
			{
				spotEffect = pow(spotEffect, gl_LightSource[0].spotExponent);
				att = spotEffect / (0.5 + 0.0001 * dist + 0.0002 * dist * dist);
        
				color.xyz += att * (emissive + (specular * 0.05) + diffuse);
			}
		}
		//else the light is a point light
		else
		{
			att = 1.0 / (0.5 + 0.0001 * dist + 0.0002 * dist * dist);

			color.xyz += att * (emissive + (specular * 0.1) + diffuse); 
		}
	}

	gl_FragColor.rgb = diffuseColor + color.rgb;
}