#pragma once
#ifndef _INT_INCLUDE
#define _INT_INCLUDE

#include <vector>
#include "Texture.h"
#include "TexturedQuad.h"
#include "Sprite.h"
#include "TileMap.h"

class Interactive_element
{

public:

	enum EnumElement
	{
		Quadrat_Lila, Quadrat_Vermell, Quadrat_Groc, Gate, Silver_Key_First, Silver_Key_Second, Silver_Key, Lava_Floor, Purple_Key_First, Purple_Key_Second, Purple_Key, Red_Key_First, Red_Key_Second, Red_Key, Yellow_Key_First, Yellow_Key_Second, Yellow_Key, Coin
	};

	Interactive_element();
	~Interactive_element();

	void init(const glm::ivec2& tileMapPos, ShaderProgram* shaderProgram, const int type, glm::vec2 block_size);
	void update(int deltaTime);
	void render();

	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, const int movement, vector<Interactive_element*> elements_restants);
	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size, const int movement, vector<Interactive_element*> elements_restants);
	bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, const int movement, vector<Interactive_element*> elements_restants);
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, const int movement, vector<Interactive_element*> elements_restants);

	glm::ivec2 getSize();
	glm::ivec2 getPosition();

	void setPosition(const glm::ivec2& pos);
	void setTileMap(TileMap* tileMap);
	int GetType();
	void ChangeGate(ShaderProgram& shaderProgram, bool open);
	//bool CanChangeType();
	bool IsInsideElement(const glm::ivec2 PlayerPosition, const glm::ivec2 PlayerSize);



private:
	int type;
	bool IsCollisionable;
	//bool ChangeType; BASURA
	glm::ivec2 tileMapDispl, position, size;
	Texture image;
	TexturedQuad* block;
	Sprite* sprite;
	ShaderProgram* textureQuadProgram;
	TileMap *map;
	glm::mat4 projection;

};

#endif _INT_INCLUDE