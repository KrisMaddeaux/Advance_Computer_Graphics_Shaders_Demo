#include "game.h"

//-----------------------------------------------------------------------------

game::game()
{	
	player = playerStats();

	//used to help call the nessary functions to move the camera
	prevX = Vec3f(0.0f, 0.0f, 0.0f);
	prevY = Vec3f(0.0f, 0.0f, 0.0f);

//**********LEVELS********************//
	//level 1 (redlight district)
	levels[0] = new Level1();
//***********************************//
	//PARTICLES//

//************************************//

	//Vec3f l1CameraVector(0.0f, 10.f, -40.f);
	Vec3f l1CameraVector(0.0f, 0.f, -5.5f);
	theCamera.setStartingVector(l1CameraVector);	
	theCamera.setSavedOffset(l1CameraVector);
	theCamera.setCurrentVector(theCamera.getStartingVector());
	
	theCamera.playerPoint = player.position;
	theCamera.playerPointReserved = player.position;
	
	theCamera.setPosition(/*player.position*/);

	player.state.fp = false;
	player.state.tp = true;
	player.state.aiming = false;

	//gameState.windowWidth = 1080;
	//gameState.windowHeight = 720;
	gameState.windowWidth = 1920;
	gameState.windowHeight = 1080;
	gameState.district = true;
	gameState.interior = false;

	gameState.districtID = 0;
	gameState.interiorID = 0;
	gameState.levelID = 0;

	gameState.frameRate = 60;

//*****SHADERS*******//
	FBO = new cbmini::cbfw::FrameBuffer;
	FBO_BP = new cbmini::cbfw::FrameBuffer;
	FBO_BOX_BLUR = new cbmini::cbfw::FrameBuffer;
	FBO_G_BLUR_X = new cbmini::cbfw::FrameBuffer;
	FBO_G_BLUR_Y = new cbmini::cbfw::FrameBuffer;
	FBO_FINAL = new cbmini::cbfw::FrameBuffer;
	HUD = new cbmini::cbfw::FrameBuffer;
	FBO_MOTION_BLUR = new cbmini::cbfw::FrameBuffer;
	FBO_LIGHT_RAYS = new cbmini::cbfw::FrameBuffer;
	FBO_LIGHT_RAYS_COMPOSITE = new cbmini::cbfw::FrameBuffer;
	FBO_DEFFERED_REDNERING = new cbmini::cbfw::FrameBuffer;
	FBO_SSAO = new cbmini::cbfw::FrameBuffer;

	FBO_SHADOW[0] = new cbmini::cbfw::FrameBuffer;
	FBO_SHADOW[1] = new cbmini::cbfw::FrameBuffer;
	FBO_SHADOW[2] = new cbmini::cbfw::FrameBuffer;
	FBO_SHADOW[3] = new cbmini::cbfw::FrameBuffer;

	skyBox = new SkyBox(player.position);

	shrinkFactor = 8; 
	player.state.tp = true;

	displayCursor = true;
	drawE = false;

	gameState.currentTime = 0.0f;

	player.input.Lmouse = false;
	player.input.Lt = 0.0f; 
	player.input.Rt = 0.0f;

	frames = 0;
	nextUpdate = 0;

	depth_size = 2048;

}

game::~game()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void game::runGame()
{
	
	//for creating the main window
	sf::ContextSettings contextSettings;
	
	// Request a 32-bits depth buffer when creating the window
    contextSettings.depthBits = 32;

	//renders smooth edges
	contextSettings.antialiasingLevel = 4; 

	//sf::Window
	sf::RenderWindow window(sf::VideoMode(gameState.windowWidth, gameState.windowHeight), "Tech Demo", sf::Style::Default, contextSettings);
	this->window = &window; 
	window.setMouseCursorVisible(false); // hide cursor

	//load curser and use it to create sprite
	//sf::Texture texture;
	//texture.loadFromFile("Images/Cursor/cursor2.png");
	//sf::Sprite cursorSprite(texture);

	//load window icon
	//tex *windowIcon;
	//windowIcon = new tex();
	//windowIcon->loadTex("Images/ObjectiveIcon/hand.png");
	//window.setIcon(windowIcon->texMap.getSize().x, windowIcon->texMap.getSize().y, windowIcon->texMap.getPixelsPtr());

    // Create the main window
    window.setVerticalSyncEnabled(true);

    // Make it the active window for OpenGL calls
    window.setActive();
	
	//load and render loading screen
	UI loading = UI("Images/Misc/loadingscreen.png");
	//enable openGL functionality
	initRenderFunc();
	GLfloat ratio = (float)gameState.windowWidth/(float)gameState.windowHeight;
	initWindowFunc();

	glEnable(GL_BLEND);	//particles must have the background as transparent and must be in png format
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//first parameter is the pixel you are currently drawing and second parameter is the old pixel
	
	//shader->inGameMenuShader->Activate();
	//loading.draw(Vec3f(0,0,0), Vec3f(0,0,-1), gameState.windowWidth, gameState.windowHeight);
	//shader->inGameMenuShader->Deactivate();

	glDisable(GL_BLEND);

	window.display();

	//Initialize the text for the GUI
	myGUIView = sf::View(window.getDefaultView());

	//for the player's animation
	player.loadAnimations();
	
	//load level
	levels[0]->loadLevel(); 


//******************PARTICLES*****************************************//
	

///////////////////////////////////////////////////////////
	runningState = running; 
	theCamera.setLastState(theCamera.savedOffset);

	//load sky textures
	skyBox->initSkyBox();
	Sun.loadTex("Images/SkyBox/sun.png");

	//load rand_normal texture
	rand_normals.loadTex("Images/Misc/rand_normals.jpg"); 

	//initialize FBO
	FBO->Initialize(gameState.windowWidth,gameState.windowHeight, 6, 1);
	FBO_BP->Initialize(gameState.windowWidth/shrinkFactor,gameState.windowHeight/shrinkFactor, 1, 0);
	FBO_G_BLUR_X->Initialize(gameState.windowWidth/shrinkFactor,gameState.windowHeight/shrinkFactor, 1, 0);
	FBO_G_BLUR_Y->Initialize(gameState.windowWidth/shrinkFactor,gameState.windowHeight/shrinkFactor, 1, 0);
	FBO_BOX_BLUR->Initialize(gameState.windowWidth/shrinkFactor,gameState.windowHeight/shrinkFactor, 1, 0);
	FBO_FINAL->Initialize(gameState.windowWidth, gameState.windowHeight, 1, 0);
	HUD->Initialize(gameState.windowWidth, gameState.windowHeight, 1, 0);
	FBO_MOTION_BLUR->Initialize(gameState.windowWidth,gameState.windowHeight, 1, 0);
	FBO_LIGHT_RAYS->Initialize(gameState.windowWidth/8,gameState.windowHeight/8, 1, 0);
	FBO_LIGHT_RAYS_COMPOSITE->Initialize(gameState.windowWidth,gameState.windowHeight, 1, 0);
	FBO_DEFFERED_REDNERING->Initialize(gameState.windowWidth,gameState.windowHeight, 1, 0);
	FBO_SSAO->Initialize(gameState.windowWidth,gameState.windowHeight, 1, 0);

	FBO_SHADOW[0]->Initialize(depth_size, depth_size, 0, 1);
	FBO_SHADOW[1]->Initialize(depth_size, depth_size, 0, 1);
	FBO_SHADOW[2]->Initialize(depth_size, depth_size, 0, 1);
	FBO_SHADOW[3]->Initialize(depth_size, depth_size, 0, 1);

//////////////////////////////////////////////////////////
	while(window.isOpen())
	{

		//handles user input whether it be by keyboard or joystick/controller
		handleInput();

		//process events

		//Mouse input
		sf::Vector2i TLocalPosition = sf::Mouse::getPosition(window);
		mouse.current = TLocalPosition;
		mouseMotion(mouse.current, &window);


		sf::Event Event;
		while (window.pollEvent(Event))
		{
			//close window (exit button)
			if(Event.type == sf::Event::Closed)
			{
				cleanUp();
				window.close();
			}
			//escape key (exit game)
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			{
				cleanUp();
				window.close();
			}

			if((Event.type == sf::Event::MouseButtonPressed) && (Event.key.code == sf::Mouse::Right) && (player.alive))
			{
				player.state.aiming = true;
				player.input.Rmouse = true;
				theCamera.setLastState(theCamera.getCurrentVector());
				theCamera.cameraClock.restart();
			}
			
			if((Event.type == sf::Event::MouseButtonReleased) && (Event.key.code == sf::Mouse::Right) && (player.alive))
			{
				player.state.aiming = false;
				player.input.Rmouse = false;
				theCamera.setLastState(theCamera.getCurrentVector());
				theCamera.cameraClock.restart();
			}

			//change perspective
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::P))
			{
				if(player.state.fp == false)
				{
					player.state.fp = true;
					player.state.tp = false;
				}
				else if(player.state.fp == true)
				{
					player.state.fp = false;
					player.state.tp = true;
				}
				theCamera.setLastState(theCamera.getCurrentVector());
				theCamera.cameraClock.restart();
			}

			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Space) && (player.alive) && player.playerMove)
			{
				if(player.position.y <= player.landHeight)
				{
					player.state.jumping = true;
				}
				player.input.space = true;
			}
			if((Event.type == sf::Event::KeyReleased) && (Event.key.code == sf::Keyboard::F))
			{
				cout << "The current FrameRate is: " << gameState.frameRate << endl;
			}

			//adjust the viewport when the window is resized

			if(Event.type == sf::Event::Resized)
			{
				//tell openGL how to convert from coordinates to pixel values
				glViewport(0, 0, Event.size.width, Event.size.height);
				gameState.windowWidth = Event.size.width;
				gameState.windowHeight = Event.size.height;

				//resize the FBO resolution so it matches the window's
				FBO->Release();
				FBO->Initialize(gameState.windowWidth,gameState.windowHeight, 6, 1);

				FBO_BP->Release();
				FBO_BP->Initialize(gameState.windowWidth/shrinkFactor,gameState.windowHeight/shrinkFactor, 1, 0);

				FBO_G_BLUR_X->Release();
				FBO_G_BLUR_X->Initialize(gameState.windowWidth/shrinkFactor,gameState.windowHeight/shrinkFactor, 1, 0);

				FBO_G_BLUR_Y->Release();
				FBO_G_BLUR_Y->Initialize(gameState.windowWidth/shrinkFactor,gameState.windowHeight/shrinkFactor, 1, 0);

				FBO_BOX_BLUR->Release();
				FBO_BOX_BLUR->Initialize(gameState.windowWidth/shrinkFactor,gameState.windowHeight/shrinkFactor, 1, 0);

				FBO_FINAL->Release();
				FBO_FINAL->Initialize(gameState.windowWidth, gameState.windowHeight, 1, 0);

				HUD->Release();
				HUD->Initialize(gameState.windowWidth, gameState.windowHeight, 1, 0);

				FBO_MOTION_BLUR->Release();
				FBO_MOTION_BLUR->Initialize(gameState.windowWidth, gameState.windowHeight, 1, 0);

				FBO_LIGHT_RAYS->Release();
				FBO_LIGHT_RAYS->Initialize(gameState.windowWidth/8,gameState.windowHeight/8, 1, 0);

				FBO_LIGHT_RAYS_COMPOSITE->Release();
				FBO_LIGHT_RAYS_COMPOSITE->Initialize(gameState.windowWidth,gameState.windowHeight, 1, 0);

				FBO_DEFFERED_REDNERING->Release();
				FBO_DEFFERED_REDNERING->Initialize(gameState.windowWidth,gameState.windowHeight, 1, 0);

				FBO_SSAO->Release(); 
				FBO_SSAO->Initialize(gameState.windowWidth,gameState.windowHeight, 1, 0);
			}
		}

		theCamera.aspectRatio = (float)gameState.windowWidth/(float)gameState.windowHeight;
		initWindowFunc();

		//resize the text upon window resize
		myGUIView = sf::View(sf::FloatRect(0.0f, 0.0f, gameState.windowWidth, gameState.windowHeight));
		window.setView(myGUIView);
		
		if(runningState == states::running)
		{
			updateFunc();
			drawFunc(&window);
		}

		// Finally, display the rendered frame on screen
        window.display();
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////
void game::handleInput()
{
	//handles player in game input
	if(runningState == running /*&& player.playerMove*/ && player.alive != false)
	{

		if(player.playerMove)
		{
			GameLevel *tempLevel = &levels[gameState.levelID]->gameLevel; 

			if(gameState.district)
			{
				District *temp = &tempLevel->district[gameState.districtID];
				//player.handleKeyFunc(&theCamera, levels[gameState.levelID]->gameLevel.district[gameState.districtID].Bullets, &levels[gameState.levelID]->gameLevel.district[gameState.districtID].Bullet, levels[gameState.levelID]->gameLevel.district[gameState.districtID].collisionList);
				player.handleKeyFunc(&theCamera);
			}
			else if(gameState.interior)
			{
				player.handleKeyFunc(&theCamera);
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//initializer
void game::initRenderFunc()
{
	glClearDepth(1.f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	glEnable(GL_COLOR_MATERIAL);		//enables color									 
	glEnable(GL_DEPTH_TEST);		//essantial for 3D
	glEnable(GL_LIGHTING);		//enables light

	//rendering is faster
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_NORMALIZE);		//automatically normlize normals
	glEnable(GL_TEXTURE_2D);	//enables 2D textures
	//glEnable(GL_BLEND);
	//glEnable(GL_POLYGON_SMOOTH);
	//glEnable(GL_FOG);		//enables fog

	//for antialaising 
	glEnable(GL_MULTISAMPLE_ARB);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);

	
	//find frent frame of camera
	theCamera.updateCamera();

	//intialize GLEW
	GLenum err = glewInit();

	shader = new Shader();
	shader->LoadShaders(err);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//intializes window and projection/prespective
void game::initWindowFunc()
{
	glMatrixMode(GL_PROJECTION);	//switch to setting the camera perspective
	//set the camera perspective
	glLoadIdentity();	//reset the camera
	
	gluPerspective(45.0f,						//the camera angle
					theCamera.aspectRatio,		//the width to height ratio (aspect ratio)
					1.0f,							//the near z clipping coordinate (if there is something that is closer than one unit to the eye, then openGL will not draw it, do not want object taking up full screen)
					2000.0f);						//the far z clipping coordinate (if there is something that is far than 200 units to the eye, then openGL will not draw it, there is no point in drawing something that you cannot see)

		
	// Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	////////////////////////////////////////////////////////////////////////////////

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//draws the game
void game::drawFunc(sf::RenderWindow *window)
{
	//cout << player.position << endl;
	//cout << player.ZaxisPos << endl;
	//cout << theCamera.position << endl;

	float dt = frameTime.asSeconds();

	//***Render the Game**
	RenderHDRScene(window);

	//bind fbo to primitive to render it to screen
	glActiveTexture(GL_TEXTURE0);
	//FBO_SSAO->BindColour(0); 
	//FBO_DEFFERED_REDNERING->BindColour(0); 
	FBO_MOTION_BLUR->BindColour(0);
	//FBO_FINAL->BindColour(0);
	//FBO->BindColour(0);
	//FBO_LIGHT_RAYS_COMPOSITE->BindColour(0);
	gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);	
	//shader->rippleShader->Deactivate();

	glEnable(GL_BLEND);	//particles must have the background as transparent and must be in png format
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//first parameter is the pixel you are currently drawing and second parameter is the old pixel


	//***Render the HUD***
	HUD->Activate();	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	/*if(runningState == paused)
	{
		if(rainSound->isPlaying)
		{
			rainSound->stopSound();
		}

		if(lowBass->isPlaying)
		{
			lowBass->stopSound();
		}

		shader->inGameMenuShader->Activate();
		inGameMenu.draw(gameState.windowWidth, gameState.windowHeight, &missions, window);
		shader->inGameMenuShader->Deactivate();
	}*/
	//only play rain sound if we are outside
	/*else if (gameState.district)
	{
		if(!rainSound->isPlaying)
		{
			rainSound->playSound();
		}
	}
	else
	{
		if(rainSound->isPlaying)
		{
			rainSound->stopSound();
		}
	}*/
	
	/*shader->HealthShader->Activate();
	if(player.health < 0)
	{
		player.health = 0;
	}
	//glUniform1i(glGetUniformLocation(shader->HealthShader->GetHandle(), "health"), player.health);
	glUniform1f(glGetUniformLocation(shader->HealthShader->GetHandle(), "health"), (float)player.health);
	//glUniform1f(glGetUniformLocation(shader->HealthShader->GetHandle(), "health"), 100.0);

	ui.draw(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);
	
	if(!player.alive)
	{
		glUniform1i(glGetUniformLocation(shader->HealthShader->GetHandle(), "health"), 0.0f);
		deathUI.draw(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);
	}

	glDisable(GL_BLEND);
	shader->HealthShader->Deactivate();*/
	HUD->Deactivate();

	//bind fbo to screen to render it
	glEnable(GL_BLEND);	//particles must have the background as transparent and must be in png format
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//first parameter is the pixel you are currently drawing and second parameter is the old pixel
	glDisable(GL_DEPTH_TEST);
	HUD->BindColour(0);
	gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	//draw missions (text) to screen
	//missions.drawGameMissions(window, dt);

	theCamera.prevViewMat = theCamera.viewMat;
	theCamera.prevProjectionMat = theCamera.projectionMat; 

	//calculate frames per second (frame rate)
	frames++;
	float overtime = clock() - nextUpdate;
	if (overtime > 0)
	{
		gameState.frameRate = frames / (float)(1+ (float)overtime/(float)CLOCKS_PER_SEC);
		frames = 0;
		nextUpdate = clock() + 1 * CLOCKS_PER_SEC;
	}

	//fix errors 
	if( gameState.frameRate <= 0)
	{
		gameState.frameRate = 60.0f;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Everything that renders the 3D scene with HDR
void game::RenderHDRScene(sf::RenderWindow *window)
{
	//Render shadow map for each light
	{
	////////////////////////////////////////////////////////////////////////////////
		theCamera.fovy = 45.0f;
		theCamera.nearPlane = 1.0f;
		theCamera.farPlane = 500.0f;

		obj_BoundingSphere obj_BSphere[4];

		int td = 256 / 2; //900/2;

		obj_BSphere[0].center = Vec3f(-td, 50.0f, -td);
		obj_BSphere[1].center = Vec3f(-td, 50.0f,  td);
		obj_BSphere[2].center = Vec3f( td, 50.0f,  td);
		obj_BSphere[3].center = Vec3f( td, 50.0f, -td);
		obj_BSphere[0].radius = 1.0f;
		obj_BSphere[1].radius = 1.0f;
		obj_BSphere[2].radius = 1.0f;
		obj_BSphere[3].radius = 1.0f;

		// set up camera
		// update camera once per-frame

		// compute V matrix by inverting the camera's transform in world space
		theCamera.viewMat = theCamera.lightViewMat = LookAt(Vec3f(0.0f, 0.0f, 0.0f), (levels[gameState.levelID]->gameLevel.district[gameState.districtID].directedLightPosition.returnAsVec3f() - player.startingPosition).normalize(), Vec3f(0.0f, 1.0f, 0.0f));

		glDisable(GL_TEXTURE_2D);

		// offset the geometry slightly to prevent z-fighting
		// note that this introduces some light-leakage artifacts
		glPolygonOffset( 1.0f, 4096.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);

		// draw all faces since our terrain is not closed.
		glCullFace(GL_FRONT);

		//calculate frustrum splits
		int numSplits = 4;
		float strength = 0.75f;
		float ratio = theCamera.farPlane / theCamera.nearPlane;
		theCamera.f[0].neard =  theCamera.nearPlane;

		for(int i = 1; i < numSplits; i++)
		{
			theCamera.lightProjectionMat[i] = Identity();

			float si = i / (float)numSplits; 

			//computes the near and far distances for every frustum slice
			// in camera eye space - that is, at what distance does a slice start and end
			theCamera.f[i].neard = strength * (theCamera.nearPlane * powf(ratio, si )) + ((1.0f - strength) * (theCamera.nearPlane + (si  * (theCamera.farPlane - theCamera.nearPlane)))); 
			theCamera.f[i - 1].fard = theCamera.f[i].neard * 1.005f;

			//cout << theCamera.f[i - 1].fard << endl;
		}

		theCamera.f[numSplits - 1].fard =  theCamera.farPlane;

		for(int i = 0; i < numSplits; i++)
		{
			float nearDist = theCamera.f[i].neard;
			float farDist = theCamera.f[i].fard;

			// these heights and widths are half the heights and widths of
			// the near and far plane rectangles
			float nearHeight = tanf((theCamera.fovy * DegreesToRadians) / 2.0f) * nearDist;
			float nearWidth = nearHeight * theCamera.aspectRatio;
			float farHeight = tanf((theCamera.fovy * DegreesToRadians) / 2.0f) * farDist;
			float farWidth = farHeight * theCamera.aspectRatio;

			Vec3f fc = theCamera.position + (theCamera.ForwardVector * farDist);
			Vec3f nc = theCamera.position + (theCamera.ForwardVector * nearDist);
				
			Vec4f cornerPoints[8]; 
				
			//near plane
			cornerPoints[0] = Vec4f(nc - (theCamera.UpVector * nearHeight) - (theCamera.RightVector * nearWidth), 1.0f);  
			cornerPoints[1] = Vec4f(nc + (theCamera.UpVector * nearHeight) - (theCamera.RightVector * nearWidth), 1.0f); 
			cornerPoints[2] = Vec4f(nc + (theCamera.UpVector * nearHeight) + (theCamera.RightVector * nearWidth), 1.0f);  
			cornerPoints[3] = Vec4f(nc - (theCamera.UpVector * nearHeight) + (theCamera.RightVector * nearWidth), 1.0f); 
	
			//far plane
			cornerPoints[4] = Vec4f(fc - (theCamera.UpVector * farHeight) - (theCamera.RightVector * farWidth), 1.0f);  //topLeft
			cornerPoints[5] = Vec4f(fc + (theCamera.UpVector * farHeight) - (theCamera.RightVector * farWidth), 1.0f); //topRight
			cornerPoints[6] = Vec4f(fc + (theCamera.UpVector * farHeight) + (theCamera.RightVector * farWidth), 1.0f);  //bottomLeft
			cornerPoints[7] = Vec4f(fc - (theCamera.UpVector * farHeight) + (theCamera.RightVector * farWidth), 1.0f); //bottomRight


			// builds a projection matrix for rendering from the shadow's POV.
			// First, it computes the appropriate z-range and sets an orthogonal projection.
			// Then, it translates and scales it, so that it exactly captures the bounding box
			// of the current frustum slice
			Vec4f transf;

			transf = theCamera.lightViewMat * cornerPoints[0];
			float minZ = transf.z;
			float maxZ = transf.z; 
			for(int k = 1; k < 8; k++)
			{
				transf = theCamera.lightViewMat * cornerPoints[k];
				if(transf.z > maxZ)
				{
					maxZ = transf.z;
				}
				if(transf.z < minZ)
				{
					minZ = transf.z;
				}
			}

			// make sure all relevant shadow casters are included
			// note that these here are dummy objects at the edges of our scene
			for(int k = 0; k < 4; k ++)
			{
				transf = theCamera.lightViewMat * Vec4f(obj_BSphere[k].center, 1.0f);
				if(transf.z + obj_BSphere[k].radius > maxZ)
				{
					maxZ = transf.z + obj_BSphere[k].radius;
				}
				
				if(transf.z - obj_BSphere[k].radius < minZ) 
				{
					minZ = transf.z - obj_BSphere[k].radius;
				}
				
			}

			// set the projection matrix with the new z-bounds
			// note the inversion because the light looks at the neg. z axis
			// gluPerspective(LIGHT_FOV, 1.0, maxZ, minZ); // for point lights
			theCamera.lightProjectionMat[i] = Orthographic(-1.0f, 1.0f, -1.0f, 1.0f, -minZ, -maxZ);  

			float maxX = -1000.0f;
			float maxY = -1000.0f;
			float minX = 1000.0f;
			float minY = 1000.0f;

			for(int k = 0; k < 8; k++)
			{
				transf = theCamera.lightProjectionMat[i] * theCamera.lightViewMat * cornerPoints[k];

				transf.x /= transf.a;
				transf.y /= transf.a;

				//
				if(transf.x > maxX)
				{
					maxX = transf.x;
				}
				if(transf.x < minX)
				{
					minX = transf.x;
				}
				//
				if(transf.y > maxY)
				{
					maxY = transf.y;
				}
				if(transf.y < minY)
				{
					minY = transf.y;
				}
			}

			//build a crop matrix so we makes sure that we get the best precision in z and loose as little as possible in x and y
			float scaleX = 2.0f / (maxX - minX);
			float scaleY = 2.0f / (maxY - minY);
			float offsetX = -0.5f * (maxX + minX) * scaleX;
			float offsetY = -0.5f * (maxY + minY) * scaleY;

			theCamera.cropMat[i] = Mat4f(Vec4f(scaleX, 0.0f, 0.0f, offsetX),
											Vec4f(0.0f, scaleY, 0.0f, offsetY),
											Vec4f(0.0f, 0.0f, 1.0f, 0.0f),
											Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
			

			theCamera.sliceProjectionMat[i] = theCamera.lightProjectionMat[i];  
				
			// apply a crop matrix to modify the projection matrix we got from glOrtho.
			theCamera.projectionMat = theCamera.lightProjectionMat[i] = theCamera.cropMat[i] * theCamera.sliceProjectionMat[i]; //Orthographic(gameState.windowWidth, gameState.windowHeight, 1.0f, 2000.0f); 

			// store the product of all shadow matries for later
			theCamera.cpm[i] = theCamera.projectionMat * theCamera.lightViewMat; 
		////////////////////////////////////////////////////////////////////////////////////
			// make the current depth map a rendering target
			FBO_SHADOW[i]->Activate();
			glViewport(0, 0, depth_size, depth_size); 

			// clear the depth texture from last time
			glClear(GL_DEPTH_BUFFER_BIT);

			shader->shadowMapShader->Activate();

			glUniformMatrix4fv(glGetUniformLocation(shader->shadowMapShader->GetHandle(), "projectionMat"), 1, 1, theCamera.projectionMat.m);
			glUniformMatrix4fv(glGetUniformLocation(shader->shadowMapShader->GetHandle(), "viewMat"), 1, 1, theCamera.viewMat.m);

			///*Player*/
			player.drawCharacter(shader->shadowMapShader, theCamera, true);
		
			levels[gameState.levelID]->drawDistrict(gameState.districtID, shader->shadowMapShader, shader, theCamera, player);

			shader->shadowMapShader->Deactivate();

			FBO_SHADOW[i]->Deactivate();
		}

		// revert to normal back face culling as used for rendering
		//glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glDisable(GL_POLYGON_OFFSET_FILL);

		glEnable(GL_TEXTURE_2D);
	}

	//Render 3D scene to offscreen Framebuffer
	{
	//////////////////////////////////////////////////////////////////////////

		//set up perspective
		theCamera.projectionMat = Perspective(theCamera.fovy, theCamera.aspectRatio, theCamera.nearPlane, theCamera.farPlane);

		// set up camera
		// update camera once per-frame
		theCamera.viewMat = (RotateX(theCamera.thetaX) * RotateY(theCamera.thetaY)) * Translate(theCamera.position.negate()); 

	//////////////////////////////////////////////////////////////////////////

		FBO->Activate();
		glViewport(0,0,gameState.windowWidth,gameState.windowHeight);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		/*Camera*/ //for FBO
		//first 3 variables are the positon of the camera
		//second three variables are the postion that the camera is looking at
		//last theree variables is where up is. 

		glPushMatrix();
		gluLookAt(theCamera.position.x,theCamera.position.y, theCamera.position.z, 
				  theCamera.playerPoint.x, theCamera.playerPoint.y, theCamera.playerPoint.z, 
				  0.0f, 1.0f, 0.0f); 

		shader->ShaderProgram->Activate();

		Mat4f lightTransfrom = Translate(levels[gameState.levelID]->gameLevel.district[gameState.districtID].directedLightPosition.x,
										levels[gameState.levelID]->gameLevel.district[gameState.districtID].directedLightPosition.y,
										levels[gameState.levelID]->gameLevel.district[gameState.districtID].directedLightPosition.z);

		glUniformMatrix4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "projectionMat"), 1, 1, theCamera.projectionMat.m);
		glUniformMatrix4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "viewMat"), 1, 1, theCamera.viewMat.m);
		glUniformMatrix4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "prevViewMat"), 1, 1, theCamera.prevViewMat.m);
		glUniformMatrix4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "prevProjectionMat"), 1, 1, theCamera.prevProjectionMat.m);

		Mat4f inverseViewMat = transformInverseNoScale(theCamera.viewMat);

		glUniformMatrix4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "lightProjectionMat"), 4, 1, (float*)theCamera.lightProjectionMat);
		glUniformMatrix4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "lightViewMat"), 1, 1, theCamera.lightViewMat.m);

		//// theCamera.splits[i] is originally in eye space - tell's us how far we can see.
		//// Here we compute it in camera homogeneous coordinates. Basically, we calculate
		//// cam_proj * (0, 0, theCamera.splits[i], 1)^t and then normalize to [0; 1]
		float far_bound[4]; 
		far_bound[0] = 0.5f * (-theCamera.f[0].fard * theCamera.projectionMat.transpose().m[10] + theCamera.projectionMat.transpose().m[14]) / theCamera.f[0].fard + 0.5f;
		far_bound[1] = 0.5f * (-theCamera.f[1].fard * theCamera.projectionMat.transpose().m[10] + theCamera.projectionMat.transpose().m[14]) / theCamera.f[1].fard + 0.5f;
		far_bound[2] = 0.5f * (-theCamera.f[2].fard * theCamera.projectionMat.transpose().m[10] + theCamera.projectionMat.transpose().m[14]) / theCamera.f[2].fard + 0.5f;
		far_bound[3] = 0.5f * (-theCamera.f[3].fard * theCamera.projectionMat.transpose().m[10] + theCamera.projectionMat.transpose().m[14]) / theCamera.f[3].fard + 0.5f;

		glUniform4fv(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "farDist"), 1, far_bound);

		glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "useNormalMap"), 0.0f);

		//textures
		glUniform1i(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "my_color_texture"), 0);
		glUniform1i(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "shadowMap1"), 2);
		glUniform1i(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "shadowMap2"), 3);
		glUniform1i(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "shadowMap3"), 4);
		glUniform1i(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "shadowMap4"), 5);
		//glUniform1i(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "jitter"), 6);

		glActiveTexture(GL_TEXTURE2);
		FBO_SHADOW[0]->BindDepth();
		
		glActiveTexture(GL_TEXTURE3);
		FBO_SHADOW[1]->BindDepth();

		glActiveTexture(GL_TEXTURE4);
		FBO_SHADOW[2]->BindDepth();

		glActiveTexture(GL_TEXTURE5);
		FBO_SHADOW[3]->BindDepth();

		if(gameState.district)
		{
			skyBox->drawSkyBox(shader->ShaderProgram);
		}

		glUniform1f(glGetUniformLocation(shader->ShaderProgram->GetHandle(), "enableLight"), 1.0f); //true 

		///*Player*/
		player.drawCharacter(shader->ShaderProgram, theCamera, false);
	
		//the level
		levels[gameState.levelID]->drawDistrict(gameState.districtID, shader->ShaderProgram, shader, theCamera, player);

		shader->ShaderProgram->Deactivate();


		shader->Particle_Shader->Activate();
		//*******PARTICLES************)
	
		glEnable(GL_BLEND);	//particles must have the background as transparent and must be in png format
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//first parameter is the pixel you are currently drawing and second parameter is the old pixel


		Vec4f lightPos =  levels[gameState.levelID]->gameLevel.district[gameState.districtID].directedLightPosition;
		lightPos.w = 1.0f;
		Mat4f modelMat = Translate(player.position - player.startingPosition);
		lightPos = modelMat * lightPos;

		glUniform1f(glGetUniformLocation(shader->Particle_Shader->GetHandle(), "size"), 100.0f);
		glUniform1f(glGetUniformLocation(shader->Particle_Shader->GetHandle(), "alpha"), 1.0f); 
		glUniform1f(glGetUniformLocation(shader->Particle_Shader->GetHandle(), "black"), 1.0f);
		
		Mat4f projectionMat = Perspective(theCamera.fovy, theCamera.aspectRatio, theCamera.nearPlane, 1000.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader->Particle_Shader->GetHandle(), "projectionMat"), 1, 1, projectionMat.m);
		glUniformMatrix4fv(glGetUniformLocation(shader->Particle_Shader->GetHandle(), "modelViewMat"), 1, 1, theCamera.viewMat.m);

		//render the sun's texture
		glPushMatrix();
		Sun.drawTex(0);
		glBegin(GL_POINTS);
				glVertex3f(lightPos.x, lightPos.y, lightPos.z);
		glEnd();
		glPopMatrix();

		glUniform1f(glGetUniformLocation(shader->Particle_Shader->GetHandle(), "black"), 0.0f);

		glDisable(GL_BLEND);
		glPopMatrix();
		shader->Particle_Shader->Deactivate();
		FBO->Deactivate();
	}
	glDisable(GL_DEPTH_TEST);

	//Screen Space Ambient Occlusion 
	/*{
		FBO_SSAO->Activate();
		glViewport(0, 0, (gameState.windowWidth), (gameState.windowHeight)); 
		shader->ssaoShader->Activate(); 

		glUniform1i(glGetUniformLocation(shader->ssaoShader->GetHandle(), "normal_texture"), 0);
		glUniform1i(glGetUniformLocation(shader->ssaoShader->GetHandle(), "pos_texture"), 1);
		glUniform1i(glGetUniformLocation(shader->ssaoShader->GetHandle(), "rand_texture"), 2);
		glUniform1i(glGetUniformLocation(shader->ssaoShader->GetHandle(), "diffuse_texture"), 3);

		glActiveTexture(GL_TEXTURE0);
		FBO->BindColour(3);

		glActiveTexture(GL_TEXTURE1);
		FBO->BindColour(4);

		glActiveTexture(GL_TEXTURE2);
		rand_normals.drawTex(2); 

		glActiveTexture(GL_TEXTURE3);
		FBO->BindColour(0); 

		gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);

		shader->ssaoShader->Deactivate(); 
		FBO_SSAO->Deactivate();
	}*/

	//Render lighting (Deffered Rendering) 
	{
		//FBO_DEFFERED_REDNERING->Activate();
		//glViewport(0, 0, (gameState.windowWidth), (gameState.windowHeight)); 
		//shader->defferedRenderingShader->Activate();

		//glUniform4fv(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "gameLights[0].position"), 1, Vec4f(-175.0f, 400.0f, 175.0f, 0.0f).v);
		//glUniform4fv(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "gameLights[0].color"), 1, Vec4f(1.0f, 0.89f, 0.45f, 1.0f).v);      
		//																																						   
		//// theCamera.splits[i] is originally in eye space - tell's us how far we can see.																		   
		//// Here we compute it in camera homogeneous coordinates. Basically, we calculate																		   
		//// cam_proj * (0, 0, theCamera.splits[i], 1)^t and then normalize to [0; 1]
		///*float far_bound[4]; 
		//far_bound[0] = 0.5f * (-theCamera.f[0].fard * theCamera.projectionMat.transpose().m[10] + theCamera.projectionMat.transpose().m[14]) / theCamera.f[0].fard + 0.5f;
		//far_bound[1] = 0.5f * (-theCamera.f[1].fard * theCamera.projectionMat.transpose().m[10] + theCamera.projectionMat.transpose().m[14]) / theCamera.f[1].fard + 0.5f;
		//far_bound[2] = 0.5f * (-theCamera.f[2].fard * theCamera.projectionMat.transpose().m[10] + theCamera.projectionMat.transpose().m[14]) / theCamera.f[2].fard + 0.5f;
		//far_bound[3] = 0.5f * (-theCamera.f[3].fard * theCamera.projectionMat.transpose().m[10] + theCamera.projectionMat.transpose().m[14]) / theCamera.f[3].fard + 0.5f;

		//glUniform4fv(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "farDist"), 1, far_bound);*/

		///*glUniformMatrix4fv(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "lightProjectionMat"), 4, 1, (float*)theCamera.lightProjectionMat);
		//glUniformMatrix4fv(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "lightViewMat"), 1, 1, theCamera.lightViewMat.m);*/

		//glUniform1i(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "s_texture"), 0);
		//glUniform1i(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "s_texture1"), 1);
		//glUniform1i(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "s_texture2"), 2);
		//glUniform1i(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "s_texture3"), 3);

		///*glUniform1i(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "shadowMap1"), 4);
		//glUniform1i(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "shadowMap2"), 5);
		//glUniform1i(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "shadowMap3"), 6);
		//glUniform1i(glGetUniformLocation(shader->defferedRenderingShader->GetHandle(), "shadowMap4"), 7);*/


		//glActiveTexture(GL_TEXTURE0);
		//FBO->BindColour(0);

		//glActiveTexture(GL_TEXTURE1);
		//FBO->BindColour(3);

		//glActiveTexture(GL_TEXTURE2);
		//FBO->BindColour(4);

		//glActiveTexture(GL_TEXTURE3);
		//FBO->BindColour(5);

		///*glActiveTexture(GL_TEXTURE4);
		//FBO_SHADOW[0]->BindDepth();
		//
		//glActiveTexture(GL_TEXTURE5);
		//FBO_SHADOW[1]->BindDepth();

		//glActiveTexture(GL_TEXTURE6);
		//FBO_SHADOW[2]->BindDepth();

		//glActiveTexture(GL_TEXTURE7);
		//FBO_SHADOW[3]->BindDepth();*/

		//gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);

		//shader->defferedRenderingShader->Deactivate();
		//FBO_DEFFERED_REDNERING->Deactivate();
	}

	//Hightlight Bright areas (tone-mapping)
	{
		FBO_BP->Activate();
		glViewport(0, 0, (gameState.windowWidth/shrinkFactor), (gameState.windowHeight/shrinkFactor)); 
			
		shader->HDR_BP_Shader->Activate();

		////bind fbo to primitive to see what is going on 
		glActiveTexture(GL_TEXTURE0);
		//FBO_MOTION_BLUR->BindColour(0);
		FBO->BindColour(0);
		gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);
			
		shader->HDR_BP_Shader->Deactivate();
		FBO_BP->Deactivate();
	}

	//Apply a Box Blur 
	{
		FBO_BOX_BLUR->Activate();

		shader->HDR_Box_Blur_Shader->Activate();

		//send pixel size to shader
		//glUniform2f(glGetUniformLocation(shader->HDR_Box_Blur_Shader->GetHandle(), "pixelSize"), 1.0f/(float)(gameState.windowWidth/shrinkFactor), 1.0f/(float)(gameState.windowHeight/shrinkFactor));

		////bind fbo to primitive to see what is going on 
		glActiveTexture(GL_TEXTURE0);
		//FBO_BP->BindColour(0);
		FBO_BP->BindColour(0);
		gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);

		shader->HDR_Box_Blur_Shader->Deactivate();
		FBO_BOX_BLUR->Deactivate();
	}

	//Apply a 1D Gaussian blur horzontally (x-axis)
	{
		FBO_G_BLUR_X->Activate();

		shader->HDR_G_Blur_X_Shader->Activate();

		//send pixel size to shader
		//glUniform2f(glGetUniformLocation(shader->HDR_G_Blur_X_Shader->GetHandle(), "pixelSize"), 1.0f/(float)(gameState.windowWidth/shrinkFactor), 1.0f/(float)(gameState.windowHeight/shrinkFactor));

		////bind fbo to primitive to see what is going on 
		glActiveTexture(GL_TEXTURE0);
		FBO_BOX_BLUR->BindColour(0);
		gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);

		shader->HDR_G_Blur_X_Shader->Deactivate();
		FBO_G_BLUR_X->Deactivate();
	}

	//Apply a 1D Gaussian blur vertically (y-axis)
	{
		FBO_G_BLUR_Y->Activate();

		shader->HDR_G_Blur_Y_Shader->Activate();

		//send pixel size to shader
		//glUniform2f(glGetUniformLocation(shader->HDR_Box_Blur_Shader->GetHandle(), "pixelSize"), 1.0f/(float)(gameState.windowWidth/shrinkFactor), 1.0f/(float)(gameState.windowHeight/shrinkFactor));

		////bind fbo to primitive to see what is going on 
		glActiveTexture(GL_TEXTURE0);
		FBO_G_BLUR_X->BindColour(0);
		gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);

		shader->HDR_G_Blur_Y_Shader->Deactivate();
		FBO_G_BLUR_Y->Deactivate();
	}

	
	//Final Image = FBO_BOX_BLUR + FBO
	{
		FBO_FINAL->Activate();
		glViewport(0, 0, (gameState.windowWidth), (gameState.windowHeight)); 
		//glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
		//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		shader->HDR_Final_Shader->Activate();

		glUniform1i(glGetUniformLocation(shader->HDR_Final_Shader->GetHandle(), "myTextureSampler0"), 0);

		glUniform1i(glGetUniformLocation(shader->HDR_Final_Shader->GetHandle(), "myTextureSampler1"), 1);

		glActiveTexture(GL_TEXTURE0);
		FBO->BindColour();
			
		glActiveTexture(GL_TEXTURE1);
		FBO_G_BLUR_Y->BindColour();
			
		gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);

		shader->HDR_Final_Shader->Deactivate();
		FBO_FINAL->Deactivate();
	}

	
	//Light Rays
	{
		FBO_LIGHT_RAYS->Activate();
		glViewport(0, 0, (gameState.windowWidth / 8), (gameState.windowHeight / 8)); 
		shader->lightRaysShader->Activate();

		Vec4f lightScreenPos =  levels[gameState.levelID]->gameLevel.district[gameState.districtID].directedLightPosition;
		lightScreenPos.w = 1.0f;
		Mat4f modelMat = Translate(player.position - player.startingPosition);
		lightScreenPos = theCamera.projectionMat * theCamera.viewMat * modelMat * lightScreenPos;

		glUniform4fv(glGetUniformLocation(shader->lightRaysShader->GetHandle(), "lightPositionOnScreen"), 1, lightScreenPos.v);
		
		glUniform1i(glGetUniformLocation(shader->lightRaysShader->GetHandle(), "firstPass"), 0);

		glActiveTexture(GL_TEXTURE0);
		FBO->BindColour(2);

		gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);

		shader->lightRaysShader->Deactivate();
		FBO_LIGHT_RAYS->Deactivate();
	}

	//light ray composite
	{
		FBO_LIGHT_RAYS_COMPOSITE->Activate();
		glViewport(0, 0, (gameState.windowWidth), (gameState.windowHeight)); 

		shader->lightRaysCompositeShader->Activate();

		glUniform1i(glGetUniformLocation(shader->lightRaysCompositeShader->GetHandle(), "texture0"), 0);
		glUniform1i(glGetUniformLocation(shader->lightRaysCompositeShader->GetHandle(), "texture1"), 1); 

		glActiveTexture(GL_TEXTURE0);
		FBO_LIGHT_RAYS->BindColour(0);
			
		glActiveTexture(GL_TEXTURE1);
		FBO_FINAL->BindColour(0);

		gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);

		shader->lightRaysCompositeShader->Deactivate();
		FBO_LIGHT_RAYS_COMPOSITE->Deactivate();
	}

	//Motion blur
	{
		FBO_MOTION_BLUR->Activate();
		//glViewport(0, 0, (1920), (1080)); 
		glViewport(0, 0, (gameState.windowWidth), (gameState.windowHeight)); 
		shader->motionBlurShader->Activate();

		//uVelocityScale = currentFps / targetFps;
		float uVelocityScale = gameState.frameRate / 60.0f;

		if(uVelocityScale >= 1)
		{
			glUniform1f(glGetUniformLocation(shader->motionBlurShader->GetHandle(), "uVelocityScale"), 1.0f);
		}
		else
		{
			glUniform1f(glGetUniformLocation(shader->motionBlurShader->GetHandle(), "uVelocityScale"), uVelocityScale); 
		}

		glUniform1i(glGetUniformLocation(shader->motionBlurShader->GetHandle(), "uTexInput"), 0);
		glUniform1i(glGetUniformLocation(shader->motionBlurShader->GetHandle(), "uTexVelocity"), 1); 

		glActiveTexture(GL_TEXTURE0);
		FBO_LIGHT_RAYS_COMPOSITE->BindColour(0);
			
		glActiveTexture(GL_TEXTURE1);
		FBO->BindColour(1);

		gameScreen.drawScreen(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f,0.0f, -1.0f), gameState.windowWidth, gameState.windowHeight);

		shader->motionBlurShader->Deactivate();
		FBO_MOTION_BLUR->Deactivate();
	}

	glEnable(GL_DEPTH_TEST);
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Delete stuff here
void game::cleanUp()
{ 
	levels[0]->deleteLevel();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
// update anything that needs to be updated and/or moved
void game::updateFunc()
{
	//update time every frame
	frameTime = theClock.getElapsedTime();
	theClock.restart();
	float dt = frameTime.asSeconds();
	//rippleTime += dt;
	player.ETimer += dt;
	gameState.currentTime += dt;
	//For when the player jumps
	player.playerJumping(&theCamera);
	
	//calcualte the TLocal axis of which the player will move on depending on the orientation of the camera
	player.calcAxis();

	skyBox->updateSkyBox(player.position);
	
	//update camera
	theCamera.updateCamera(player.ZaxisPos,player.XaxisPos, player.ZaxisNeg, player.position, player.landHeight, player.state.fp, player.state.aiming);

////************player animation*******************//
	  player.updateAnimations(dt);

//************************************************//
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//handles updating mouse input, mouse direction, and camera's orientation
void game::mouseMotion(sf::Vector2i current, sf::RenderWindow *window)
{
	//if we are in the actually game and not in the menu
	if(runningState != states::menu && runningState != states::paused)
	{
		//make curser invisable to player
		displayCursor = false;

		//center of the screen
		Vec3f center = Vec3f(gameState.windowWidth/2.0f, gameState.windowHeight/2.0f, 0.0f);
		
		//calculate the differnece between the mouse and the center of the screen
		Vec3f diff; 
		
		diff = (Vec3f(mouse.current.x,mouse.current.y, 0.0f) - center) /* 0.5f*/;

		theCamera.thetaY += diff.x / 10.0f;	//rotation on Y-axis
		theCamera.thetaX += diff.y / 10.0f;	//rotation on X-axis


		//have a looking bound
		if(theCamera.thetaX > 76 || theCamera.thetaX < -70)
		{
			theCamera.thetaX -= diff.y / 10.0f;
		}

		//apply rotation for player 
		player.theta = theCamera.thetaY - 180;

		Vec4f currentVector = (RotateY(theCamera.thetaY * -1) * RotateX(theCamera.thetaX)) * Vec4f(theCamera.startingVector, 1.0f); 

		theCamera.setCurrentVector(Vec3f(currentVector.x, currentVector.y, currentVector.z));
		theCamera.setSavedOffset(theCamera.currentVector);

		//set the mouse back to the center of the screen
		sf::Mouse::setPosition(sf::Vector2i(gameState.windowWidth/2.0f, gameState.windowHeight/2.0f), *window);


		/*fix floating point errors*/
		if(player.theta >= 360.0f)
		{
			player.theta -= 360.0f;
		
		}
		else if(player.theta <= -360.0f)
		{
			player.theta += 360.0f;
		
		}
	}
	//if we are in a menu
	else
	{
		//make curser visable to player
		displayCursor = true;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

