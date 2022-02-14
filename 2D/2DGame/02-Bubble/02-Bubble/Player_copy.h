#pragma once
#ifndef _PCOPY_INCLUDE
#define _PCOPY_INCLUDE

#include <vector>
#include "Sprite.h"
#include "TileMap.h"
#include "Interactive_element.h"

class Player_copy
{

public:

	enum EnumCopy
	{
		Purple_Copy, Red_Copy, Yellow_Copy
	};

	void init(const glm::ivec2& tileMapPos, glm::ivec2 size, int type, ShaderProgram& shaderProgram);
	void update(int deltaTime, int animation, vector<Interactive_element*>* elements, const vector<bool> collisioned);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	int GetType();
	glm::ivec2 GetPos();
	glm::ivec2 GetSize();
	int PlayerVelocity = 2;

private:
	int type;
	glm::ivec2 tileMapDispl, posPlayer, size;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	glm::ivec2 RealPlayerSize = glm::ivec2(20, 16);
	glm::ivec2 RealOffsetToPlayer = glm::ivec2(6, 16);
};
#endif _PCOPY_INCLUDE