#pragma once
#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE
#include <glm/glm.hpp>
#include <irrKlang.h>
#include "ShaderProgram.h"
#include "TexturedQuad.h"
#include "Quad.h"
#include "Sprite.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

class Credits
{

public:
	Credits();
	~Credits();

	void init();
	void update(int deltaTime);
	void render();
	void stop_sound();

private:
	void initShaders();

	TexturedQuad* game_by[7];
	TexturedQuad *nom1[11], *nom2[10];
	Texture spriteSheet, abecedari;
	Sprite* sprite;
	ShaderProgram textureProgram, textureQuadProgram;
	float currentTime;
	glm::mat4 projection;
	irrklang::ISoundEngine* engine;
	irrklang::ISound* sound;

};

#endif _CREDITS_INCLUDE