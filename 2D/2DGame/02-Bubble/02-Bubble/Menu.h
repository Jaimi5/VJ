#pragma once
#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TexturedQuad.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

class Menu
{
public:
	Menu();
	~Menu();

	void init();
	void render();

private:
	void initShaders();

private:
	Texture image_background, abecedari;
	TexturedQuad* background;
	TexturedQuad* lletra[9];
	ShaderProgram  textureProgram;
	glm::mat4 projection;

};

#endif _MENU_INCLUDE