#pragma once
#include "Include\GL\glew.h"
#include "Include\CBMini\CBMiniFW.h"
#include "Include/SFML/Graphics.hpp"

class tex
{
public:
	tex();
	~tex();
	
	sf::Image texMap;
	GLuint texture;
	void loadTex(const std::string &filename);
	void drawTex(int ID);
};
