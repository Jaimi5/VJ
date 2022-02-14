#pragma once
#ifndef _INST_INCLUDE
#define _INST_INCLUDE
#include <vector>
#include <glm/glm.hpp>
#include <irrKlang.h>
#include "ShaderProgram.h"
#include "TexturedQuad.h"
#include "Quad.h"
#include "Sprite.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

class Instructions
{
	enum EnumPage
	{
		MAIN_RULES, PURPLE_COPY, RED_COPY, YELLOW_COPY
	};

public:
	Instructions();
	~Instructions();

	void init(int page);
	void update(int deltaTime);
	void render();

private:
	void initShaders();

	int page;
	bool once[2];
	TexturedQuad* background;
	vector<TexturedQuad*> elements;
	vector<Texture> image_background;
	vector<Texture> images_elems;
	ShaderProgram textureProgram, textureQuadProgram;
	float currentTime;
	glm::mat4 projection;
	irrklang::ISoundEngine* engine;
	irrklang::ISound* sound;

};

#endif _INST_INCLUDE