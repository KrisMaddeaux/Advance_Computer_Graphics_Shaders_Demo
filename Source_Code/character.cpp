#include "character.h"

character::character()
{

		species = 0;

		health = 0;

		alive = true;

		theta = 0.0f;
		position = Vec3f(0.0f, 0.0f, 0.0f);
		startingPosition = Vec3f(0.0f,0.0f,0.0f);
		tValue = 0.f;

		speed = 1.0f;

		ZaxisPos = Vec3f(0.0f, 0.0f, 1.0f);		//front of the character
		ZaxisNeg = Vec3f(0.0f, 0.0f, -1.0f);		//back of the character

		XaxisNeg = Vec3f(-1.0f, 0.0f, 0.0f);			//left of the character
		XaxisPos = Vec3f(1.0f, 0.0f, 0.0f);			//right of the character

		flipNegXAxis = false;
		flipPosXAxis = false;
		flipPosZAxis = false;
		flipNegZAxis = false;

		accumulatedTime = 0.f;
		waitTime = 0.f;

		modelMat = Identity();
}



character::character(bool isAlive, int hitpoints, Vec3f Cposition, float angle, int Cspecies, Vec3f CstartingPosition)
{

	species = Cspecies;

	health = hitpoints;

	alive = isAlive;

	theta = 0.0f;
	position = Vec3f();
	startingPosition = Vec3f();
	tValue = 0.f;
	deltaTime = 0.f;

	ZaxisPos = Vec3f(0.0f, 0.0f, 1.0f);		//front of the character
	ZaxisNeg = Vec3f(0.0f, 0.0f, -1.0f);		//back of the character

	XaxisNeg = Vec3f(-1.0f, 0.0f, 0.0f);			//left of the character
	XaxisPos = Vec3f(1.0f, 0.0f, 0.0f);			//right of the character

	flipNegXAxis = false;
	flipPosXAxis = false;
	flipPosZAxis = false;
	flipNegZAxis = false;

	accumulatedTime = 0.f;
	waitTime = 0.f;
}

character::~character()
{
	//destructor
	//delete theTexture1;
	//delete theModel;
}

void character::loadCharacter(tex *importedTex, char* modelFileName, int polyCount)
{
	theModel = new objLoader();

	theTexture1 = importedTex; 
	theModel->LoadOBJ(modelFileName, polyCount, true);
}

void character::drawCharacter(cbmini::cbfw::GLSLProgram *ShaderProgram, camera1 camera)
{
	updateCharacter(camera); 
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->GetHandle(), "modelMat"), 1, 1, modelMat.m);
	//glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->GetHandle(), "modelViewProjectionMat"), 1, 1, modelViewProjectionMat.m);
	//glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->GetHandle(), "modelViewMat"), 1, 1, modelViewMat.m);
	theTexture1->drawTex(0);
	theModel->drawModel();
}

void character::updateCharacter(camera1 camera)
{
	Mat4f r = RotateY(theta);

	modelMat = makeTransform(r, Scale(0.6f, 0.6f, 0.6f), Vec3f(position.x, position.y - 8.0f, position.z));

	//modelViewMat = camera.viewMat * modelMat;

	//modelViewProjectionMat = camera.projectionMat * modelViewMat; 

}

void character::calcAxis()
{
	//rotation for x axis
	//using quaternions
	//using QvQ^c formula
	//first we must figure out the rotation quaternion and its conjucate
	Quat rotateQuat = rotationQuat(theta, Vec3f(0, 1, 0));
	Quat conjugate = rotateQuat.conjugate();

	//next we find the new direction vector by rotation it
	Quat newQuatPosX = rotateQuat * Quat(0, 1, 0, 0) * conjugate;
	Quat newQuatNegX = rotateQuat * Quat(0, -1, 0, 0) * conjugate; 
	Quat newQuatPosZ = rotateQuat * Quat(0, 0, 0, 1) * conjugate;
	Quat newQuatNegZ = rotateQuat * Quat(0, 0, 0, -1) * conjugate;

	//transfer our direction vector from pure quaternion to vector form
	Vec3f newVecPosX = newQuatPosX.toVector();
	Vec3f newVecNegX = newQuatNegX.toVector();
	Vec3f newVecPosZ = newQuatPosZ.toVector();
	Vec3f newVecNegZ = newQuatNegZ.toVector();

	//finally normalize the vectors to make sure they are direction vectors
	/*XaxisPos = (newVecPosX.normalize());
	XaxisNeg = (newVecNegX.normalize());
	ZaxisPos = (newVecPosZ.normalize());
	ZaxisNeg = (newVecNegZ.normalize());*/

	XaxisPos = newVecPosX;
	XaxisNeg = newVecNegX;
	ZaxisPos = newVecPosZ;
	ZaxisNeg = newVecNegZ;
}


void character::loadAnimations()
{
}

void character::updateAnimations(float dt)
{
}