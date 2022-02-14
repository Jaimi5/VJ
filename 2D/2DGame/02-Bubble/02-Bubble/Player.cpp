#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <algorithm>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

Player::~Player()
{
	for (int i = 0; i < sounds.size(); i++) sounds[i]->drop();
	engine->drop();
}

enum PlayerAnims
{
	STAND_DOWN, STAND_UP, STAND_LEFT, STAND_RIGHT, STAND_UP_LEFT, STAND_UP_RIGHT, STAND_DOWN_LEFT, STAND_DOWN_RIGHT,
	MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, MOVE_UP_LEFT, MOVE_UP_RIGHT, MOVE_DOWN_LEFT, MOVE_DOWN_RIGHT, VICTORY
};


void Player::init(const glm::ivec2& tileMapPos, const glm::ivec2 size, ShaderProgram& shaderProgram)
{
	bJumping = false;
	Player::size = size;
	spritesheet.loadFromFile("images/pj.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(size, glm::vec2(1.f / 18.f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(17);

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

	sprite->setAnimationSpeed(VICTORY, 8);
	sprite->addKeyframe(VICTORY, glm::vec2(1.f / 18.f, 0.f));
	sprite->addKeyframe(VICTORY, glm::vec2(1.f / 18.f, 0.25f));
	sprite->addKeyframe(VICTORY, glm::vec2(1.f / 18.f, 0.75f));
	sprite->addKeyframe(VICTORY, glm::vec2(1.f / 18.f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	engine = irrklang::createIrrKlangDevice();
	//engine->setSoundVolume(1.f);
	sounds = vector<irrklang::ISound*>(3); // TODO //
	sounds[0] = engine->play2D("sounds/Walking.mp3", true, true, true);
	sounds[0]->setVolume(0.5f);
	sounds[1] = engine->play2D("sounds/hit_wall_1.mp3", false, true, true);
	sounds[2] = engine->play2D("sounds/hit_wall_2.mp3", false, true, true);

	//[0] = caminar
	//[1] = collision sound 1
	//[2] = collision sound 2
}

void Player::update(int deltaTime)
{

	int velocitat = PlayerVelocity;
	if (sounds[1]->isFinished())
	{
		sounds[1] = engine->play2D("sounds/hit_wall_1.mp3", false, true, true);
	}
	if (sounds[2]->isFinished())
	{
		sounds[2] = engine->play2D("sounds/hit_wall_2.mp3", false, true, true);
	}

	sprite->update(deltaTime);
	vector<bool> collisioned(4, false); // left, right, up, down

	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (!Game::instance().getSpecialKey(GLUT_KEY_UP) && !Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		{
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);

			posPlayer.x -= velocitat;
			if (map->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize))
			{
				posPlayer.x += velocitat;
				sprite->changeAnimation(STAND_LEFT);
				collisioned[0] = true;
			}
			else
			{
				for (int i = 0; i < elements.size(); i++)
				{
					vector<Interactive_element*> elements_restants;
					for (int j = 0; j < elements.size(); j++)
					{
						if (j != i) elements_restants.push_back(elements[j]);
					}
					if (elements[i]->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat, elements_restants))
					{
						posPlayer.x += velocitat;
						sprite->changeAnimation(STAND_LEFT);
						collisioned[0] = true;
						break;
					}
				}
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
		{
			if (sprite->animation() != MOVE_UP_LEFT)
				sprite->changeAnimation(MOVE_UP_LEFT);

			posPlayer.x -= velocitat / 2;
			if (map->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize))
			{
				collisioned[0] = true;
				posPlayer.x += velocitat / 2;
			}
			else
			{
				for (int i = 0; i < elements.size(); i++)
				{
					vector<Interactive_element*> elements_restants;
					for (int j = 0; j < elements.size(); j++)
					{
						if (j != i) elements_restants.push_back(elements[j]);
					}
					if (elements[i]->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat / 2, elements_restants))
					{
						collisioned[0] = true;
						posPlayer.x += velocitat / 2;
						break;
					}
				}
			}

			posPlayer.y -= velocitat / 2;
			if (map->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize))
			{
				collisioned[2] = true;
				posPlayer.y += velocitat / 2;
			}
			else
			{
				for (int i = 0; i < elements.size(); i++)
				{
					vector<Interactive_element*> elements_restants;
					for (int j = 0; j < elements.size(); j++)
					{
						if (j != i) elements_restants.push_back(elements[j]);
					}
					if (elements[i]->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat / 2, elements_restants))
					{
						collisioned[2] = true;
						posPlayer.y += velocitat / 2;
						break;
					}
				}
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		{
			if (sprite->animation() != MOVE_DOWN_LEFT)
				sprite->changeAnimation(MOVE_DOWN_LEFT);

			posPlayer.x -= velocitat / 2;
			if (map->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize))
			{
				collisioned[0] = true;
				posPlayer.x += velocitat / 2;
			}
			else
			{
				for (int i = 0; i < elements.size(); i++)
				{
					vector<Interactive_element*> elements_restants;
					for (int j = 0; j < elements.size(); j++)
					{
						if (j != i) elements_restants.push_back(elements[j]);
					}
					if (elements[i]->collisionMoveLeft(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat / 2, elements_restants))
					{
						collisioned[0] = true;
						posPlayer.x += velocitat / 2;
						break;
					}
				}
			}

			posPlayer.y += velocitat / 2;
			if (map->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize))
			{
				collisioned[3] = true;
				posPlayer.y -= velocitat / 2;
			}
			else
			{
				for (int i = 0; i < elements.size(); i++)
				{
					vector<Interactive_element*> elements_restants;
					for (int j = 0; j < elements.size(); j++)
					{
						if (j != i) elements_restants.push_back(elements[j]);
					}
					if (elements[i]->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat / 2, elements_restants))
					{
						collisioned[3] = true;
						posPlayer.y -= velocitat / 2;
						break;
					}
				}
			}
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (!Game::instance().getSpecialKey(GLUT_KEY_UP) && !Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		{
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);

			posPlayer.x += velocitat;
			if (map->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize))
			{
				posPlayer.x -= velocitat;
				sprite->changeAnimation(STAND_RIGHT);
				collisioned[1] = true;
			}
			else
			{
				for (int i = 0; i < elements.size(); i++)
				{
					vector<Interactive_element*> elements_restants;
					for (int j = 0; j < elements.size(); j++)
					{
						if (j != i) elements_restants.push_back(elements[j]);
					}
					if (elements[i]->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat, elements_restants))
					{
						posPlayer.x -= velocitat;
						sprite->changeAnimation(STAND_RIGHT);
						collisioned[1] = true;
						break;
					}
				}
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
		{
			if (sprite->animation() != MOVE_UP_RIGHT)
				sprite->changeAnimation(MOVE_UP_RIGHT);

			posPlayer.x += velocitat / 2;
			if (map->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize))
			{
				collisioned[1] = true;
				posPlayer.x -= velocitat / 2;
			}
			else
			{
				for (int i = 0; i < elements.size(); i++)
				{
					vector<Interactive_element*> elements_restants;
					for (int j = 0; j < elements.size(); j++)
					{
						if (j != i) elements_restants.push_back(elements[j]);
					}
					if (elements[i]->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat / 2, elements_restants))
					{
						collisioned[1] = true;
						posPlayer.x -= velocitat / 2;
						break;
					}
				}
			}

			posPlayer.y -= velocitat / 2;
			if (map->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize))
			{
				collisioned[2] = true;
				posPlayer.y += velocitat / 2;
			}
			else
			{
				for (int i = 0; i < elements.size(); i++)
				{
					vector<Interactive_element*> elements_restants;
					for (int j = 0; j < elements.size(); j++)
					{
						if (j != i) elements_restants.push_back(elements[j]);
					}
					if (elements[i]->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat / 2, elements_restants))
					{
						collisioned[2] = true;
						posPlayer.y += velocitat / 2;
						break;
					}
				}
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		{
			if (sprite->animation() != MOVE_DOWN_RIGHT)
				sprite->changeAnimation(MOVE_DOWN_RIGHT);

			posPlayer.x += velocitat / 2;
			if (map->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize))
			{
				collisioned[1] = true;
				posPlayer.x -= velocitat / 2;
			}
			else
			{
				for (int i = 0; i < elements.size(); i++)
				{
					vector<Interactive_element*> elements_restants;
					for (int j = 0; j < elements.size(); j++)
					{
						if (j != i) elements_restants.push_back(elements[j]);
					}
					if (elements[i]->collisionMoveRight(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat / 2, elements_restants))
					{
						collisioned[1] = true;
						posPlayer.x -= velocitat / 2;
						break;
					}
				}
			}

			posPlayer.y += velocitat / 2;
			if (map->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize))
			{
				collisioned[3] = true;
				posPlayer.y -= velocitat / 2;
			}
			else
			{
				for (int i = 0; i < elements.size(); i++)
				{
					vector<Interactive_element*> elements_restants;
					for (int j = 0; j < elements.size(); j++)
					{
						if (j != i) elements_restants.push_back(elements[j]);
					}
					if (elements[i]->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat / 2, elements_restants))
					{
						collisioned[3] = true;
						posPlayer.y -= velocitat / 2;
						break;
					}
				}
			}
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (sprite->animation() != MOVE_UP)
			sprite->changeAnimation(MOVE_UP);

		posPlayer.y -= velocitat;
		if (map->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize))
		{
			posPlayer.y += velocitat;
			sprite->changeAnimation(STAND_UP);
			collisioned[2] = true;
		}
		else
		{
			for (int i = 0; i < elements.size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements.size(); j++)
				{
					if (j != i) elements_restants.push_back(elements[j]);
				}
				if (elements[i]->collisionMoveUp(posPlayer + RealOffsetToPlayer, RealPlayerSize, -velocitat, elements_restants))
				{
					posPlayer.y += velocitat;
					sprite->changeAnimation(STAND_UP);
					collisioned[2] = true;
					break;
				}
			}
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);

		posPlayer.y += velocitat;
		if (map->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize))
		{
			posPlayer.y -= velocitat;
			sprite->changeAnimation(STAND_DOWN);
			collisioned[3] = true;
		}
		else
		{
			for (int i = 0; i < elements.size(); i++)
			{
				vector<Interactive_element*> elements_restants;
				for (int j = 0; j < elements.size(); j++)
				{
					if (j != i) elements_restants.push_back(elements[j]);
				}
				if (elements[i]->collisionMoveDown(posPlayer + RealOffsetToPlayer, RealPlayerSize, velocitat, elements_restants))
				{
					posPlayer.y -= velocitat;
					sprite->changeAnimation(STAND_DOWN);
					collisioned[3] = true;
					break;
				}
			}
		}
	}
	else
	{
		switch (sprite->animation()) {
		case MOVE_LEFT:
			sprite->changeAnimation(STAND_LEFT);
			break;
		case MOVE_RIGHT:
			sprite->changeAnimation(STAND_RIGHT);
			break;
		case MOVE_UP:
			sprite->changeAnimation(STAND_UP);
			break;
		case MOVE_DOWN:
			sprite->changeAnimation(STAND_DOWN);
			break;
		case MOVE_UP_LEFT:
			sprite->changeAnimation(STAND_UP_LEFT);
			break;
		case MOVE_UP_RIGHT:
			sprite->changeAnimation(STAND_UP_RIGHT);
			break;
		case MOVE_DOWN_LEFT:
			sprite->changeAnimation(STAND_DOWN_LEFT);
			break;
		case MOVE_DOWN_RIGHT:
			sprite->changeAnimation(STAND_DOWN_RIGHT);
			break;
		}
	}

	if (sprite->animation() == MOVE_UP_LEFT && collisioned[0] && collisioned[2]) sprite->changeAnimation(STAND_UP_LEFT);
	else if (sprite->animation() == MOVE_UP_RIGHT && collisioned[1] && collisioned[2]) sprite->changeAnimation(STAND_UP_RIGHT);
	else if (sprite->animation() == MOVE_DOWN_LEFT && collisioned[0] && collisioned[3]) sprite->changeAnimation(STAND_DOWN_LEFT);
	else if (sprite->animation() == MOVE_DOWN_RIGHT && collisioned[1] && collisioned[3]) sprite->changeAnimation(STAND_DOWN_RIGHT);

	for (int i = 0; i < copies.size(); i++) copies[i]->update(deltaTime, sprite->animation(), &elements, collisioned);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	if (sprite->animation() != STAND_DOWN && sprite->animation() != STAND_UP &&
		sprite->animation() != STAND_LEFT && sprite->animation() != STAND_RIGHT &&
		sprite->animation() != STAND_UP_RIGHT && sprite->animation() != STAND_UP_LEFT &&
		sprite->animation() != STAND_DOWN_RIGHT && sprite->animation() != STAND_DOWN_LEFT)
	{
		if (sounds[0]->getIsPaused())
		{
			sounds[0]->setPlayPosition(0);
			sounds[0]->setIsPaused(false);
		}
	}
	else if (!sounds[0]->getIsPaused())
		sounds[0]->setIsPaused(true);

	if (any_of(collisioned.begin(), collisioned.end(), [&](bool i) { return i; }))
	{
		if (sounds[2]->getIsPaused() && !hit)
		{
			sounds[1]->setIsPaused(false);
			hit = true;
		}
		else if (sounds[1]->getIsPaused() && hit)
		{
			sounds[2]->setIsPaused(false);
			hit = false;
		}
	}

}

void Player::SetWinAnimation(int deltaTime, int currentTime) {
	sprite->update(deltaTime);
	if (sprite->animation() != VICTORY) {
		for (int i = 0; i < sounds.size(); i++) {
			if (!sounds[i]->getIsPaused())
				sounds[i]->setIsPaused();
		}
		sprite->changeAnimation(VICTORY);
		AnimationWinLoop = currentTime + 700;
	}
	else if (currentTime > AnimationWinLoop)
		sprite->changeAnimation(STAND_DOWN);
}

bool Player::WinAnimationFinished() {
	return sprite->animation() != VICTORY;
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Player::setElement(vector<Interactive_element*>& elements)
{
	Player::elements = elements;
}

void Player::setCopies(vector<Player_copy*>& copies)
{
	Player::copies = copies;
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Player::getPosition()
{
	return posPlayer;
}

glm::ivec2 Player::getSize()
{
	return size;
}


