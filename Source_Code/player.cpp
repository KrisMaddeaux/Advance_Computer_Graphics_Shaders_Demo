#pragma once
#include "player.h"

playerStats::playerStats()
{
	//animations.test = Skeleton();

	species = 10;

	health = 100;

	alive = true;
	isHostile = false;
	isAttackable = true;
		
	theta = 0.0f;
	//startingPosition = Vec3f(520.f * 0.6  * 3.0, 0.0, 290.f * 0.6 * 3.0);
	//startingPosition = Vec3f(85.f * 0.6  * 3.0, 0.0f, 260.f * 0.6 * 3.0);
	startingPosition = Vec3f(389, 0, 428);

	position = startingPosition;
	tValue = 0.f;
		
	speed = 1.0f;
		
	ZaxisPos = Vec3f(0.0f, 0.0f, 1.0f);		//front of the character
	ZaxisNeg = Vec3f(0.0f, 0.0f, -1.0f);		//back of the character

	XaxisNeg = Vec3f(-1.0f, 0.0f, 0.0f);			//left of the character
	XaxisPos = Vec3f(1.0f, 0.0f, 0.0f);			//right of the character
		
	state.jumping = false;
	playerMove = true;
	state.sneaking = false;

	input.LCtrl = false;
		
	mousePos.z = 0.0f;
	landHeight = position.y;

	updatePlayerStateTheta = false;

	//jumping
	runSpeed = 1.0f;
	jumpForce = 0.0f;
	yAccel = 0.0f;
	yVelocity = 0.0f;
	playerMass = 50.0f;

	//create the parent/child node
	//node = pcNode();

	relaxingPeriod = 1.0f; //amount of time a character takes to relax after its last shot
	recentlyAttacked = relaxingPeriod + 1; //amount of time its been since an npc attacked
		

	timeDelay = 0.0f; 

	state.prevfp = false;

	dialogue = false;
	updateDialoguePerspective = false;

	//collisionObject(8,this->position, this->speed, true);

	ETimer = 0.0f;
	firstPersonTimer = 0.0f;
	vibrationTimer = 10.0f;
}

///////////////////////////////////////////////////////////////////////////////
void playerStats::loadAnimations()
{

	theModel = new objLoader();
	theTexture1 = new tex();

	//theTexture1->loadTex("Images/Characters/MainCharacterTextureV3.png");
	loadCharacter(theTexture1, "Models/Characters/Player/mainCharacter.obj", 11644);
	//theModel->LoadOBJForMorphTargeting("Models/Characters/Player/mainCharacter.obj", 11644);
		

	//for the player's animation

	////idle
	animations.Idle.addKeyFrame("Animations/Player/Idle/keyFrame01.obj", 11644);
	animations.Idle.addKeyFrame("Animations/Player/Idle/keyFrame02.obj", 11644);
	animations.Idle.addKeyFrame("Animations/Player/Idle/keyFrame03.obj", 11644);
	animations.Idle.addKeyFrame("Animations/Player/Idle/keyFrame04.obj", 11644);
	animations.Idle.addKeyFrame("Animations/Player/Idle/keyFrame05.obj", 11644);
	animations.Idle.addKeyFrame("Animations/Player/Idle/keyFrame06.obj", 11644);
	animations.Idle.addKeyFrame("Animations/Player/Idle/keyFrame07.obj", 11644);

	//animations.Jumping.addKeyFrame("Animations/Player/jumping/keyFrame01.obj", 12297);
	animations.Jumping.addKeyFrame("Animations/Player/jumping/keyFrame02.obj", 11644);
	animations.Jumping.addKeyFrame("Animations/Player/jumping/keyFrame03.obj", 11644);
	animations.Jumping.addKeyFrame("Animations/Player/jumping/keyFrame04.obj", 11644);
	animations.Jumping.addKeyFrame("Animations/Player/jumping/keyFrame05.obj", 11644);
	animations.Jumping.addKeyFrame("Animations/Player/jumping/keyFrame06.obj", 11644);
	animations.Jumping.addKeyFrame("Animations/Player/jumping/keyFrame07.obj", 11644);

	animations.StrafeLeft.addKeyFrame("Animations/Player/strafeLeft/keyFrame01.obj", 11644);
	animations.StrafeLeft.addKeyFrame("Animations/Player/strafeLeft/keyFrame02.obj", 11644);
	animations.StrafeLeft.addKeyFrame("Animations/Player/strafeLeft/keyFrame03.obj", 11644);
	animations.StrafeLeft.addKeyFrame("Animations/Player/strafeLeft/keyFrame04.obj", 11644);
	animations.StrafeLeft.addKeyFrame("Animations/Player/strafeLeft/keyFrame05.obj", 11644);
	animations.StrafeLeft.addKeyFrame("Animations/Player/strafeLeft/keyFrame06.obj", 11644);

	animations.StrafeRight.addKeyFrame("Animations/Player/strafeRight/keyFrame01.obj", 11644);
	animations.StrafeRight.addKeyFrame("Animations/Player/strafeRight/keyFrame02.obj", 11644);
	animations.StrafeRight.addKeyFrame("Animations/Player/strafeRight/keyFrame03.obj", 11644);
	animations.StrafeRight.addKeyFrame("Animations/Player/strafeRight/keyFrame04.obj", 11644);
	animations.StrafeRight.addKeyFrame("Animations/Player/strafeRight/keyFrame05.obj", 11644);
	animations.StrafeRight.addKeyFrame("Animations/Player/strafeRight/keyFrame06.obj", 11644);

	animations.Walking.addKeyFrame("Animations/Player/forwardWalking/keyFrame01.obj", 11644);
	animations.Walking.addKeyFrame("Animations/Player/forwardWalking/keyFrame02.obj", 11644);
	animations.Walking.addKeyFrame("Animations/Player/forwardWalking/keyFrame03.obj", 11644);
	animations.Walking.addKeyFrame("Animations/Player/forwardWalking/keyFrame04.obj", 11644);
	animations.Walking.addKeyFrame("Animations/Player/forwardWalking/keyFrame05.obj", 11644);
	animations.Walking.addKeyFrame("Animations/Player/forwardWalking/keyFrame06.obj", 11644);
	animations.Walking.addKeyFrame("Animations/Player/forwardWalking/keyFrame07.obj", 11644);
	animations.Walking.addKeyFrame("Animations/Player/forwardWalking/keyFrame08.obj", 11644);

	animations.WalkingBackward.addKeyFrame("Animations/Player/forwardWalking/keyFrame08.obj", 11644);
	animations.WalkingBackward.addKeyFrame("Animations/Player/forwardWalking/keyFrame07.obj", 11644);
	animations.WalkingBackward.addKeyFrame("Animations/Player/forwardWalking/keyFrame06.obj", 11644);
	animations.WalkingBackward.addKeyFrame("Animations/Player/forwardWalking/keyFrame05.obj", 11644);
	animations.WalkingBackward.addKeyFrame("Animations/Player/forwardWalking/keyFrame04.obj", 11644);
	animations.WalkingBackward.addKeyFrame("Animations/Player/forwardWalking/keyFrame03.obj", 11644);
	animations.WalkingBackward.addKeyFrame("Animations/Player/forwardWalking/keyFrame02.obj", 11644);
	animations.WalkingBackward.addKeyFrame("Animations/Player/forwardWalking/keyFrame01.obj", 11644);

	
	animations.Shooting.addKeyFrame("Animations/Player/shooting/v2playershoot1.obj", 11644);
	animations.Shooting.addKeyFrame("Animations/Player/shooting/v2playershoot2.obj", 11644);
	animations.Shooting.addKeyFrame("Animations/Player/shooting/v2playershoot3.obj", 11644);
	animations.Shooting.addKeyFrame("Animations/Player/shooting/v2playershoot4.obj", 11644);

	animations.Death.addKeyFrame("Animations/Player/death/dying1.obj", 11644);
	animations.Death.addKeyFrame("Animations/Player/death/dying2.obj", 11644);
	animations.Death.addKeyFrame("Animations/Player/death/dying3.obj", 11644);
	animations.Death.addKeyFrame("Animations/Player/death/dying4.obj", 11644);
	animations.Death.addKeyFrame("Animations/Player/death/dying5.obj", 11644);
	animations.Death.loop = false;

	/*
	animations.StillFrame.addKeyFrame("Animations/Player/stillFrame/keyFrame01.obj", 2862);

	animations.Aiming.addKeyFrame("Animations/Player/aiming/keyFrame01.obj", 2862);
	animations.Aiming.addKeyFrame("Animations/Player/aiming/keyFrame02.obj", 2862);*/

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void playerStats::updateAnimations(float dt)
{

	//////************player animation*******************//
		
	//death
	if(!alive)
	{
		animations.Death.animate(5, theModel, dt);
	}
	//idle
	else if(state.idle || state.fp || dialogue || state.aiming)
	{
		animations.Idle.animate(7, theModel, dt);
	}
		///////if jumping////////
	else if(input.space && !state.fp)
	{
		animations.Jumping.animate(6, theModel, dt);
	}
	//  ///////if shooting////////
	else if(input.Lmouse && !state.fp && !dialogue)
	{
		animations.Shooting.animate(4, theModel, dt);
	}
	//  ///////if strafing right////////
	else if(input.d && !state.fp && !dialogue)
	{
		animations.StrafeRight.animate(6, theModel, dt);
	}
	///////if strafing left////////
	else if(input.a && !state.fp && !dialogue)
	{
		animations.StrafeLeft.animate(6, theModel, dt);
	}
	////	 ///////if walking backwards////////
	else if(input.s && !state.fp && !dialogue)
	{
		animations.WalkingBackward.animate(8, theModel, dt);
	}
	//if walking forward
	else if(input.w && !state.fp && !dialogue)
	{
		animations.Walking.animate(8, theModel, dt);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
void playerStats::drawCharacter(cbmini::cbfw::GLSLProgram *ShaderProgram, camera1 camera, bool shadow)
{
	updateCharacter(camera); 
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->GetHandle(), "modelMat"), 1, 1, modelMat.m);
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->GetHandle(), "prevModelMat"), 1, 1, prevModelMat.m);
	//glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->GetHandle(), "modelViewProjectionMat"), 1, 1, modelViewProjectionMat.m);
	//glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->GetHandle(), "modelViewMat"), 1, 1, modelViewMat.m);
	theTexture1->drawTex(0);
	//if(shadow)
	//{
		theModel->drawModel();
	//}

}
/////////////////////////////////////////////////////////////////////////////////
void playerStats::updateCharacter(camera1 camera)
{
	Mat4f r;
	//handles when the player is idle, camera rotates around player
	//if(((!state.idle && !dialogue) || ((state.fp || playerMove) && (!state.tp)) || state.aiming) && (alive))
	//{
		r = RotateY(-theta);
	//	state.theta = theta;
	//}
	//else
	//{
	//	r = RotateY(state.theta);
	//}
	prevModelMat = modelMat;
	modelMat = makeTransform(r, Scale(1.2f, 1.2f, 1.2f), Vec3f(position.x, position.y - 10.0f, position.z));

	//modelViewMat = camera.viewMat * modelMat;

	//modelViewProjectionMat = camera.projectionMat * modelViewMat; 
}


///////////////////////////////////////////////////////////////////////////////
void playerStats::playerJumping(camera1 *theCamera)
{
	if(state.jumping == true && position.y >= landHeight)
	{
		jumpForce = G;
		state.jumping = false;
		position.y = landHeight;
		yVelocity = 6.f;
		jumpClock.restart();
	}
	else if(position.y <= landHeight)
	{
		jumpForce = 0.0f;
		yAccel = 0.0f;
		yVelocity = 0.0f;
		position.y = landHeight;
		theCamera->currentVector.y = theCamera->savedOffset.y;
		theCamera->playerPointReserved.y = landHeight;
		// player.input.space = false;
	}
	yAccel = jumpForce / playerMass;
	yVelocity += yAccel;
	position += Vec3f(0.0f, yVelocity*jumpClock.getElapsedTime().asSeconds(), 0.0f);
	theCamera->playerPointReserved += Vec3f(0.0f, yVelocity*jumpClock.getElapsedTime().asSeconds(), 0.0f);
	theCamera->currentVector += Vec3f(0.0f, yVelocity*jumpClock.getElapsedTime().asSeconds(), 0.0f);
	theCamera->setPosition();

	if(position.y == 0.0f)
	{
		input.space = false;
	}
}

///////////////////////////////////////////////////////////////////////////////
//player input
//key is the buttton that the user presses on the keyboard
//x and y are the mouse's position on the screen
void playerStats::handleKeyFunc(camera1 *theCamera)
{
//*********IF PLAYER IS IN A DISTRICT (OUTSIDE)******************//
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		input.a = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		input.w = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		input.s = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		input.d = true;
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		input.Lmouse = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		input.Lshift = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if(ETimer > 1.0f)
		{
			input.E = true;
			ETimer = 0.0f;
		}
		else
		{
			input.E = false;
		}
	}

	movementVec = Vec3f(0.f, 0.f, 0.f);
	//A button
	if (input.a == true)
	{
		//update player position
		position += theCamera->RightVector.negate() * Vec3f(runSpeed, 0.0f, runSpeed);

		theCamera->playerPoint = position;
		theCamera->playerPointReserved = position; 
	}

	//D button
	if (input.d == true)
	{
		position += theCamera->RightVector * Vec3f(runSpeed, 0.0f, runSpeed);
			
		//Camera update for running, jumping, and first person
		theCamera->playerPoint = position;
		theCamera->playerPointReserved = position; 
	}

	//W button
	if (input.w == true)
	{
		position += theCamera->ForwardVector * Vec3f(runSpeed, 0.0f, runSpeed);

		//Camera update for running, jumping, and first person
		theCamera->playerPoint = position;
		theCamera->playerPointReserved = position; 
	}

	//S button
	if (input.s == true)
	{
		position += theCamera->ForwardVector.negate() * Vec3f(runSpeed, 0.0f, runSpeed);
		//Camera update for running, jumping, and first person
		theCamera->playerPoint = position;
		theCamera->playerPointReserved = position; 
	}

	//Left shift
	if(input.Lshift == true)
	{
		runSpeed = 2.0f;
		state.running = true;
		state.walking = false;
	}
	else
	{
		runSpeed = 1.0f;
		state.running = false;
		state.walking = true;
	}

	////Ctrl button
	if(state.sneaking)
	{
		runSpeed = 0.5f;
	}

	////checks player's state
	if(input.w || input.a || input.s || input.d || input.Lmouse || input.Lshift ||input.space)
	{
		state.idle = false;
		updatePlayerStateTheta = true;
	}
	else
	{
		state.idle = true;
		if(updatePlayerStateTheta)
		{
			state.theta = theta;
			updatePlayerStateTheta = false;
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && joyStick.getAxisPosition(0, joyStick.X) > -50.0f)
	{
		input.a = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && joyStick.getAxisPosition(0, joyStick.Y) > -50.0f)
	{
		input.w = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S)&& joyStick.getAxisPosition(0, joyStick.Y) < 50.0f)
	{
		input.s = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && joyStick.getAxisPosition(0, joyStick.X) < 50.0f)
	{
		input.d = false;
	}
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && input.Rt < 100)
	{
		input.Lmouse = false;
	}
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		input.Lshift = false;
	}
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !joyStick.isButtonPressed(0,0))
	{
		input.E = false;
	}
}



