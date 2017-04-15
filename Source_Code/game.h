#pragma once
#include "Include\CBMini\CBMiniFW.h"
#include "ShaderInit.h" 
#include "Include\GL\glew.h"
#include "texture.h"
#include "player.h"
#include "objLoader.h"
#include "camera1.h"
#include <math.h>
#include <vector>
#include <list>
#include "Level.h"
#include "character.h"
#include "MorphTargeting.h"
#include "UIClass.h"
#include "SkyBox.h"

//handles information on the mouse
//used for camera movement
//in screen coordinates
struct mouseInput
{
	sf::Vector2i current;	//current mouse position
};

//handles information on the current state of the game
struct GameState
{
	unsigned int windowWidth, windowHeight; 
	//keeps track if the current section being rendered is a interior or district
	bool interior;	//if inside
	bool district;	//if outside
	int interiorID;	//the ID of the current interior
	int districtID;	//the ID of the current district
	int levelID;	//the ID of the current level

	float currentTime; //current time in seconds

	int frameRate;
};

//games current state e.g. paused, menu, running
enum states
{
	menu,
	running,
	paused
};

struct obj_BoundingSphere
{
	Vec3f center;
	float radius;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

class game
{
public:
	game();	//constructor
	~game(); //destructor
	void handleInput(); //handles input for both keyboard and controller
	void initRenderFunc();	//renders the 3D scene
	void initWindowFunc();	//handles the window
	void drawFunc(sf::RenderWindow *window);		//draws the 3D scene
	void cleanUp();			//cleans up once the user presses the esc key or quites
	void updateFunc();	//updates the scene
	void mouseMotion(sf::Vector2i current, sf::RenderWindow *window);
	void keyboardUp(unsigned char key, int x, int y);		//when a button is realeased
	void runGame();
	void updateMenu();
	void RenderHDRScene(sf::RenderWindow *window);
	
	Shader *shader; 

	sf::RenderWindow *window;

	//for useing the mouse to look around the scene
	void mouseDirectionCheckX(float x, float y);	//for x axis
	void mouseDirectionCheckY(float x, float y);	//for y axis
	Vec3f prevX;	//stores the previous mouse direction for x axis
	Vec3f prevY;	//stores the previous mouse direction for y axis

	sf::Vector2i dirVec(sf::Vector2i v, sf::Vector2i other);
	sf::Vector2f norm(sf::Vector2i temp);

	//sf::Joystick joyStick;
	playerStats player;	//gain access the playerStats data members.
	mouseInput mouse; 
	GameState gameState;

	int runningState;
	int menuState;

	camera1 theCamera;

//**********UI STUFF********************//
	UI gameScreen;

//**********LEVELS************************//
	Level *levels[2];	//an array of levels, 2 is the number of levels

//***********PARTICLES*********************//
	
// clock for time tracking and constant updates
	sf::Clock theClock;
	sf::Time frameTime;

//////////////////////////////////////////////////////////////////////
	sf::View myGUIView;

	//Sky Box
	SkyBox *skyBox;

//////////////////////////////////////////////////////////////////////
	//HDR Rending
	cbmini::cbfw::FrameBuffer *FBO;
	cbmini::cbfw::FrameBuffer *FBO_BP;	//Bright Pass Filter
	cbmini::cbfw::FrameBuffer *FBO_BOX_BLUR; //Box Blurring
	cbmini::cbfw::FrameBuffer *FBO_G_BLUR_X; //Gaussian Bluring X
	cbmini::cbfw::FrameBuffer *FBO_G_BLUR_Y; //Gaussian Bluring Y
	cbmini::cbfw::FrameBuffer *FBO_FINAL; //Final with HDR rendering applied
	cbmini::cbfw::FrameBuffer *FBO_MOTION_BLUR;
	cbmini::cbfw::FrameBuffer *FBO_LIGHT_RAYS;
	cbmini::cbfw::FrameBuffer *FBO_LIGHT_RAYS_COMPOSITE;
	cbmini::cbfw::FrameBuffer *FBO_DEFFERED_REDNERING;
	cbmini::cbfw::FrameBuffer *FBO_SSAO;
	float shrinkFactor; 

	//shadows
	cbmini::cbfw::FrameBuffer *FBO_SHADOW[4]; //creates shadow map for each slice of the view frustrum
	cbmini::cbfw::FrameBuffer *FBO_SHADOW_BLURX[4]; 
	cbmini::cbfw::FrameBuffer *FBO_SHADOW_BLURY[4]; 

	int depth_size;

	//HUD
	cbmini::cbfw::FrameBuffer *HUD;
	bool displayCursor;

	//for SSAO
	tex rand_normals; 

///////////////////////////////////////////////////////////////
	//Missions
	//GameMissions missions; 

////////////////////////
	//float ETimer;
	bool drawE;


	///to calculate framerate
	int frames;
	float nextUpdate;

	//sun
	tex Sun; 

};
