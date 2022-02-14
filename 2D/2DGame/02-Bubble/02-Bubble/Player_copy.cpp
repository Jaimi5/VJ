#include "Player_copy.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

glm::ivec2 RealPlayerSize = glm::ivec2(20, 16);
glm::ivec2 RealOffsetToPlayer = glm::ivec2(6, 16);

enum PlayerAnims
{
	STAND_DOWN, STAND_UP, STAND_LEFT, STAND_RIGHT, STAND_UP_LEFT, STAND_UP_RIGHT, STAND_DOWN_LEFT, STAND_DOWN_RIGHT,
	MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, MOVE_UP_LEFT, MOVE_UP_RIGHT, MOVE_DOWN_LEFT, MOVE_DOWN_RIGHT
};

void Player_copy::init(const glm::ivec2& tileMapPos, const glm::ivec2 size, int type, ShaderProgram& shaderProgram)
{
	Player_copy::type = type;
	Player_copy::size = size;
	if (type == Purple_Copy) spritesheet.loadFromFile("images/pj_lila.png", TEXTURE_PIXEL_FORMAT_RGBA);
	else if (type == Red_Copy) spritesheet.loadFromFile("images/pj_rojo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	else if (type == Yellow_Copy) spritesheet.loadFromFile("images/pj_amarillo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(size, glm::vec2(1.f / 18.f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(16);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(1.f / 18.f, 0.25f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(1.f / 18.f, 0.5f));

	sprite->setAnimationSpeed(STAND_UP, 8);
	sprite->addKeyframe(STAND_UP, glm::vec2(1.f / 18.f, 0.75f));

	sprite->setAnimationSpeed(STAND_DOWN, 8);
	sprite->addKeyframe(STAND_DOWN, glm::vec2(1.f / 18.f, 0.f));

	sprite->setAnimationSpeed(STAND_UP_LEFT, 8);
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(4.f / 18.f, 0.5f));

	sprite->setAnimationSpeed(STAND_UP_RIGHT, 8);
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(4.f / 18.f, 0.75f));

	sprite->setAnimationSpeed(STAND_DOWN_LEFT, 8);
	sprite->addKeyframe(STAND_DOWN_LEFT, glm::vec2(4.f / 18.f, 0.f));

	sprite->setAnimationSpeed(STAND_DOWN_RIGHT, 8);
	sprite->addKeyframe(STAND_DOWN_RIGHT, glm::vec2(4.f / 18.f, 0.25f));

	sprite->setAnimationSpeed(MOVE_UP, 8);
	sprite->addKeyframe(MOVE_UP, glm::vec2(6.f / 18.f, 0.75f));
	sprite->addKeyframe(MOVE_UP, glm::vec2(7.f / 18.f, 0.75f));
	sprite->addKeyframe(MOVE_UP, glm::vec2(8.f / 18.f, 0.75f));
	sprite->addKeyframe(MOVE_UP, glm::vec2(9.f / 18.f, 0.75f));
	sprite->addKeyframe(MOVE_UP, glm::vec2(10.f / 18.f, 0.75f));
	sprite->addKeyframe(MOVE_UP, glm::vec2(11.f / 18.f, 0.75f));

	sprite->setAnimationSpeed(MOVE_DOWN, 8);
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(6.f / 18.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(7.f / 18.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(8.f / 18.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(9.f / 18.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(10.f / 18.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(11.f / 18.f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(6.f / 18.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(7.f / 18.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(8.f / 18.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(9.f / 18.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(10.f / 18.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(11.f / 18.f, 0.25f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(6.f / 18.f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(7.f / 18.f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(8.f / 18.f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(9.f / 18.f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(10.f / 18.f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(11.f / 18.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_UP_LEFT, 8);
	sprite->addKeyframe(MOVE_UP_LEFT, glm::vec2(12.f / 18.f, 0.5f));
	sprite->addKeyframe(MOVE_UP_LEFT, glm::vec2(13.f / 18.f, 0.5f));
	sprite->addKeyframe(MOVE_UP_LEFT, glm::vec2(14.f / 18.f, 0.5f));
	sprite->addKeyframe(MOVE_UP_LEFT, glm::vec2(15.f / 18.f, 0.5f));
	sprite->addKeyframe(MOVE_UP_LEFT, glm::vec2(16.f / 18.f, 0.5f));
	sprite->addKeyframe(MOVE_UP_LEFT, glm::vec2(17.f / 18.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_UP_RIGHT, 8);
	sprite->addKeyframe(MOVE_UP_RIGHT, glm::vec2(12.f / 18.f, 0.75f));
	sprite->addKeyframe(MOVE_UP_RIGHT, glm::vec2(13.f / 18.f, 0.75f));
	sprite->addKeyframe(MOVE_UP_RIGHT, glm::vec2(14.f / 18.f, 0.75f));
	sprite->addKeyframe(MOVE_UP_RIGHT, glm::vec2(15.f / 18.f, 0.75f));
	sprite->addKeyframe(MOVE_UP_RIGHT, glm::vec2(16.f / 18.f, 0.75f));
	sprite->addKeyframe(MOVE_UP_RIGHT, glm::vec2(17.f / 18.f, 0.75f));

	sprite->setAnimationSpeed(MOVE_DOWN_LEFT, 8);
	sprite->addKeyframe(MOVE_DOWN_LEFT, glm::vec2(12.f / 18.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN_LEFT, glm::vec2(13.f / 18.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN_LEFT, glm::vec2(14.f / 18.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN_LEFT, glm::vec2(15.f / 18.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN_LEFT, glm::vec2(16.f / 18.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN_LEFT, glm::vec2(17.f / 18.f, 0.f));

	sprite->setAnimationSpeed(MOVE_DOWN_RIGHT, 8);
	sprite->addKeyframe(MOVE_DOWN_RIGHT, glm::vec2(12.f / 18.f, 0.25f));
	sprite->addKeyframe(MOVE_DOWN_RIGHT, glm::vec2(13.f / 18.f, 0.25f));
	sprite->addKeyframe(MOVE_DOWN_RIGHT, glm::vec2(14.f / 18.f, 0.25f));
	sprite->addKeyframe(MOVE_DOWN_RIGHT, glm::vec2(15.f / 18.f, 0.25f));
	sprite->addKeyframe(MOVE_DOWN_RIGHT, glm::vec2(16.f / 18.f, 0.25f));
	sprite->addKeyframe(MOVE_DOWN_RIGHT, glm::vec2(17.f / 18.f, 0.25f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player_copy::update(int deltaTime, int animation, vector<Interactive_element*>* elements, const vector<bool> collisioned)
{
	int velocitat = PlayerVelocity;
	sprite->update(deltaTime);

	if (sprite->animation() != animation)
		sprite->changeAnimation(animation);

	switch (animation)
	{
	case(MOVE_LEFT):
		posPlayer.x -= velocitat;

		if (type != Yellow_Copy && map->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize))
		{
			posPlayer.x += velocitat;
			sprite->changeAnimation(STAND_LEFT);
		}
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat, elements_restants))
				{
					posPlayer.x += velocitat;
					sprite->changeAnimation(STAND_LEFT);
				}
			}
			if (posPlayer.x < 0) posPlayer.x += velocitat;
		}
		break;
	case(MOVE_RIGHT):
		posPlayer.x += velocitat;
		if (type != Yellow_Copy && map->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize))
		{
			posPlayer.x -= velocitat;
			sprite->changeAnimation(STAND_RIGHT);
		}
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat, elements_restants))
				{
					posPlayer.x -= velocitat;
					sprite->changeAnimation(STAND_RIGHT);
				}
			}
			if (posPlayer.x > 550) posPlayer.x -= velocitat;
		}
		break;
	case(MOVE_UP):
		posPlayer.y -= velocitat;
		if (type != Yellow_Copy && map->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize))
		{
			posPlayer.y += velocitat;
			sprite->changeAnimation(STAND_UP);
		}
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat, elements_restants))
				{
					posPlayer.y += velocitat;
					sprite->changeAnimation(STAND_UP);
				}
			}
			if (posPlayer.y < 0) posPlayer.y += velocitat;
		}
		break;
	case(MOVE_DOWN):
		posPlayer.y += velocitat;
		if (type != Yellow_Copy && map->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize))
		{
			posPlayer.y -= velocitat;
			sprite->changeAnimation(STAND_DOWN);
		}
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat, elements_restants))
				{
					posPlayer.y -= velocitat;
					sprite->changeAnimation(STAND_DOWN);
				}
			}
			if (posPlayer.y > 430) posPlayer.y -= velocitat;
		}
		break;
	case(MOVE_UP_LEFT):
		posPlayer.x -= velocitat/2;
		if (collisioned[0]) posPlayer.x += velocitat / 2;
		else if (type != Yellow_Copy && map->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize)) posPlayer.x += velocitat / 2;
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat / 2, elements_restants)) posPlayer.x += velocitat / 2;
			}
			if (posPlayer.x < 0) posPlayer.x += velocitat / 2;
		}

		posPlayer.y -= velocitat / 2;
		if (collisioned[2]) posPlayer.y += velocitat / 2;
		else if (type != Yellow_Copy && map->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize)) posPlayer.y += velocitat / 2;
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat / 2, elements_restants)) posPlayer.y += velocitat / 2;
			}
			if (posPlayer.y < 0) posPlayer.y += velocitat / 2;
		}
		break;
	case(MOVE_DOWN_LEFT):
		posPlayer.x -= velocitat / 2;
		if (collisioned[0]) posPlayer.x += velocitat / 2;
		else if (type != Yellow_Copy && map->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize)) posPlayer.x += velocitat / 2;
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat / 2, elements_restants)) posPlayer.x += velocitat / 2;
			}
		}
		if (posPlayer.x < 0) posPlayer.x += velocitat / 2;

		posPlayer.y += velocitat / 2;
		if (collisioned[3]) posPlayer.y -= velocitat / 2;
		else if (type != Yellow_Copy && map->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize)) posPlayer.y -= velocitat / 2;
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat / 2, elements_restants)) posPlayer.y -= velocitat / 2;
			}
			if (posPlayer.y > 430) posPlayer.y -= velocitat / 2;
		}
		break;
	case(MOVE_UP_RIGHT):
		posPlayer.x += velocitat / 2;
		if (collisioned[1]) posPlayer.x -= velocitat / 2;
		else if (type != Yellow_Copy && map->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize)) posPlayer.x -= velocitat / 2;
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat / 2, elements_restants)) posPlayer.x -= velocitat / 2;
			}
			if (posPlayer.x > 550) posPlayer.x -= velocitat / 2;
		}

		posPlayer.y -= velocitat / 2;
		if (collisioned[2]) posPlayer.y += velocitat / 2;
		else if (type != Yellow_Copy && map->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize)) posPlayer.y += velocitat / 2;
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat / 2, elements_restants)) posPlayer.y += velocitat / 2;
			}
			if (posPlayer.y < 0) posPlayer.y += velocitat / 2;
		}
		break;
	case(MOVE_DOWN_RIGHT):
		posPlayer.x += velocitat / 2;
		if (collisioned[1]) posPlayer.x -= velocitat / 2;
		else if (type != Yellow_Copy && map->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize)) posPlayer.x -= velocitat / 2;
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat / 2, elements_restants)) posPlayer.x -= velocitat / 2;
			}
			if (posPlayer.x > 550) posPlayer.x -= velocitat / 2;
		}

		posPlayer.y += velocitat / 2;
		if (collisioned[3]) posPlayer.y -= velocitat / 2;
		else if (type != Yellow_Copy && map->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize))
			posPlayer.y -= velocitat / 2;
		else
		{
			for (int i = 0; i < elements->size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements->size(); j++)
				{
					if (j != i) elements_restants.push_back(elements->at(j));
				}
				if (elements->at(i)->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat / 2, elements_restants)) posPlayer.y -= velocitat / 2;
			}
			if (posPlayer.y > 430) posPlayer.y -= velocitat / 2;
		}
		break;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player_copy::render()
{
	sprite->render();
}

void Player_copy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Player_copy::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Player_copy::GetType()
{
	return type;
}

glm::ivec2 Player_copy::GetPos()
{
	return posPlayer;
}

glm::ivec2 Player_copy::GetSize()
{
	return size;
}
