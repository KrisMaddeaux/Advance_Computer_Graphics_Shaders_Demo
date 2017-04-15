#pragma once
#include "ShaderInit.h"
#include "MathClass.h"
#include "character.h"
#include "camera1.h"
//#include <Xinput.h>


//input by the player to the game
struct playerInput
{
	bool w,a,s,d, Lshift, space, Lmouse, Rmouse, LCtrl, E;
	float Lt, Rt; //right trigger and left trigger, for joystick
};

//the state of the player
struct playerState
{
	bool running, walking, idle, sneaking, jumping, aiming; 
	bool fp, tp;	//first person and third person;
	float theta;	//the theta of the player at a frozen state
	bool prevfp; //if the player was in first person when entering the dialogue 
};

//the players's statistics that the game needs to know
class playerStats : public character
{
public:
	
	playerStats();

	//************TO DO: TOO MANY VARIABLES, PUT SOME IN STRUCTS*************************

	
	Vec3f mousePos;		//the mouse's position
	Vec3f screenSize;	//the size of the screen in pixels, (stored as a 2D vector)
	Vec3f mouseDirX;	//the direction of the mouse for x-axis
	Vec3f mouseDirY;	//the direction of the mouse for y-axis
	bool playerMove;	//if the player can move, true, if not false
	float landHeight;

	bool dialogue; //if player is in dialogue 
	bool updateDialoguePerspective; 

	float timeDelay; 

	bool updatePlayerStateTheta;

	//jumping
	float jumpForce, yAccel, yVelocity, playerMass, runSpeed;

	////player Animations
	//playerAnimations animations; 

	playerInput input;
	playerState state;

	//********************JUMPIING*********************//
	sf::Clock jumpClock;

	//Joystick
	sf::Joystick joyStick;

	sf::Clock bulletClock;

	float ETimer;
	float testTimer;

	///////////////////////
	//for xbox controller
	//XINPUT_STATE controllerState;
	//XINPUT_VIBRATION vibration; 
	float vibrationTimer;
	float firstPersonTimer;

//this is called when the player shoots to see if npc's notice the player or not. 
//takes in a list, and has an if statement at the beginning that compares if the player is hostile or not. if they are, it 
//goes through and sees if any enemies are in range. if they are, maintain hostility. if not, hostile = true
	void loadAnimations();
	void updateAnimations(float dt);
	void drawCharacter(cbmini::cbfw::GLSLProgram *ShaderProgram, camera1 camera, bool shadow);
	void updateCharacter(camera1 camera);
	void playerJumping(camera1 *theCamera);
	//player input
	//key is the buttton that the user presses on the keyboard
	//x and y are the mouse's position on the screen
	void handleKeyFunc(camera1 *theCamera);
};