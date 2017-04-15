#pragma once
#include "Include\GL\glew.h"
#include "Include\CBMini\CBMiniFW.h"
#include <iostream>


// initialize a GLSL program with vertex and fragment shader
// returns 0 if fail, 1 if success
static int CreateShaderProgram(cbmini::cbfw::GLSLProgram *program, const char *VertexShader, const char *FragmentShader)
{
	if (program)
	{
		//// the result will be multiplicative so that if anything fails it will be zero
		int result = 1;

		//// load some shaders
		//// ****
		cbmini::cbfw::GLSLShader testVertShader, testFragShader;
		result *= testVertShader.CreateFromFile(cbmini::cbfw::GLSL_VERTEX_SHADER, VertexShader);
		result *= testFragShader.CreateFromFile(cbmini::cbfw::GLSL_FRAGMENT_SHADER, FragmentShader);

		// attach them to the program
		result *= program->AttachShader(&testVertShader);
		result *= program->AttachShader(&testFragShader);

		// link and validate
		result *= program->LinkProgram();
		result *= program->ValidateProgram();

		// done
		return result;
	}
	return 0;
}

// initialize a GLSL program with vertex, fragment, and geometry shader
// returns 0 if fail, 1 if success
static int CreateShaderProgram(cbmini::cbfw::GLSLProgram *program, const char *VertexShader, const char *FragmentShader, const char *GeometryShader)
{
	if (program)
	{
		//// the result will be multiplicative so that if anything fails it will be zero
		int result = 1;

		//// load some shaders
		//// ****
		cbmini::cbfw::GLSLShader testVertShader, testFragShader, testGeomShader;
		result *= testVertShader.CreateFromFile(cbmini::cbfw::GLSL_VERTEX_SHADER, VertexShader);
		result *= testFragShader.CreateFromFile(cbmini::cbfw::GLSL_FRAGMENT_SHADER, FragmentShader);
		result *= testGeomShader.CreateFromFile(cbmini::cbfw::GLSL_GEOMETRY_SHADER, GeometryShader);

		// attach them to the program
		result *= program->AttachShader(&testVertShader);
		result *= program->AttachShader(&testFragShader);
		result *= program->AttachShader(&testGeomShader);

		// link and validate
		result *= program->LinkProgram();
		result *= program->ValidateProgram();

		// done
		return result;
	}
	return 0;
}


//loads all of our shaders in game
//lets us use all of our shader throughout our game easy
class Shader
{
public:
	Shader()
	{
		ShaderProgram = new cbmini::cbfw::GLSLProgram;
		HDR_BP_Shader = new cbmini::cbfw::GLSLProgram;
		HDR_Box_Blur_Shader = new cbmini::cbfw::GLSLProgram;
		HDR_G_Blur_X_Shader = new cbmini::cbfw::GLSLProgram;
		HDR_G_Blur_Y_Shader = new cbmini::cbfw::GLSLProgram;
		HDR_Final_Shader = new cbmini::cbfw::GLSLProgram;
		Particle_Shader = new cbmini::cbfw::GLSLProgram;
		shadowMapShader = new cbmini::cbfw::GLSLProgram;
		motionBlurShader = new cbmini::cbfw::GLSLProgram;
		lightRaysShader = new cbmini::cbfw::GLSLProgram;
		lightRaysCompositeShader = new cbmini::cbfw::GLSLProgram;
		defferedRenderingShader = new cbmini::cbfw::GLSLProgram;
		ssaoShader = new cbmini::cbfw::GLSLProgram;
	}
	~Shader()
	{
	}

	void LoadShaders(GLenum err)
	{
		//make sure GLEW initialized properly and load shaders
		if(GLEW_OK == err)
		{
			if(!CreateShaderProgram(ShaderProgram, "Shaders/passthru_v.glsl",  "Shaders/passthru_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 2" << std::endl;
			}
			if(!CreateShaderProgram(HDR_BP_Shader, "Shaders/HDR/HDR_BP_v.glsl",  "Shaders/HDR/HDR_BP_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 5" << std::endl;
			}

			if(!CreateShaderProgram(HDR_Box_Blur_Shader, "Shaders/HDR/HDR_Box_Blur_v.glsl",  "Shaders/HDR/HDR_Box_Blur_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 6" << std::endl;
			}

			if(!CreateShaderProgram(HDR_G_Blur_X_Shader, "Shaders/HDR/HDR_G_Blur_X_v.glsl",  "Shaders/HDR/HDR_G_Blur_X_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 7" << std::endl;
			}

			if(!CreateShaderProgram(HDR_G_Blur_Y_Shader, "Shaders/HDR/HDR_G_Blur_Y_v.glsl",  "Shaders/HDR/HDR_G_Blur_Y_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 8" << std::endl;
			}

			if(!CreateShaderProgram(HDR_Final_Shader, "Shaders/HDR/HDR_Final_v.glsl",  "Shaders/HDR/HDR_Final_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 9" << std::endl;
			}

			if(!CreateShaderProgram(Particle_Shader, "Shaders/particles/passThruPt_v.glsl",  "Shaders/particles/applyTexture_f.glsl", "Shaders/particles/pt2quad_g.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 11" << std::endl;
			}

			if(!CreateShaderProgram(shadowMapShader, "Shaders/shadowMap/shadowMap_v.glsl", "Shaders/shadowMap/shadowMap_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 13" << std::endl;
			}

			if(!CreateShaderProgram(motionBlurShader, "Shaders/motionBlur/motionBlur_v.glsl", "Shaders/motionBlur/motionBlur_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 14" << std::endl;
			}

			if(!CreateShaderProgram(lightRaysShader, "Shaders/lightRays/lightRays_v.glsl", "Shaders/lightRays/lightRays_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 15" << std::endl;
			}

			if(!CreateShaderProgram(lightRaysCompositeShader, "Shaders/lightRays/lightRaysComposite_v.glsl", "Shaders/lightRays/lightRaysComposite_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 16" << std::endl;
			}

			if(!CreateShaderProgram(defferedRenderingShader, "Shaders/defferedRendering/dr_v.glsl", "Shaders/defferedRendering/dr_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 17" << std::endl;
			}

			if(!CreateShaderProgram(ssaoShader, "Shaders/ssao/ssao_v.glsl", "Shaders/ssao/ssao_f.glsl"))
			{
				std::cout << "ERROR, Could not load shader(s) 18" << std::endl;
			}
		}
		else
		{
			std::cout << "ERROR, Could not initialize GLEW" << std::endl;
		}
	}

	cbmini::cbfw::GLSLProgram *ShaderProgram;
	cbmini::cbfw::GLSLProgram *HDR_BP_Shader;
	cbmini::cbfw::GLSLProgram *HDR_Final_Shader;
	cbmini::cbfw::GLSLProgram *HDR_Box_Blur_Shader;
	cbmini::cbfw::GLSLProgram *HDR_G_Blur_X_Shader;
	cbmini::cbfw::GLSLProgram *HDR_G_Blur_Y_Shader;
	cbmini::cbfw::GLSLProgram *Particle_Shader;
	cbmini::cbfw::GLSLProgram *shadowMapShader;
	cbmini::cbfw::GLSLProgram *motionBlurShader;
	cbmini::cbfw::GLSLProgram *lightRaysShader;
	cbmini::cbfw::GLSLProgram *lightRaysCompositeShader;
	cbmini::cbfw::GLSLProgram *defferedRenderingShader;
	cbmini::cbfw::GLSLProgram *ssaoShader;
};

