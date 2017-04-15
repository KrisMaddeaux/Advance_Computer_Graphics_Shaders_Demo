#pragma once
#include "Include/SFML/Graphics.hpp"
#include "Include\GL\glew.h"
#include "MathClass.h" 
//using namespace std;

//frustrum data
struct frustrum
{
	float neard;
	float fard; 
};

#ifndef CAMERA_H
#define CAMERA_H

class camera1
{
public:
	camera1();
	~camera1();

	void setStartingVector (Vec3f levelStartingVector);
	void setCurrentVector (Vec3f currentVec);
	void setPosition (/*Vec3f positionition*/);
	void setSavedOffset(Vec3f currentVec);
	void setLastState(Vec3f parameter);
	void updateCamera(Vec3f ZaxisPos, Vec3f XaxisPos, Vec3f ZaxisNeg, Vec3f position, float landHeight, bool fp, bool aiming); 
	void updateCamera(); 

	Vec3f getStartingVector ();
	Vec3f getCurrentVector ();
	Vec3f getPosition ();

	Vec3f position;	//the position of the camera in world space
	Vec3f startingVector; //the starting difference between the player's and camera's position (the camera's position in the player's object space)
	Vec3f currentVector;  //the difference between the player's and camera's position (the camera's position in the player's object space)
	Vec3f savedOffset;

	float thetaX;
	float thetaY; 

	Vec3f ForwardVector;
	Vec3f UpVector;
	Vec3f RightVector;

	Vec3f playerPoint;	//the position that tells the camera where to look at
	Vec3f playerPointReserved;

	Vec3f lastState;

	//***************CAMERA DELTA TIME********************//
	sf::Clock cameraClock;

	//for perspective change
	float lerpTime;

	//these matrices must be set and updated
	Mat4f projectionMat; 
	Mat4f viewMat; 
	Mat4f eyeToWorld;

	//Mat4f prevModelViewProj;
	//Mat4f inverseModelViewMat;

	Mat4f prevViewMat; 
	Mat4f prevProjectionMat; 

	//for shadows
	Mat4f lightProjectionMat[4]; 
	Mat4f lightViewMat; 
	Mat4f lightToWorld;

	//for camera's frustruim
	float aspectRatio; 
	float fovy;
	float nearPlane;
	float farPlane;
	//GLfloat splits[5];	//splits in the camera's frustrum on the Z-axis, for cascaded shadow mapping 
	frustrum f[4];
	Mat4f cropMat[4]; //crop matrix for each split/slice
	Mat4f sliceProjectionMat[4]; //orthogonal matrix for every split/slice
	Mat4f cpm[4];  //crop-projection-modelview matrix


	////view frustrum's shape//
	////The height and width of the rectangular boundary on the near plane
	//float Hnear;
	//float Wnear; 
	////The height and width of the rectangular boundary on the far plane
	//float Hfar;
	//float Wfar;

};

#endif