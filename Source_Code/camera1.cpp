#include "camera1.h"

camera1::camera1()
{
	//initializations
		position = Vec3f(0,0,0);
		startingVector = Vec3f(0,0,0);
		currentVector = Vec3f(0,0,0);

		ForwardVector = Vec3f(0,0,0) ;
		UpVector = Vec3f(0,0,0);
		RightVector = Vec3f(0,0,0);
		//savedOffset = Vec3f(0.0f, 10.0f, -40.0f);

		lerpTime = 0.5f;

		//prevModelViewProj = Identity();

		prevViewMat = Identity();
		prevProjectionMat = Identity();

		thetaX = 0.0f;
		thetaY = 0.0f;
}
camera1::~camera1()
{

}

void camera1::setStartingVector (Vec3f levelStartingVector)
{
	startingVector = levelStartingVector;
}

void camera1::setCurrentVector (Vec3f currentVec)
{
	currentVector = currentVec;
}

void camera1::setSavedOffset (Vec3f currentVec)
{
	savedOffset = currentVec;
}
void camera1::setLastState(Vec3f parameter)
{
	lastState = parameter;
}
void camera1::setPosition ()
{
	position = playerPointReserved + currentVector; 
}

void camera1::updateCamera(Vec3f ZaxisPos, Vec3f XaxisPos, Vec3f ZaxisNeg, Vec3f playerPosition, float landHeight, bool fp, bool aiming)
{
	//cout << ForwardVector << endl;

	//find frenet frame of camera
	ForwardVector = (playerPoint - Vec3f(position.x, -position.y, position.z)).normalize();
	RightVector = ((ForwardVector).cross(Vec3f(0.0f, 1.0f, 0.0f))).normalize();
	UpVector = (RightVector.cross(ForwardVector)).normalize();

	ForwardVector = ForwardVector.negate();
	RightVector = RightVector.negate();
	UpVector = UpVector.negate();


	////update camera for first person view
	// float tempTime = cameraClock.getElapsedTime().asSeconds();
	// if(tempTime > lerpTime)
	// {
	//	tempTime = lerpTime;
	// }
	// //for first person perspective
	// Vec3f bob = playerPosition + (ZaxisPos*50.0f) ;
	// if(fp && lastState == XaxisPos*-2.5f + ZaxisNeg*8.5f + Vec3f(0.0f, playerPosition.y + 8.0f, 0.0f))
	// {
	//	  setCurrentVector(LERP(lastState, Vec3f(0.0f, 6.1f + playerPosition.y - landHeight , 0.0f) , tempTime/lerpTime));
	//	  playerPoint = LERP(playerPosition, bob, tempTime/lerpTime);
	//	  setPosition();
	// }
	// else if(fp)
	// {
	//	  setCurrentVector(LERP(lastState, Vec3f(0.0f, 6.1f + playerPosition.y - landHeight , 0.0f) , tempTime/lerpTime));
	//	  playerPoint = bob;
	//	  setPosition();
	// }
	// //for aiming
	// else if(aiming)
	// {
	//	 setCurrentVector(LERP(lastState, XaxisPos*-2.5f + ZaxisNeg*8.5f + Vec3f(0.0f, playerPosition.y + 8.0f, 0.0f), tempTime/lerpTime));
	//	 playerPoint = LERP(playerPosition, bob, tempTime/lerpTime);
	//	 setPosition();
	// }
	// //back to third person
	// else
	// {
	//	  setCurrentVector(LERP(lastState,savedOffset , tempTime/lerpTime)); 
	//	  playerPoint = LERP(bob , playerPosition, tempTime/lerpTime);
	//	  setPosition();
	// }
	// if(tempTime == lerpTime)
	// {
	//	 setLastState(getCurrentVector());
	//	 if(lastState != getCurrentVector())
	//	 {
	//		 cameraClock.restart();
	//	 }
	// }
}

void camera1::updateCamera()
{
	//find frent frame of camera
	ForwardVector = (playerPoint - Vec3f(position.x, -position.y, position.z)).normalize();
	RightVector = ((ForwardVector).cross(Vec3f(0.0f, 1.0f, 0.0f))).normalize();
	UpVector = (RightVector.cross(ForwardVector)).normalize();

	ForwardVector = ForwardVector.negate();
	RightVector = RightVector.negate();
	UpVector = UpVector.negate();
}

Vec3f camera1::getStartingVector ()
{
	return startingVector;
}

Vec3f camera1::getCurrentVector ()
{
	return currentVector;
}
	
Vec3f camera1::getPosition ()
{
	return position;
}