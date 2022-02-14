#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Interactive_element.h"

Interactive_element::Interactive_element()
{
	block = NULL;
	textureQuadProgram = NULL;
	sprite = NULL;
}

Interactive_element::~Interactive_element()
{
	//if (block != NULL) delete block;
}

void Interactive_element::init(const glm::ivec2& tileMapPos, ShaderProgram* shaderProgram, const int type, glm::vec2 block_size)
{
	Interactive_element::type = type;
	Interactive_element::size.x = block_size.x;
	Interactive_element::size.y = block_size.y;
	Interactive_element::textureQuadProgram = shaderProgram;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(size) };
	if (type == Quadrat_Lila)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(2.f * 1.f / 8.f, 2.f * 1.f / 6.f), glm::vec2(3.f * 1.f / 8.f,3.f * 1.f / 6.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/tiles_floor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Gate)
	{
		IsCollisionable = false;
		glm::vec2 texCoords[2] = { glm::vec2(11.f * 1.f / 13.f, 0.f * 1.f / 1.f), glm::vec2(13.f * 1.f / 13.f, 2.f * 1.f / 7.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/spr_Greenlands_orth_0.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Silver_Key_First)
	{
		//First Part of the silver Key
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(6.f * 1.f / 8.f, 0.f * 1.f / 2.f), glm::vec2(7.f * 1.f / 8.f, 2.f * 1.f / 2.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Silver_Key_Second)
	{
		//Second part of silver Key
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(7.f * 1.f / 8.f, 0.f * 1.f / 2.f), glm::vec2(8.f * 1.f / 8.f, 2.f * 1.f / 2.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Silver_Key)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(3.f * 1.f / 4.f, 0.f * 1.f / 2.f), glm::vec2(4.f * 1.f / 4.f, 2.f * 1.f / 2.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Purple_Key_First)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(0.f * 1.f / 8.f, 0.f), glm::vec2(1.f * 1.f / 8.f, 1.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Purple_Key_Second)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(1.f * 1.f / 8.f, 0.f), glm::vec2(2.f * 1.f / 8.f, 1.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Purple_Key)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(0.f * 1.f / 4.f, 0.f * 1.f / 2.f), glm::vec2(1.f * 1.f / 4.f, 2.f * 1.f / 2.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Red_Key_First)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(2.f * 1.f / 8.f, 0.f), glm::vec2(3.f * 1.f / 8.f, 1.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Red_Key_Second)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(3.f * 1.f / 8.f, 0.f), glm::vec2(4.f * 1.f / 8.f, 1.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Red_Key)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(1.f * 1.f / 4.f, 0.f * 1.f / 2.f), glm::vec2(2.f * 1.f / 4.f, 2.f * 1.f / 2.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Yellow_Key_First)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(4.f * 1.f / 8.f, 0.f), glm::vec2(5.f * 1.f / 8.f, 1.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Yellow_Key_Second)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(5.f * 1.f / 8.f, 0.f), glm::vec2(6.f * 1.f / 8.f, 1.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Yellow_Key)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(2.f * 1.f / 4.f, 0.f * 1.f / 2.f), glm::vec2(3.f * 1.f / 4.f, 2.f * 1.f / 2.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Quadrat_Vermell)
	{
		IsCollisionable = true;
		glm::vec2 texCoords[2] = { glm::vec2(4.f * 1.f / 8.f, 5.f * 1.f / 6.f), glm::vec2(5.f * 1.f / 8.f, 6.f * 1.f / 6.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/tiles_floor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Quadrat_Groc)
	{
	IsCollisionable = true;
	glm::vec2 texCoords[2] = { glm::vec2(2.f * 1.f / 8.f, 1.f * 1.f / 6.f), glm::vec2(3.f * 1.f / 8.f, 2.f * 1.f / 6.f) };
	block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
	image.loadFromFile("images/tiles_floor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Lava_Floor) {
		IsCollisionable = false;
		glm::vec2 texCoords[2] = { glm::vec2(0.f * 1.f / 8.f, 5.f * 1.f / 6.f), glm::vec2(1.f * 1.f / 8.f, 6.f * 1.f / 6.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, *textureQuadProgram);
		image.loadFromFile("images/tiles_floor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == Coin) {
		IsCollisionable = false;
		image.loadFromFile("images/coin.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(size, glm::vec2(1.f / 6.f, 1.f), &image, textureQuadProgram);
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f / 6.f, 0.f));
		sprite->addKeyframe(0, glm::vec2(1.f / 6.f, 0.f));
		sprite->addKeyframe(0, glm::vec2(2.f / 6.f, 0.f));
		sprite->addKeyframe(0, glm::vec2(3.f / 6.f, 0.f));
		sprite->addKeyframe(0, glm::vec2(4.f / 6.f, 0.f));
		sprite->addKeyframe(0, glm::vec2(5.f / 6.f, 0.f));
		sprite->changeAnimation(0);
	}

	Interactive_element::tileMapDispl = tileMapPos;
}

bool Interactive_element::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size, const int movement, vector<Interactive_element*> elements_restants)
{
	int x0, x1, y0, y1, initialX;

	initialX = position.x;

	x0 = pos.x;
	x1 = (pos.x + size.x);
	y0 = pos.y;
	y1 = (pos.y + size.y);

	if ((x0 < position.x) && (x1 >= position.x) && (((y0 >= position.y) && (y0 <= position.y + Interactive_element::size.y)) || ((y1 <= position.y + Interactive_element::size.y) && (y1 >= position.y)) || ((y0 < position.y) && (y1 > position.y + Interactive_element::size.y)) || ((y0 > position.y) && (y1 < position.y + Interactive_element::size.y))))
	{
		if (IsCollisionable) {
			position.x += movement;
			if (map->collisionMoveRight(position, this->size)) {
				position.x = initialX;
				return true;
			}

			for (int i = 0; i < elements_restants.size(); i++)
			{
				vector<Interactive_element*> elements_restants2;
				for (int j = 0; j < elements_restants.size(); j++)
				{
					if (j != i) elements_restants2.push_back(elements_restants[j]);
				}
				if (elements_restants[i]->collisionMoveRight(this->getPosition(), this->getSize(), movement, elements_restants2)) {
					position.x = initialX;
					return true;
				}
			}
		}
	}
	return false;
}

bool Interactive_element::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size, const int movement, vector<Interactive_element*> elements_restants)
{
	int x0, x1, y0, y1, initialX;

	initialX = position.x;

	x0 = pos.x;
	x1 = (pos.x + size.x);
	y0 = pos.y;
	y1 = (pos.y + size.y);

	if ((x0 <= position.x + Interactive_element::size.x) && (x1 > position.x + Interactive_element::size.x) && (((y0 >= position.y) && (y0 <= position.y + Interactive_element::size.y)) || ((y1 <= position.y + Interactive_element::size.y) && (y1 >= position.y)) || ((y0 < position.y) && (y1 > position.y + Interactive_element::size.y)) || ((y0 > position.y) && (y1 < position.y + Interactive_element::size.y))))
	{
		if (IsCollisionable) {
			position.x += movement;
			if (map->collisionMoveLeft(position, this->size)) {
				position.x = initialX;
				return true;
			}

			for (int i = 0; i < elements_restants.size(); i++)
			{
				vector<Interactive_element*> elements_restants2;
				for (int j = 0; j < elements_restants.size(); j++)
				{
					if (j != i) elements_restants2.push_back(elements_restants[j]);
				}
				if (elements_restants[i]->collisionMoveLeft(this->getPosition(), this->getSize(), movement, elements_restants2)) {
					position.x = initialX;
					return true;
				}
			}
		}
	}
	return false;
}

bool Interactive_element::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, const int movement, vector<Interactive_element*> elements_restants)
{
	int x0, x1, y0, y1, initialY;

	initialY = position.y;

	x0 = pos.x;
	x1 = (pos.x + size.x);
	y0 = pos.y;
	y1 = (pos.y + size.y);

	if ((y0 <= position.y + Interactive_element::size.y) && (y1 > position.y + Interactive_element::size.y) && (((x0 >= position.x) && (x0 <= position.x + Interactive_element::size.x)) || ((x1 <= position.x + Interactive_element::size.x) && (x1 >= position.x)) || ((x0 < position.x) && (x1 > position.x + Interactive_element::size.x)) || ((x0 > position.x) && (x1 < position.x + Interactive_element::size.x))))
	{
		if (IsCollisionable) {
			position.y += movement;
			if (map->collisionMoveUp(position, this->size)) {
				position.y = initialY;
				return true;
			}

			for (int i = 0; i < elements_restants.size(); i++)
			{
				vector<Interactive_element*> elements_restants2;
				for (int j = 0; j < elements_restants.size(); j++)
				{
					if (j != i) elements_restants2.push_back(elements_restants[j]);
				}
				if (elements_restants[i]->collisionMoveUp(this->getPosition(), this->getSize(), movement, elements_restants2)) {
					position.y = initialY;
					return true;
				}
			}
		}
	}
	return false;
}

bool Interactive_element::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, const int movement, vector<Interactive_element*> elements_restants)
{
	int x0, x1, y0, y1, initialY;

	initialY = position.y;

	x0 = pos.x;
	x1 = (pos.x + size.x);
	y0 = pos.y;
	y1 = (pos.y + size.y);

	if ((y0 < position.y) && (y1 >= position.y) && (((x0 >= position.x) && (x0 <= position.x + Interactive_element::size.x)) || ((x1 <= position.x + Interactive_element::size.x) && (x1 >= position.x)) || ((x0 < position.x) && (x1 > position.x + Interactive_element::size.x)) || ((x0 > position.x) && (x1 < position.x + Interactive_element::size.x))))
	{
		if (IsCollisionable) {
			position.y += movement;
			if (map->collisionMoveDown(position, this->size)) {
				position.y = initialY;
				return true;
			}

			for (int i = 0; i < elements_restants.size(); i++)
			{
				vector<Interactive_element*> elements_restants2;
				for (int j = 0; j < elements_restants.size(); j++)
				{
					if (j != i) elements_restants2.push_back(elements_restants[j]);
				}
				if (elements_restants[i]->collisionMoveDown(this->getPosition(), this->getSize(), movement, elements_restants2)) {
					position.y = initialY;
					return true;
				}
			}
		}
	}
	return false;
}

void Interactive_element::update(int deltaTime)
{
	if (type == Coin)
	{
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
	}
}

void Interactive_element::render()
{
	glm::mat4 modelview = glm::mat4(1.f);
	if (type != Coin) modelview = glm::translate(glm::mat4(1.0f), glm::vec3(tileMapDispl.x + position.x, tileMapDispl.y + position.y, 0.f));

	textureQuadProgram->setUniformMatrix4f("modelview", modelview);

	if (type != Coin) block->render(image);
	else sprite->render();
}

glm::ivec2 Interactive_element::getPosition()
{
	return position;
}

void Interactive_element::setPosition(const glm::ivec2& pos)
{
	position = pos;
}

glm::ivec2 Interactive_element::getSize()
{
	return size;
}

void Interactive_element::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

int Interactive_element::GetType()
{
	return type;
}

//EL METODE CHANGETYPE ja no cal, mira't el que ha canviat.

void Interactive_element::ChangeGate(ShaderProgram& shaderProgram, bool open)
{
	//TODO: Add sound or something to the gate
	if (open)
	{
		glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(size) };
		glm::vec2 texCoords[2] = { glm::vec2(11.f * 1.f / 13.f, 2.f * 1.f / 7.f), glm::vec2(13.f * 1.f / 13.f, 4.f * 1.f / 7.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	}
	else
	{
		glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(size) };
		glm::vec2 texCoords[2] = { glm::vec2(11.f * 1.f / 13.f, 0.f * 1.f / 1.f), glm::vec2(13.f * 1.f / 13.f, 2.f * 1.f / 7.f) };
		block = TexturedQuad::createTexturedQuad(geom, texCoords, shaderProgram);
	}
}

bool Interactive_element::IsInsideElement(const glm::ivec2 PlayerPosition, const glm::ivec2 PlayerSize)
{
	int x0, x1, y0, y1;

	x0 = PlayerPosition.x + 0.25 * PlayerSize.x;
	x1 = PlayerPosition.x + 0.75 * PlayerSize.x;
	y0 = PlayerPosition.y + 0.25 * PlayerSize.y;
	y1 = PlayerPosition.y + 0.75 * PlayerSize.y;

	if (x0 <= position.x + 0.75 * size.x && x1 >= position.x + 0.25 * size.x && y0 <= position.y + 0.75 * size.y && y1 >= position.y + 0.25 * size.y)
		return true;

	return false;
}
