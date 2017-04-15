#pragma once
#include "Include\CBMini\CBMiniFW.h"
#include "ShaderInit.h"
#include "Include\GL\glew.h"
#include "texture.h"
#include <iostream>
#include <list>
#include "objLoader.h"
#include "player.h"
#include "camera1.h"
#include "UIClass.h"
#include "MorphTargeting.h"


//Light data
class Light
{
public:
	Light()
	{
		drawPoint = false;
		spotLight = false;

		spotCutoff = 180.0f;
	}
	Light(Vec4f lightColor, Vec4f lightPosition, bool DrawPoint, bool SpotLight)
	{																			 
		LightColor[0] = lightColor.x;
		LightColor[1] =	lightColor.y;
		LightColor[2] =	lightColor.z;
		LightColor[3] =	lightColor.a;

		LightPosition[0] = lightPosition.x;
		LightPosition[1] = lightPosition.y;
		LightPosition[2] = lightPosition.z;
		LightPosition[3] = lightPosition.a;

		drawPoint = DrawPoint;
		spotLight = SpotLight; 

		spotCutoff = 180.0f; 

		linearConstant = 0.0001f;
		quadraticConstant = 0.0002f; 
	}
	Light(Vec4f lightColor, Vec4f lightPosition, bool DrawPoint, bool SpotLight, float linearAtt, float quadraticAtt)
	{																			 
		LightColor[0] = lightColor.x;
		LightColor[1] =	lightColor.y;
		LightColor[2] =	lightColor.z;
		LightColor[3] =	lightColor.a;

		LightPosition[0] = lightPosition.x;
		LightPosition[1] = lightPosition.y;
		LightPosition[2] = lightPosition.z;
		LightPosition[3] = lightPosition.a;

		drawPoint = DrawPoint;
		spotLight = SpotLight; 

		spotCutoff = 180.0f; 

		linearConstant = linearAtt;
		quadraticConstant = quadraticAtt; 
	}
	Light(Vec4f lightColor, Vec4f lightPosition, bool DrawPoint, bool SpotLight, float spotCutoffAngle,  float linearAtt, float quadraticAtt)
	{
		LightColor[0] = lightColor.x;
		LightColor[1] =	lightColor.y;
		LightColor[2] =	lightColor.z;
		LightColor[3] =	lightColor.a;

		LightPosition[0] = lightPosition.x;
		LightPosition[1] = lightPosition.y;
		LightPosition[2] = lightPosition.z;
		LightPosition[3] = lightPosition.a;

		drawPoint = DrawPoint;
		spotLight = SpotLight; 

		spotCutoff = spotCutoffAngle; 

		linearConstant = linearAtt;
		quadraticConstant = quadraticAtt; 
	}
	~Light()
	{
	}
	GLfloat LightColor[4];
	GLfloat LightPosition[4];
	float spotCutoff; 
	float rank;
	bool drawPoint;	//if true, draws a point at the light's position to visual show where the light is positioned
	bool spotLight; //if the light is a spotlight
	float linearConstant;
	float quadraticConstant; 
};

//a district is made up of models, textures, fog
struct District
{
	std::list <tex*> sectionTexs;		//a list of all of the textures for the particular district
	std::list <tex*> sectionNormalMaps;  //a list of all of the normal maps for the particular district
	std::list <objLoader*> sectionModels;	//a list of all of the models for the particular district; 


	////////////////////////////////////////////////////////

	GLfloat fogColor[4];	//what is the color for the fog?
	GLfloat fogStart;	
	GLfloat fogEnd; 

	//lights
	GLfloat ambientLightColor[4];
	GLfloat directedLightColor[4];
	Vec4f directedLightPosition;
	//Vec4f directedLightScreenPos; 
	vector<Light> lights;	//a list that stores all of the point lights for the particular district
	vector<Light> normalLights; //a list that stores all of the white point lights that bring out the normals of the level
};

//a interior is made up of models and textures
struct Interior
{
	std::list <tex*> sectionTexs;		//a list of all of the textures for the particular interiors
	std::list <tex*> sectionNormalMaps;  //a list of all of the normal maps for the particular interiors
	std::list <objLoader*> sectionModels;	//a list of all of the models for the particular interiors

	//lights
	GLfloat ambientLightColor[4];
	/*GLfloat directedLightColor[4];
	GLfloat directedLightPosition[4];*/
	vector<Light> lights;		//a list that stores all of the point lights for the particular interior
}; 

//a level is made up of districts and interiors
struct GameLevel
{
	District district[100];		//a array of all of the districts for the level, a array of lists
	Interior interior[100];		//a array of all of the interiors for the level, a array of lists
};

//***********************SHOULD NOT TOUCH ANYTHING FROM THIS CLASS*********************************//
//***To create a new level create a new level class and have it inherite publicly from this class***
//abstract base class (polymorphism)
class Level
{
public:
	virtual void loadLevel() = 0;		//loads all the distrcts and interiors of the level

	/*void loadMissions();
	void updateMissions(playerStats player, float dt);
	void drawMissions();*/

	void drawDistrict(int n, cbmini::cbfw::GLSLProgram *ShaderProgram, Shader *shader, camera1 camera, playerStats thePlayer);	//int n is the district number
	void drawInterior(int n, Shader *shader, camera1 camera, playerStats thePlayer);
	
	void updateDistrict(playerStats *thePlayer, camera1 *theCamera, bool &interor, bool &district, int &districtID, int &interiorID, bool &drawE, float dt);
	void updateInterior(playerStats *thplayer, camera1 *theCamera, bool &interor, bool &district, int &districtID, int &interiorID, bool &drawE, float dt);
	
	void deleteLevel();		//deletes all districts and interiors of the level from memory

	GameLevel gameLevel;
	//GameMissions missions; 
	sf::Clock timeSinceDiscovered;

	int numInteriors, numDistricts;		//keeps track of how many interiors and districts there are in the level

	Mat4f prevModelMat; //previous model matrix of buildings;
};

//inherites publicly from calss level
class Level1 : public Level
{
public:
	void loadLevel();
};