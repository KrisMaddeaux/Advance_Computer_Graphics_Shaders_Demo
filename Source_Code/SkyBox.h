#pragma once
#include "Include\CBMini\CBMiniFW.h"
#include "texture.h"
#include "MathClass.h"
#include "player.h"

class SkyBox
{
public:
	SkyBox()
	{
		pos = Vec3f();
		scale = 1.0f;
	}
	SkyBox(Vec3f Pos)
	{
		pos = Pos;
		scale = 250.0f;

	}
	~SkyBox(){}

	void initSkyBox()
	{
		/*SkyTex[0] = new tex();
		SkyTex[0]->loadTex("Images/SkyBox/sky_blue.jpg");
		SkyTex[1] = new tex();
		SkyTex[1]->loadTex("Images/SkyBox/sky_blue.jpg");
		SkyTex[2] = new tex();
		SkyTex[2]->loadTex("Images/SkyBox/sky_blue.jpg");
		SkyTex[3] = new tex();
		SkyTex[3]->loadTex("Images/SkyBox/sky_blue.jpg");
		SkyTex[4] = new tex();
		SkyTex[4]->loadTex("Images/SkyBox/sky_blue2.jpg");*/

		prevModelMat = Identity();
	}

	void drawSkyBox(cbmini::cbfw::GLSLProgram *shader)
	{
		//glDisable(GL_FOG);
		glDisable(GL_LIGHTING);
		glDepthMask(false);

		glPushMatrix();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		//glTranslatef(pos.x, pos.y, pos.z);
		modelMat = Translate(pos.x, pos.y, pos.z);
		glUniformMatrix4fv(glGetUniformLocation(shader->GetHandle(), "modelMat"), 1, 1, modelMat.m);
		glUniformMatrix4fv(glGetUniformLocation(shader->GetHandle(), "prevModelMat"), 1, 1, prevModelMat.m);
		glUniform1f(glGetUniformLocation(shader->GetHandle(), "enableLight"), 0.0f); //false 

		//back
		//SkyTex[0]->drawTex(0);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(scale,-scale,-scale);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(scale,scale,-scale);	
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-scale,scale,-scale);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-scale,-scale,-scale);
		glEnd();
		

		//front 
		//SkyTex[1]->drawTex(0);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-scale,-scale,scale);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-scale,scale,scale);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(scale,scale,scale);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(scale,-scale,scale);
		glEnd();
	
		//left side
		//SkyTex[2]->drawTex(0);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(scale,scale,scale);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(scale,scale,-scale);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(scale,-scale,-scale);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(scale,-scale,scale);
		glEnd();
	

		//right side
		//SkyTex[3]->drawTex(0);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-scale,scale,-scale);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-scale,scale,scale);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-scale,-scale,scale);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-scale,-scale,-scale);
		glEnd();

		//top side
		//SkyTex[4]->drawTex(0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-scale,scale,-scale);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(scale,scale,-scale);	
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(scale,scale,scale);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-scale,scale,scale);
		glEnd();
	
	
		////bottom side
		//glVertex3f(-scale/2,-scale/2,-scale/2);
		//glVertex3f(scale/2,-scale/2,-scale/2);
		//glVertex3f(scale/2,-scale/2,-scale/2);
		//glVertex3f(-scale/2,-scale/2,scale/2);


		glPopMatrix();
		//glEnable(GL_FOG);
		glEnable(GL_LIGHTING);
		glDepthMask(true);

		prevModelMat = modelMat; 
	}

	void updateSkyBox(Vec3f playerPos)
	{
		pos = playerPos; 
	}

	Vec3f pos;
	float scale;

	Mat4f modelMat;
	Mat4f prevModelMat; 

	tex *SkyTex[6]; 
};

