#include "texture.h"

tex::tex()
{
}

tex::~tex()
{
}

void tex::loadTex(const std::string &filename)
{
	if(!texMap.loadFromFile(filename))
	{
		//The image didn't load, close the program!
		return;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texMap.getSize().x, texMap.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, texMap.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //linear to nearest
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // GL_LINEAR_MIPMAP_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void tex::drawTex(int ID)
{
	if(ID < 31)
	{
		glActiveTexture(GL_TEXTURE0 + ID);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
}