#include "Level.h"


//////////////////////////////////////////////////////////////////////////////////////////
//*********************LEVEL 1**********************************************************//
//loads all of the needed stuff for level 1
//This is where all the scripting for level 1 goes. This includes all of the  districts, and interiors for that particular level
void Level1::loadLevel()
{

///////////////////////////////////////////////////////////////////////////
//***********FOR District ONE****************************//
	//for the level's model
	const int numLevel1Models = 31; 
	objLoader *d1_tempM[numLevel1Models];

	for(int i = 0; i < numLevel1Models; i++){
		d1_tempM[i] = new objLoader(); 
	}
	
	//load the level's obj model and texture

	//ground
	d1_tempM[0]->LoadOBJ("Models/Levels/Level1/District1/Red_Light_Ground.obj", 8);

	d1_tempM[1]->LoadOBJ("Models/Levels/Level1/District1/Red_Light_Ground1.obj", 8);

	d1_tempM[2]->LoadOBJ("Models/Levels/Level1/District1/Red_Light_Ground2.obj", 8);

	d1_tempM[3]->LoadOBJ("Models/Levels/Level1/District1/Red_Light_Ground3.obj", 8);

	//fountain base
	d1_tempM[4]->LoadOBJ("Models/Levels/Level1/District1/FountainBase.obj", 456);

	//fountain water
	d1_tempM[5]->LoadOBJ("Models/Levels/Level1/District1/FountainWater.obj", 450);

	//foot bridge
	d1_tempM[6]->LoadOBJ("Models/Levels/Level1/District1/Foot_Bridge.obj", 8);

	//light fixtures
	d1_tempM[7]->LoadOBJ("Models/Levels/Level1/District1/Light_Fixtures.obj", 1184);

	//mission buildings
	//apartments
	d1_tempM[8]->LoadOBJ("Models/Levels/Level1/District1/Apartments.obj", 155);

	//bar
	d1_tempM[9]->LoadOBJ("Models/Levels/Level1/District1/GrimBar.obj", 258);

	//club
	d1_tempM[10]->LoadOBJ("Models/Levels/Level1/District1/DragonClub.obj", 108);

	//type 1 buildings
	d1_tempM[11]->LoadOBJ("Models/Levels/Level1/District1/Building1_T1.obj", 38);

	d1_tempM[12]->LoadOBJ("Models/Levels/Level1/District1/Building3_T1.obj", 22);

	d1_tempM[13]->LoadOBJ("Models/Levels/Level1/District1/Building10_T1.obj", 38);

	d1_tempM[14]->LoadOBJ("Models/Levels/Level1/District1/Building34_T1.obj", 44);

	d1_tempM[15]->LoadOBJ("Models/Levels/Level1/District1/Building6_T1.obj", 18);

	d1_tempM[16]->LoadOBJ("Models/Levels/Level1/District1/Building18_T1.obj", 34);

	d1_tempM[17]->LoadOBJ("Models/Levels/Level1/District1/Building21_T1.obj", 12);

	//type 2 buildings
	d1_tempM[18]->LoadOBJ("Models/Levels/Level1/District1/Building14_T2.obj", 44);

	d1_tempM[19]->LoadOBJ("Models/Levels/Level1/District1/Building31_T2.obj", 54);

	d1_tempM[20]->LoadOBJ("Models/Levels/Level1/District1/Building4_T2.obj", 26);

	d1_tempM[21]->LoadOBJ("Models/Levels/Level1/District1/Building23_T2.obj", 14);

	d1_tempM[22]->LoadOBJ("Models/Levels/Level1/District1/Building32_T2.obj", 24);

	d1_tempM[23]->LoadOBJ("Models/Levels/Level1/District1/Building33_T2.obj", 30);

	d1_tempM[24]->LoadOBJ("Models/Levels/Level1/District1/Building26_T2.obj", 90);

	//type 3 buildings
	d1_tempM[25]->LoadOBJ("Models/Levels/Level1/District1/Building13_T3.obj", 22);

	d1_tempM[26]->LoadOBJ("Models/Levels/Level1/District1/Building30_T3.obj", 36);

	d1_tempM[27]->LoadOBJ("Models/Levels/Level1/District1/Building12_T3.obj", 34);

	d1_tempM[28]->LoadOBJ("Models/Levels/Level1/District1/Building27_T3.obj", 556);

	d1_tempM[29]->LoadOBJ("Models/Levels/Level1/District1/Building22_T3.obj", 18);

	d1_tempM[30]->LoadOBJ("Models/Levels/Level1/District1/Building29_T3.obj", 30);
	

	for(int i = 0; i < numLevel1Models; i++){
		gameLevel.district[0].sectionModels.push_back(d1_tempM[i]);
	}

//*************FOG************
	gameLevel.district[0].fogColor[0] = 0.0f;
	gameLevel.district[0].fogColor[1] = 0.1f;
	gameLevel.district[0].fogColor[2] = 0.2f;
	gameLevel.district[0].fogColor[3] = 1;

	gameLevel.district[0].fogStart = 0.0f;
	gameLevel.district[0].fogEnd = 1000.0f;

//***********LIGHTS*********************
	//ambient light
	//color {0.25, 0.25, 0.25}, also is the intensity of the light, fourth parameter is always one
	gameLevel.district[0].ambientLightColor[0] = 0.4f;
	gameLevel.district[0].ambientLightColor[1] = 0.4f;
	gameLevel.district[0].ambientLightColor[2] = 0.4f;
	gameLevel.district[0].ambientLightColor[3] = 1.0f;

	//directed light
	//color RGBA
	gameLevel.district[0].directedLightColor[0] = 1.0f;
	gameLevel.district[0].directedLightColor[1] = 0.89f;
	gameLevel.district[0].directedLightColor[2] = 0.45f;
	gameLevel.district[0].directedLightColor[3] = 1.0f;

	//Position first 3 variables are XYZ coordinates, the last variable is if it is a directed light (0) or positioned light (1)
	gameLevel.district[0].directedLightPosition = Vec4f(-175.0f, 400.0f, 175.0f, 0.0f); //Vec4f(-175.0f, 50.0f, 175.0f, 0.0f);

//**************************************************************************************//
//**************************************************************************************//
//************************MUST ALWAYS BE UPDATED****************************************//

//the total number of districts and interiors for the level****
	numDistricts = 1;
	numInteriors = 0;
	
}







//***********************************************************************************************************************************************************//
//**********************************DO NOT CHANGE/WRITE ANYTHING IN FUNCTIONS FROM BASE CLASS LEVEL**********************************************************//
///////////////////////if you need to add something to a particular level, add it to the particular level's functions//////////////////////////////////////////
//***********************************************************************************************************************************************************//

//*****This works only if there are the same number of models and textures*****
void Level::drawDistrict(int n, cbmini::cbfw::GLSLProgram *ShaderProgram, Shader *shader, camera1 camera, playerStats thePlayer)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);

	//draws all of the models in the district
	for(int i = 0; i < numDistricts; i++)
	{
		//we have found the right district to render
		if(i == n)
		{	
			/*FOG*/
			//glFogfv (GL_FOG_COLOR, gameLevel.district[i].fogColor);
			//glFogi(GL_FOG_MODE, GL_LINEAR);   //assigns the weighting of the gray color to a linear function // Fog Mode GL_EXP, GL_EXP2, GL_LINEAR
			//glFogf(GL_FOG_START, gameLevel.district[i].fogStart);
			//glFogf(GL_FOG_END, gameLevel.district[i].fogEnd);

			/*LIGHTS*/
			//+ 1 for directed light
			glUniform1i(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "numLights"), gameLevel.district[i].lights.size() + 1);


			//add ambient light (shines everwhere in our sceen by the same amount, so every face get lit by the same amount)
			//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gameLevel.district[i].ambientLightColor);
			glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "globalAmbient"), 1, gameLevel.district[i].ambientLightColor);

			//////add directed light and sets it to light0
			//glLightfv(GL_LIGHT0, GL_DIFFUSE, gameLevel.district[i].directedLightColor);				//sets light intensity
			//glLightfv(GL_LIGHT0, GL_POSITION, gameLevel.district[i].directedLightPosition);			//sets postion of light
			int numLights = gameLevel.district[i].lights.size();

			if(numLights < 8)
			{
				// do nothing
			}
			else
			{
				numLights = 8; //max lights
			}

			Vec4f lightPos = gameLevel.district[i].directedLightPosition;
			lightPos.w = 1.0f;
			Mat4f modelMat = Translate(thePlayer.position - thePlayer.startingPosition);
			//Mat4f modelMat = Identity();
			Mat4f modelViewMat = camera.viewMat * modelMat;
			lightPos = modelViewMat * lightPos;
			//gameLevel.district[i].directedLightScreenPos = lightPos;
			lightPos.a = gameLevel.district[i].directedLightPosition.w;

			//Directed light (From sun)
			glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[0].position"), 1, lightPos.v);
			glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[0].color"), 1, gameLevel.district[i].directedLightColor);

			//for light rays
			//ShaderProgram->Deactivate();
			//shader->lightRaysShader->Activate();

			//lightPos.w = 1.0f;
			//lightPos = camera.projectionMat * lightPos;
			//lightPos.x = lightPos.x / lightPos.w;
			//lightPos.y = lightPos.y / lightPos.w;
			//gameLevel.district[i].directedLightScreenPos = lightPos; 
			//glUniform4fv(glGetUniformLocation(shader->lightRaysShader->GetHandle(), "lightPositionOnScreen"), 1, lightPos.v);

			//shader->lightRaysShader->Deactivate();
			
			//draw box to represent light
			//ShaderProgram->Deactivate();
			//	
			//glDisable(GL_LIGHTING);
			//glPushMatrix();
			//glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			//glTranslatef(gameLevel.district[i].directedLightPosition.x + (thePlayer.position.x - thePlayer.startingPosition.x), 
			//			 gameLevel.district[i].directedLightPosition.y + (thePlayer.position.y - thePlayer.startingPosition.y), 
			//			 gameLevel.district[i].directedLightPosition.z + (thePlayer.position.z - thePlayer.startingPosition.z));
			////glTranslatef(gameLevel.district[i].directedLightPosition[0], 
			////			 gameLevel.district[i].directedLightPosition[1], 
			////			 gameLevel.district[i].directedLightPosition[2]);
			//drawBox(2.0f , 2.0f, 2.0f);
			//glPopMatrix();
			//glEnable(GL_LIGHTING);	
			//	
			//ShaderProgram->Activate();
			

			//render dynamic lights
			for(int k = 0; k < numLights; k++)
			{
				lightPos = Vec4f(gameLevel.district[i].lights[k].LightPosition[0], gameLevel.district[i].lights[k].LightPosition[1], gameLevel.district[i].lights[k].LightPosition[2], 1.0f);
				lightPos = modelViewMat * lightPos;
				lightPos.a = gameLevel.district[i].lights[k].LightPosition[3];

				if(k == 0)
				{
					//glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[0].position"), 1, gameLevel.district[i].lights[k].LightPosition);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[1].position"), 1, lightPos.v);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[1].color"), 1, gameLevel.district[i].lights[k].LightColor);

					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[1].linearConstant"),  gameLevel.district[i].lights[k].linearConstant);
					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[1].quadraticConstant"),  gameLevel.district[i].lights[k].quadraticConstant);
					
					if(gameLevel.district[i].lights[k].spotLight)
					{
						//glLightf(GL_LIGHT0 + k, GL_SPOT_CUTOFF, 45.0);
						GLfloat spot_direction[] = {0.0, -1.0, 0.0};
						//glLightfv(GL_LIGHT0 + k, GL_SPOT_DIRECTION, spot_direction);
						//glLightf(GL_LIGHT0 + k, GL_SPOT_EXPONENT, 2.0);*/
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[1].spotCutoff"),  gameLevel.district[i].lights[k].spotCutoff);
						glUniform3fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[1].spotDirection"), 1, spot_direction);
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[1].spotExponent"), 2.0);
					}
					else
					{
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[1].spotCutoff"), 180.0);
					}
				}
				else if(k == 1)
				{
					//glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[1].position"), 1, gameLevel.district[i].lights[k].LightPosition);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[2].position"), 1, lightPos.v);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[2].color"), 1, gameLevel.district[i].lights[k].LightColor);

					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[2].linearConstant"),  gameLevel.district[i].lights[k].linearConstant);
					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[2].quadraticConstant"),  gameLevel.district[i].lights[k].quadraticConstant);
					
					if(gameLevel.district[i].lights[k].spotLight)
					{
						//glLightf(GL_LIGHT0 + k, GL_SPOT_CUTOFF, 45.0);
						GLfloat spot_direction[] = {0.0, -1.0, 0.0};
						//glLightfv(GL_LIGHT0 + k, GL_SPOT_DIRECTION, spot_direction);
						//glLightf(GL_LIGHT0 + k, GL_SPOT_EXPONENT, 2.0);*/
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[2].spotCutoff"), 45.0);
						glUniform3fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[2].spotDirection"), 1, spot_direction);
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[2].spotExponent"), 2.0);
					}
					else
					{
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[2].spotCutoff"), 180.0);
					}
				}
				else if(k == 2)
				{
					//glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[2].position"), 1, gameLevel.district[i].lights[k].LightPosition);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[3].position"), 1, lightPos.v);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[3].color"), 1, gameLevel.district[i].lights[k].LightColor);

					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[3].linearConstant"),  gameLevel.district[i].lights[k].linearConstant);
					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[3].quadraticConstant"),  gameLevel.district[i].lights[k].quadraticConstant);
					
					if(gameLevel.district[i].lights[k].spotLight)
					{
						//glLightf(GL_LIGHT0 + k, GL_SPOT_CUTOFF, 45.0);
						GLfloat spot_direction[] = {0.0, -1.0, 0.0};
						//glLightfv(GL_LIGHT0 + k, GL_SPOT_DIRECTION, spot_direction);
						//glLightf(GL_LIGHT0 + k, GL_SPOT_EXPONENT, 2.0);*/
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[3].spotCutoff"), 45.0);
						glUniform3fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[3].spotDirection"), 1, spot_direction);
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[3].spotExponent"), 2.0);
					}
					else
					{
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[3].spotCutoff"), 180.0);
					}
				}
				else if(k == 3)
				{
					//glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[3].position"), 1, gameLevel.district[i].lights[k].LightPosition);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[4].position"), 1, lightPos.v);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[4].color"), 1, gameLevel.district[i].lights[k].LightColor);

					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[4].linearConstant"),  gameLevel.district[i].lights[k].linearConstant);
					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[4].quadraticConstant"),  gameLevel.district[i].lights[k].quadraticConstant);
					
					if(gameLevel.district[i].lights[k].spotLight)
					{
						//glLightf(GL_LIGHT0 + k, GL_SPOT_CUTOFF, 45.0);
						GLfloat spot_direction[] = {0.0, -1.0, 0.0};
						//glLightfv(GL_LIGHT0 + k, GL_SPOT_DIRECTION, spot_direction);
						//glLightf(GL_LIGHT0 + k, GL_SPOT_EXPONENT, 2.0);*/
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[4].spotCutoff"), 45.0);
						glUniform3fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[4].spotDirection"), 1, spot_direction);
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[4].spotExponent"), 2.0);
					}
					else
					{
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[4].spotCutoff"), 180.0);
					}

				}
				else if(k == 4)
				{
					//glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[0].position"), 1, gameLevel.district[i].lights[0].LightPosition);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[5].position"), 1, lightPos.v);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[5].color"), 1, gameLevel.district[i].lights[k].LightColor);

					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[5].linearConstant"),  gameLevel.district[i].lights[k].linearConstant);
					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[5].quadraticConstant"),  gameLevel.district[i].lights[k].quadraticConstant);
					
					if(gameLevel.district[i].lights[k].spotLight)
					{
						//glLightf(GL_LIGHT0 + k, GL_SPOT_CUTOFF, 45.0);
						GLfloat spot_direction[] = {0.0, -1.0, 0.0};
						//glLightfv(GL_LIGHT0 + k, GL_SPOT_DIRECTION, spot_direction);
						//glLightf(GL_LIGHT0 + k, GL_SPOT_EXPONENT, 2.0);*/
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[5].spotCutoff"), 45.0);
						glUniform3fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[5].spotDirection"), 1, spot_direction);
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[5].spotExponent"), 2.0);
					}
					else
					{
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[5].spotCutoff"), 180.0);
					}
				}
				else if(k == 5)
				{
					//glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[0].position"), 1, gameLevel.district[i].lights[0].LightPosition);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[6].position"), 1, lightPos.v);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[6].color"), 1, gameLevel.district[i].lights[k].LightColor);

					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[6].linearConstant"),  gameLevel.district[i].lights[k].linearConstant);
					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[6].quadraticConstant"),  gameLevel.district[i].lights[k].quadraticConstant);
					
					if(gameLevel.district[i].lights[k].spotLight)
					{
						//glLightf(GL_LIGHT0 + k, GL_SPOT_CUTOFF, 45.0);
						GLfloat spot_direction[] = {0.0, -1.0, 0.0};
						//glLightfv(GL_LIGHT0 + k, GL_SPOT_DIRECTION, spot_direction);
						//glLightf(GL_LIGHT0 + k, GL_SPOT_EXPONENT, 2.0);*/
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[6].spotCutoff"), 45.0);
						glUniform3fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[6].spotDirection"), 1, spot_direction);
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[6].spotExponent"), 2.0);
					}
					else
					{
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[6].spotCutoff"), 180.0);
					}
				}
				else if(k == 6)
				{
					//glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[0].position"), 1, gameLevel.district[i].lights[0].LightPosition);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[7].position"), 1, lightPos.v);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[7].color"), 1, gameLevel.district[i].lights[k].LightColor);

					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[7].linearConstant"),  gameLevel.district[i].lights[k].linearConstant);
					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[7].quadraticConstant"),  gameLevel.district[i].lights[k].quadraticConstant);
					
					if(gameLevel.district[i].lights[k].spotLight)
					{
						//glLightf(GL_LIGHT0 + k, GL_SPOT_CUTOFF, 45.0);
						GLfloat spot_direction[] = {0.0, -1.0, 0.0};
						//glLightfv(GL_LIGHT0 + k, GL_SPOT_DIRECTION, spot_direction);
						//glLightf(GL_LIGHT0 + k, GL_SPOT_EXPONENT, 2.0);*/
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[7].spotCutoff"), 45.0);
						glUniform3fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[7].spotDirection"), 1, spot_direction);
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[7].spotExponent"), 2.0);
					}
					else
					{
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[7].spotCutoff"), 180.0);
					}
				}
				else if(k == 7)
				{
					//glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[0].position"), 1, gameLevel.district[i].lights[0].LightPosition);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[8].position"), 1, lightPos.v);
					glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[8].color"), 1, gameLevel.district[i].lights[k].LightColor);

					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[8].linearConstant"),  gameLevel.district[i].lights[k].linearConstant);
					glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[8].quadraticConstant"),  gameLevel.district[i].lights[k].quadraticConstant);
					
					if(gameLevel.district[i].lights[k].spotLight)
					{
						//glLightf(GL_LIGHT0 + k, GL_SPOT_CUTOFF, 45.0);
						GLfloat spot_direction[] = {0.0, -1.0, 0.0};
						//glLightfv(GL_LIGHT0 + k, GL_SPOT_DIRECTION, spot_direction);
						//glLightf(GL_LIGHT0 + k, GL_SPOT_EXPONENT, 2.0);*/
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[8].spotCutoff"), 45.0);
						glUniform3fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[8].spotDirection"), 1, spot_direction);
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[8].spotExponent"), 2.0);
					}
					else
					{
						glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "gameLights[8].spotCutoff"), 180.0);
					}
				}
			}


			//draw the level
			modelMat =  makeTransform(Identity(), Scale(3.0f, 3.0f, 3.0f), Vec3f(0.0f, -8.0f,0.0f));
			//modelViewMat = camera.viewMat * modelMat;
			//Mat4f modelViewProjectionMat = camera.projectionMat * modelViewMat; 
			//glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->GetHandle(), "modelViewProjectionMat"), 1, 1, modelViewProjectionMat.m);
			//glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->GetHandle(), "modelViewMat"), 1, 1, modelViewMat.m);
			glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->GetHandle(), "modelMat"), 1, 1, modelMat.m);
			glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->GetHandle(), "prevModelMat"), 1, 1, prevModelMat.m);

			std::list<objLoader*>::iterator k = gameLevel.district[i].sectionModels.begin();

			//glUniform1f(glGetUniformLocation(ShaderProgram->GetHandle(), "useNormalMap"), 1.0f); 

			for(; k != gameLevel.district[i].sectionModels.end(); k++)
			{
				(*k)->drawModel();
			}

			prevModelMat = modelMat;
		}
	}

	glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

//Just in case we need to update something over time
//NPCS WILL BE UPDATED HERE
void Level::updateDistrict(playerStats *thePlayer, camera1 *theCamera, bool &interor, bool &district, int &districtID, int &interiorID, bool &drawE, float dt)
{
	int n = districtID; 

	//cycles through all the districts and finds which one to currently update
	for(int i = 0; i < numDistricts; i++)
	{
		//we have found the right district to update
		if(i == n)
		{	
			//if there are more than 7 lights in the district
			if(gameLevel.district[i].lights.size() > 7)
			{
				//find the distance each light is away from the player
				for(unsigned int k = 0; k < gameLevel.district[i].lights.size(); k++)
				{
					gameLevel.district[i].lights[k].rank = (Vec3f(gameLevel.district[i].lights[k].LightPosition[0], gameLevel.district[i].lights[k].LightPosition[1], gameLevel.district[i].lights[k].LightPosition[2]) - thePlayer->position).magnitude();
				}

				//sort the list from the smalles rank to the largest (bubblesort)
				//*******************SORT*********************************************//
				//bubble sort
				for(unsigned int counter = 0; counter < gameLevel.district[i].lights.size(); counter++)
				{
					unsigned int countEnd = gameLevel.district[i].lights.size() - 1;

					while(countEnd > counter)
					{
						if(gameLevel.district[i].lights[countEnd].rank < gameLevel.district[i].lights[countEnd - 1].rank)
						{
							Light temp;

							temp = gameLevel.district[i].lights[countEnd];

							gameLevel.district[i].lights[countEnd] = gameLevel.district[i].lights[countEnd - 1];
							gameLevel.district[i].lights[countEnd - 1] = temp;

						}
						countEnd--;
					}

				}
			}

			//if there are more than 7 normal light in the district
			if(gameLevel.district[i].normalLights.size() > 7)
			{
				//find the distance each light is away from the player
				for(unsigned int k = 0; k < gameLevel.district[i].normalLights.size(); k++)
				{
					gameLevel.district[i].normalLights[k].rank = (Vec3f(gameLevel.district[i].normalLights[k].LightPosition[0], gameLevel.district[i].normalLights[k].LightPosition[1], gameLevel.district[i].normalLights[k].LightPosition[2]) - thePlayer->position).magnitude();
				}

				//sort the list from the smalles rank to the largest (bubblesort)
				//*******************SORT*********************************************//
				//bubble sort
				for(unsigned int counter = 0; counter < gameLevel.district[i].normalLights.size(); counter++)
				{
					unsigned int countEnd = gameLevel.district[i].normalLights.size() - 1;

					while(countEnd > counter)
					{
						if(gameLevel.district[i].normalLights[countEnd].rank < gameLevel.district[i].normalLights[countEnd - 1].rank)
						{
							Light temp;

							temp = gameLevel.district[i].normalLights[countEnd];

							gameLevel.district[i].normalLights[countEnd] = gameLevel.district[i].normalLights[countEnd - 1];
							gameLevel.district[i].normalLights[countEnd - 1] = temp;

						}
						countEnd--;
					}

				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//NPCS WILL BE UPDATED HERE
void Level::updateInterior(playerStats *thePlayer, camera1 *theCamera, bool &interor, bool &district, int &districtID, int &interiorID, bool &drawE, float dt)
{
	int n = interiorID; 
	//cycles through all the districts and finds which one to currently update
	for(int i = 0; i < numInteriors; i++)
	{
		//we have found the right district to update
		if(i == n)
		{	
			//if there are more than 7 lights in the interior
			if(gameLevel.interior[i].lights.size() > 7)
			{
				//find the distance each light is away from the player
				for(unsigned int k = 0; k < gameLevel.interior[i].lights.size(); k++)
				{
					gameLevel.interior[i].lights[k].rank = (Vec3f(gameLevel.interior[i].lights[k].LightPosition[0], gameLevel.interior[i].lights[k].LightPosition[1], gameLevel.interior[i].lights[k].LightPosition[2]) - thePlayer->position).magnitude();
				}

				//sort the list from the smalles rank to the largest (bubblesort)
				//*******************SORT*********************************************//
				//bubble sort
				for(unsigned int counter = 0; counter < gameLevel.interior[i].lights.size(); counter++)
				{
					unsigned int countEnd = gameLevel.interior[i].lights.size() - 1;

					while(countEnd > counter)
					{
						if(gameLevel.interior[i].lights[countEnd].rank < gameLevel.interior[i].lights[countEnd - 1].rank)
						{
							Light temp;

							temp = gameLevel.interior[i].lights[countEnd];

							gameLevel.interior[i].lights[countEnd] = gameLevel.interior[i].lights[countEnd - 1];
							gameLevel.interior[i].lights[countEnd - 1] = temp;

						}
						countEnd--;
					}

				}
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//void Level::loadMissions()
//{
//	missions.loadGameMissions();
//}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//void Level::updateMissions(playerStats player, float dt)
//{
//	missions.updateGameMissions(player, dt);
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//void Level::drawMissions()
//{
//	missions.drawGameMissions();
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////

//clears the memeory
void Level::deleteLevel()
{
	//deletes all of the models in the district
	for(int i = 0; i < numDistricts; i++)
	{
		//deletes the models and tectures for the particular district
		std::list<objLoader*>::iterator k = gameLevel.district[i].sectionModels.begin();
		std::list<tex*>::iterator j = gameLevel.district[i].sectionTexs.begin();
		for(; k != gameLevel.district[i].sectionModels.end();)
		{
			k = gameLevel.district[i].sectionModels.erase(k);
			j = gameLevel.district[i].sectionTexs.erase(j);
		}
		
	}

	//deletes all of the models in the district
	for(int i = 0; i < numInteriors; i++)
	{
		//deletes the models and tectures for the particular district
		std::list<objLoader*>::iterator k = gameLevel.interior[i].sectionModels.begin();
		std::list<tex*>::iterator j = gameLevel.interior[i].sectionTexs.begin();
		for(; k != gameLevel.interior[i].sectionModels.end();)
		{
			k = gameLevel.interior[i].sectionModels.erase(k);
			j = gameLevel.interior[i].sectionTexs.erase(j);
		}
		
	}
}