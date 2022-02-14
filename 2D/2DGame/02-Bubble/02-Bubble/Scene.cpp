#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 1

#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 32


Scene::Scene()
{
	map = NULL;
	player = NULL;
	gate = NULL;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	for (int i = 0; i < elements.size(); i++) if (elements[i] != NULL) delete elements[i];
	if (gate != NULL)
		delete gate;
	if (engine != NULL)
	{
		engine->drop();
	}
}

void Scene::init(int level, bool repeat)
{
	int velocitat = 2;
	win = CoinsEffect = false;
	win = false;
	CoinsEffect = false;
	initShaders();
	int elements_size = CoinsLeft = 0;
	Silver_Key = Purple_Key = Red_Key = Yellow_Key = false;
	glm::vec2 StartPositionPlayer = glm::vec2(INIT_PLAYER_X_TILES, INIT_PLAYER_Y_TILES);
#pragma region Level1
	if (level == 1) {
		actualLevel = 1;
		StartPositionPlayer = glm::vec2(6.f, 8.f);
		map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		elements = vector<Interactive_element*>(30);
		Interactive_element* elem;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Gate, glm::ivec2(PLAYER_SIZE_X, PLAYER_SIZE_Y));
		elem->setPosition(glm::vec2(25 * map->getTileSize(), 8 * map->getTileSize()));
		elem->setTileMap(map);
		gate = elem;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(12 * map->getTileSize(), 8 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(15 * map->getTileSize(), 8 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;
	}
#pragma endregion
#pragma region level2
	else if (level == 2) {
		actualLevel = 2;
		player_copies = vector<Player_copy*>(0);

		map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		Interactive_element* elem;

		elements = vector<Interactive_element*>(30);

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Gate, glm::ivec2(32, 32));
		elem->setPosition(glm::vec2(24 * map->getTileSize(), 10 * map->getTileSize()));
		elem->setTileMap(map);
		gate = elem;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Lila, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(18 * map->getTileSize(), 22 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(13 * map->getTileSize(), 15 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(15 * map->getTileSize(), 11 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Purple_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(3 * map->getTileSize(), 13 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Purple_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(20 * map->getTileSize(), 3 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

	}
#pragma endregion
#pragma region level3
	else if (level == 3) {
		actualLevel = 3;
		player_copies = vector<Player_copy*>(0);

		StartPositionPlayer.x = 2;
		StartPositionPlayer.y = 1;
		map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		Interactive_element* elem;

		elements = vector<Interactive_element*>(30);

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Gate, glm::ivec2(32, 32));
		elem->setPosition(glm::vec2(33 * map->getTileSize(), 20 * map->getTileSize()));
		elem->setTileMap(map);
		gate = elem;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Vermell, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(22 * map->getTileSize(), 13 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		for (int i = 0; i < 6; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2(18 * map->getTileSize(), (16 + i * 2) * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}

		for (int i = 0; i < 9; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2(i * 2 * map->getTileSize(), 16 * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(10 * map->getTileSize(), 24 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(10 * map->getTileSize(), 18 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Red_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(32 * map->getTileSize(), 20 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Red_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(24 * map->getTileSize(), 23 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;
	}
#pragma endregion
#pragma region level4
	else if (level == 4) {
		actualLevel = 4;
		StartPositionPlayer = glm::vec2(18.f, 3.f);
		player_copies = vector<Player_copy*>(0);
		map = TileMap::createTileMap("levels/level04.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		Interactive_element* elem;

		elements = vector<Interactive_element*>(75);

		for (int i = 0; i < 12; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2(i * 2 * map->getTileSize(), 21 * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}
		for (int i = 0; i < 12; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2(i * 2 * map->getTileSize(), 23 * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Yellow_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(25 * map->getTileSize(), 5 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Yellow_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(30 * map->getTileSize(), 8 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Groc, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(20 * map->getTileSize(), 17 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &texProgram, Interactive_element::Coin, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(4 * map->getTileSize(), 24 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;
		CoinsLeft++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(3 * map->getTileSize(), 17 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(5 * map->getTileSize(), 17 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Gate, glm::ivec2(32, 32));
		elem->setPosition(glm::vec2(33 * map->getTileSize(), 25 * map->getTileSize()));
		elem->setTileMap(map);
		gate = elem;
	}
#pragma endregion


#pragma region level5
	else if (level == 5) {
		actualLevel = 5;
		StartPositionPlayer = glm::vec2(18.f, 3.f);
		player_copies = vector<Player_copy*>(0);
		map = TileMap::createTileMap("levels/level05.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		Interactive_element* elem;

		elements = vector<Interactive_element*>(75);

		for (int i = -1; i < 10; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2(i * 2 * map->getTileSize(), 15 * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}
		for (int i = -1; i < 10; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2(i * 2 * map->getTileSize(), 25 * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}
		for (int i = 0; i < 6; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2(20 * map->getTileSize(), (15 + i * 2) * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Yellow_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(13 * map->getTileSize(), 4 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Yellow_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(15 * map->getTileSize(), 6 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Groc, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(15 * map->getTileSize(), 17 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &texProgram, Interactive_element::Coin, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(28 * map->getTileSize(), 20 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;
		CoinsLeft++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(8 * map->getTileSize(), 20 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(12 * map->getTileSize(), 22 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Gate, glm::ivec2(32, 32));
		elem->setPosition(glm::vec2(33 * map->getTileSize(), 23 * map->getTileSize()));
		elem->setTileMap(map);
		gate = elem;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Vermell, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(12 * map->getTileSize(), 18 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Red_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(23 * map->getTileSize(), 5 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Red_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(29 * map->getTileSize(), 4 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;
	}
#pragma endregion

#pragma region level6
	else if (level == 6) {
		actualLevel = 6;
		StartPositionPlayer = glm::vec2(18.f, 3.f);
		player_copies = vector<Player_copy*>(0);
		map = TileMap::createTileMap("levels/level06.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		Interactive_element* elem;

		elements = vector<Interactive_element*>(30);

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Yellow_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(25 * map->getTileSize(), 20 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Yellow_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(28 * map->getTileSize(), 23 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Groc, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(20 * map->getTileSize(), 17 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &texProgram, Interactive_element::Coin, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(4 * map->getTileSize(), 24 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;
		CoinsLeft++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Lila, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(7 * map->getTileSize(), 17 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Purple_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(22 * map->getTileSize(), 4 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Purple_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(28 * map->getTileSize(), 7 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(3 * map->getTileSize(), 17 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(5 * map->getTileSize(), 17 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Gate, glm::ivec2(32, 32));
		elem->setPosition(glm::vec2(33 * map->getTileSize(), 25 * map->getTileSize()));
		elem->setTileMap(map);
		gate = elem;
	}
#pragma endregion

#pragma region level7
	else if (level == 7) {
		actualLevel = 7;
		player_copies = vector<Player_copy*>(0);

		StartPositionPlayer.x = 2;
		StartPositionPlayer.y = 1;
		map = TileMap::createTileMap("levels/level07.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		Interactive_element* elem;

		elements = vector<Interactive_element*>(30);

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Yellow_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(25 * map->getTileSize(), 4 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Yellow_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(28 * map->getTileSize(), 4 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Groc, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(20 * map->getTileSize(), 17 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Vermell, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(15 * map->getTileSize(), 3 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Red_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(7 * map->getTileSize(), 3 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Red_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(10 * map->getTileSize(), 3 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &texProgram, Interactive_element::Coin, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(20 * map->getTileSize(), 24 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;
		CoinsLeft++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Lila, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(10 * map->getTileSize(), 25 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Purple_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(25 * map->getTileSize(), 22 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Purple_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(27 * map->getTileSize(), 22 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(5 * map->getTileSize(), 19 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(8 * map->getTileSize(), 19 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Gate, glm::ivec2(32, 32));
		elem->setPosition(glm::vec2(1 * map->getTileSize(), 25 * map->getTileSize()));
		elem->setTileMap(map);
		gate = elem;


		for (int i = 0; i < 7; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2(17 * map->getTileSize(), (i * 2) * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}

		for (int i = 0; i < 8; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2(i * 2 * map->getTileSize(), 21 * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}

		for (int i = 0; i < 3; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2(14 * map->getTileSize(), (23 + i * 2) * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}
	}
#pragma endregion

#pragma region levelToteslesproves
	else if (level == 77)
	{
		actualLevel = 77;
		player_copies = vector<Player_copy*>(0);

		map = TileMap::createTileMap("levels/levelbase2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		Interactive_element* elem;

		elements = vector<Interactive_element*>(30);

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Lila, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(12 * map->getTileSize(), 22 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &texProgram, Interactive_element::Coin, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(17 * map->getTileSize(), 8 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;
		CoinsLeft++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Vermell, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(12 * map->getTileSize(), 18 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Groc, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(15 * map->getTileSize(), 9 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(10 * map->getTileSize(), 18 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Gate, glm::ivec2(32, 32));
		elem->setPosition(glm::vec2(1 * map->getTileSize(), 20 * map->getTileSize()));
		elem->setTileMap(map);
		gate = elem;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(18 * map->getTileSize(), 18 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(20 * map->getTileSize(), 18 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Yellow_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(24 * map->getTileSize(), 15 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Yellow_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(20 * map->getTileSize(), 21 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Red_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(11 * map->getTileSize(), 14 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Red_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(13 * map->getTileSize(), 14 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Purple_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(8 * map->getTileSize(), 12 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Purple_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(5 * map->getTileSize(), 12 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;
	}
#pragma endregion
#pragma region level2like3
	else if (level == 23) { //2like3
		actualLevel = 2;
		velocitat = 2;
		player_copies = vector<Player_copy*>(0);

		map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		Interactive_element* elem;

		elements = vector<Interactive_element*>(30);

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Gate, glm::ivec2(32, 32));
		elem->setPosition(glm::vec2(32 * map->getTileSize(), 7 * map->getTileSize()));
		elem->setTileMap(map);
		gate = elem;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Lila, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(5 * map->getTileSize(), 25 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(8 * map->getTileSize(), 19 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(25 * map->getTileSize(), 23 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Purple_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(10 * map->getTileSize(), 7 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Purple_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(20 * map->getTileSize(), 8 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;
	}
#pragma endregion
#pragma region levelfirelike3
	else if (level == 34) {
		actualLevel = 3;
		player_copies = vector<Player_copy*>(0);

		map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		Interactive_element* elem;

		elements = vector<Interactive_element*>(50);

		for (int i = 0; i < 10; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2(18 * map->getTileSize(), (8 + i * 2) * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}
		for (int i = 0; i < 9; i++) {
			elem = new Interactive_element();
			elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Lava_Floor, glm::vec2(32, 32));
			elem->setPosition(glm::vec2((18 + i * 2) * map->getTileSize(), 8 * map->getTileSize()));
			elem->setTileMap(map);
			elements[elements_size] = elem;
			elements_size++;
		}

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Gate, glm::ivec2(32, 32));
		elem->setPosition(glm::vec2(33 * map->getTileSize(), 4 * map->getTileSize()));
		elem->setTileMap(map);
		gate = elem;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Vermell, glm::vec2(32, 32));
		elem->setPosition(glm::vec2(10 * map->getTileSize(), 6 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(23 * map->getTileSize(), 15 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Silver_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(30 * map->getTileSize(), 20 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Red_Key_First, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(3 * map->getTileSize(), 14 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;

		elem = new Interactive_element();
		elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Red_Key_Second, glm::vec2(16, 32));
		elem->setPosition(glm::vec2(5 * map->getTileSize(), 20 * map->getTileSize()));
		elem->setTileMap(map);
		elements[elements_size] = elem;
		elements_size++;
	}
#pragma endregion

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(PLAYER_SIZE_X, PLAYER_SIZE_Y), texProgram);
	player->setPosition(glm::vec2(StartPositionPlayer.x * map->getTileSize(), StartPositionPlayer.y * map->getTileSize()));
	player->setTileMap(map);
	player->PlayerVelocity = velocitat;

	vector<Interactive_element*> elements_player(elements_size);
	for (int i = 0; i < elements_size; i++) elements_player[i] = elements[i];
	player->setElement(elements_player);
	elements = elements_player;

	player->setCopies(player_copies);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	engine = irrklang::createIrrKlangDevice();
	sounds = vector<irrklang::ISound*>(10);

	if (actualLevel != 1 && !repeat)
	{
		irrklang::ISound* sound = engine->play2D("sounds/Next_level.mp3", false, false, true);
		sound->setVolume(0.5f);
	}
	sounds[0] = engine->play2D("sounds/Coin.mp3", false, true, true);
	sounds[1] = engine->play2D("sounds/Death.mp3", false, true, true);
	if (repeat) sounds[1]->setIsPaused(false);
	sounds[2] = engine->play2D("sounds/Change_quads_red.mp3", false, true, true);
	sounds[3] = engine->play2D("sounds/Celebration.mp3", false, true, true);
	sounds[4] = engine->play2D("sounds/Change_quads_purple.mp3", false, true, true);
	sounds[5] = engine->play2D("sounds/Change_quads_yellow.mp3", false, true, true);
	sounds[6] = engine->play2D("sounds/Door_open.wav", false, true, true);
	sounds[7] = engine->play2D("sounds/Secret.mp3", false, true, true);
	sounds[8] = engine->play2D("sounds/Victory.mp3", false, true, true);
	sounds[8]->setVolume(0.5f);
	sounds[9] = engine->play2D("sounds/Change_copies.mp3", false, true, true);
	//[0] = Monedes
	//[1] = pj i/o copies es moren
	//[2] = change quads (RED)
	//[3] = Coins left == 0
	//[4] = change quads (PURPLE)
	//[5] = change quads (YELLOW)
}

bool Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (NextLevel()) {
		if (sounds[8]->getIsPaused()) {
			sounds[8]->setIsPaused(false);
		}
		player->SetWinAnimation(deltaTime, currentTime);
		if (player->WinAnimationFinished() && sounds[8]->isFinished())
			return true;
	}
	else {
		player->update(deltaTime);
		for (int i = 0; i < elements.size(); i++) elements[i]->update(deltaTime);
	}

	if (actualLevel == 1) {
		CanOpenGateWithKeys();
	}
	else if (actualLevel == 2) {
		CanOpenGateWithKeys();
	}
	else if (actualLevel == 3) {
		if (IsInsideLava())
		{
			this->~Scene();
			init(actualLevel, true);
		}
		CanOpenGateWithKeys();
	}
	else if (actualLevel == 4) {
		if (IsInsideLava())
		{
			this->~Scene();
			init(actualLevel, true);
		}
		CanOpenGateWithKeys();
		CoinsFunc();
	}
	else if (actualLevel == 5) {
		if (IsInsideLava())
		{
			this->~Scene();
			init(actualLevel, true);
		}
		CanOpenGateWithKeys();
		CoinsFunc();
	}
	else if (actualLevel == 6) {
		CoinsFunc();
		CanOpenGateWithKeys();
	}
	else if (actualLevel == 7) {
		if (IsInsideLava())
		{
			this->~Scene();
			init(actualLevel, true);
		}
		CanOpenGateWithKeys();
		CoinsFunc();
	}
	return false;
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();

	textureQuadProgram.use();
	textureQuadProgram.setUniformMatrix4f("projection", projection);
	textureQuadProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	gate->render();
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i]->GetType() != Interactive_element::Coin)
		{
			textureQuadProgram.use();
			textureQuadProgram.setUniformMatrix4f("projection", projection);
			textureQuadProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
			elements[i]->render();
		}
		else if (elements[i] != NULL)
		{
			texProgram.use();
			texProgram.setUniformMatrix4f("projection", projection);
			texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
			texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

			elements[i]->render();
		}
	}

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	if (player != NULL)
		player->render();

	for (int i = 0; i < player_copies.size(); i++) player_copies[i]->render();
}

void Scene::stop_sound()
{// aqui fes stop(); a tots els sounds looped. es veu que si crides el destructor dos cops peta. osigui k no podem cridarlo al clicar ESC per tornar al menu :)
	for (int i = 0; sounds.size(); i++) sounds[i]->stop();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/textureQuad.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/textureQuad.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	textureQuadProgram.init();
	textureQuadProgram.addShader(vShader);
	textureQuadProgram.addShader(fShader);
	textureQuadProgram.link();
	if (!textureQuadProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << textureQuadProgram.log() << endl << endl;
	}
	textureQuadProgram.bindFragmentOutput("outColor");

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::CoinsFunc()
{
	bool AnyYellowCopy = false;
	vector<int> positions;
	for (int i = 0; i < player_copies.size(); i++)
	{
		if (player_copies[i]->GetType() == Player_copy::Yellow_Copy)
		{
			AnyYellowCopy = true;
			positions.push_back(i);
		}
	}

	if (!CoinsEffect && AnyYellowCopy)
	{
		for (int i = 0; i < elements.size(); i++)
		{
			if (elements[i]->GetType() == Interactive_element::Coin)
			{
				for (int k = 0; k < positions.size(); k++)
				{
					if (elements[i]->IsInsideElement(player_copies[positions[k]]->GetPos(), player_copies[positions[k]]->GetSize()))
					{
						vector<Interactive_element*> new_elements(elements.size() - 1);
						int x = 0;
						for (int j = 0; j < elements.size(); j++)
						{
							if (j != i) new_elements[j - x] = elements[j];
							else x = 1;
						}
						elements = new_elements;
						player->setElement(elements);
						CoinsLeft--;

						if (sounds[0]->isFinished())
							sounds[0] = engine->play2D("sounds/Coin.mp3", false, false, true);
						else
						{
							sounds[0]->setPlayPosition(0);
							sounds[0]->setIsPaused(false);
						}
					}
				}

				if (CoinsLeft == 0)
				{
					sounds[7]->setIsPaused(false);
					CoinsEffect = true;
					if (actualLevel == 4) {
						map->ChangeMapforLevel5(glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 25, 13, 5);
					}
					else if (actualLevel == 5) {
						map->ChangeMapforLevel5(glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 28, 12, 7);
					}
					else if (actualLevel == 6) {
						map->ChangeMapforLevel5(glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 15, 11, 4);
					}
					else if (actualLevel == 7) {
						map->ChangeMapforLevel5(glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 7, 13, 5);
					}
					break;
				}
			}
		}
	}
}

void Scene::ChangeQuads(int type)
{
	vector<int> eliminations;
	vector<Player_copy*> new_copies(100);
	int new_size = 0;

	if (Player_copy::Purple_Copy == type)
	{
		if (sounds[4]->isFinished())
			sounds[4] = engine->play2D("sounds/Change_quads_purple.mp3", false, false, true);
		else
			sounds[4]->setIsPaused(false);
		for (int i = 0; i < elements.size(); i++)
		{
			if (elements[i] != NULL && elements[i]->GetType() == Interactive_element::Quadrat_Lila)
			{
				eliminations.push_back(i);
				Player_copy* copy = new Player_copy();
				copy->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(PLAYER_SIZE_X, PLAYER_SIZE_Y), Player_copy::Purple_Copy, texProgram);
				copy->setPosition(elements[i]->getPosition());
				copy->setTileMap(map);
				copy->PlayerVelocity = player->PlayerVelocity;
				new_copies[new_size] = copy;
				new_size++;
			}
		}
	}
	else if (Player_copy::Red_Copy == type)
	{
		if (sounds[2]->isFinished())
			sounds[2] = engine->play2D("sounds/Change_quads_red.mp3", false, false, true);
		else
			sounds[2]->setIsPaused(false);
		for (int i = 0; i < elements.size(); i++)
		{
			if (elements[i] != NULL && elements[i]->GetType() == Interactive_element::Quadrat_Vermell)
			{
				eliminations.push_back(i);
				Player_copy* copy = new Player_copy();
				copy->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(PLAYER_SIZE_X, PLAYER_SIZE_Y), Player_copy::Red_Copy, texProgram);
				copy->setPosition(elements[i]->getPosition());
				copy->setTileMap(map);
				copy->PlayerVelocity = player->PlayerVelocity;
				new_copies[new_size] = copy;
				new_size++;
			}
		}
	}
	else if (Player_copy::Yellow_Copy == type)
	{
		if (sounds[5]->isFinished())
			sounds[5] = engine->play2D("sounds/Change_quads_yellow.mp3", false, false, true);
		else
			sounds[5]->setIsPaused(false);
		for (int i = 0; i < elements.size(); i++)
		{
			if (elements[i] != NULL && elements[i]->GetType() == Interactive_element::Quadrat_Groc)
			{
				eliminations.push_back(i);
				Player_copy* copy = new Player_copy();
				copy->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(PLAYER_SIZE_X, PLAYER_SIZE_Y), Player_copy::Yellow_Copy, texProgram);
				copy->setPosition(elements[i]->getPosition());
				copy->setTileMap(map);
				copy->PlayerVelocity = player->PlayerVelocity;
				new_copies[new_size] = copy;
				new_size++;
			}
		}
	}

	vector<Interactive_element*> elementscopy;
	for (int k = 0; k < elements.size(); k++)
	{
		if (!(any_of(eliminations.begin(), eliminations.end(), [&](int i) { return i == k; }))) elementscopy.push_back(elements[k]);
	}
	elements = elementscopy;
	player->setElement(elementscopy);

	for (int i = 0; i < player_copies.size(); i++) new_copies[i + new_size] = player_copies[i];
	player_copies = vector<Player_copy*>(player_copies.size() + new_size);
	for (int i = 0; i < player_copies.size(); i++) player_copies[i] = new_copies[i];

	player->setCopies(player_copies);
}

void Scene::ChangeCopies(int type)
{
	vector<int> eliminations;
	vector<Interactive_element*> new_elements(100);
	int new_size = 0;

	if (Interactive_element::Quadrat_Lila == type)
	{
		for (int i = 0; i < player_copies.size(); i++)
		{
			if (player_copies[i]->GetType() == Player_copy::Purple_Copy)
			{
				eliminations.push_back(i);
				Interactive_element* elem = new Interactive_element();
				elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Lila, glm::vec2(32, 32));
				elem->setPosition(player_copies[i]->GetPos());
				elem->setTileMap(map);
				new_elements[new_size] = elem;
				new_size++;
			}
		}
	}
	else if (Interactive_element::Quadrat_Vermell == type)
	{
		for (int i = 0; i < player_copies.size(); i++)
		{
			if (player_copies[i]->GetType() == Player_copy::Red_Copy)
			{
				eliminations.push_back(i);
				Interactive_element* elem = new Interactive_element();
				elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Vermell, glm::vec2(32, 32));
				elem->setPosition(player_copies[i]->GetPos());
				elem->setTileMap(map);
				new_elements[new_size] = elem;
				new_size++;
			}
		}
	}
	else if (Interactive_element::Quadrat_Groc == type)
	{
		for (int i = 0; i < player_copies.size(); i++)
		{
			if (player_copies[i]->GetType() == Player_copy::Yellow_Copy)
			{
				eliminations.push_back(i);
				Interactive_element* elem = new Interactive_element();
				elem->init(glm::vec2(SCREEN_X, SCREEN_Y), &textureQuadProgram, Interactive_element::Quadrat_Groc, glm::vec2(32, 32));
				elem->setPosition(player_copies[i]->GetPos());
				elem->setTileMap(map);
				new_elements[new_size] = elem;
				new_size++;
			}
		}
	}

	vector<Player_copy*> copies;
	for (int k = 0; k < player_copies.size(); k++)
	{
		if (!(any_of(eliminations.begin(), eliminations.end(), [&](int i) { return i == k; }))) copies.push_back(player_copies[k]);
	}
	player_copies = copies;
	player->setCopies(copies);

	for (int i = 0; i < elements.size(); i++) new_elements[i + new_size] = elements[i];
	elements = vector<Interactive_element*>(elements.size() + new_size);
	for (int i = 0; i < elements.size(); i++) elements[i] = new_elements[i];

	player->setElement(elements);

	if (sounds[9]->isFinished())
		sounds[9] = engine->play2D("sounds/Change_copies.mp3", false, false, true);
	else
	{
		sounds[9]->setPlayPosition(0);
		sounds[9]->setIsPaused(false);
	}
}

bool Scene::NextLevel()
{
	if (gate->IsInsideElement(player->getPosition(), player->getSize()) && win == true)
		return true;
	for (int i = 0; i < player_copies.size(); i++) {
		if (player_copies[i]->GetType() == Player_copy::Purple_Copy)
		{
			if (gate->IsInsideElement(player_copies[i]->GetPos(), player_copies[i]->GetSize()) && win == true)
				return true;
		}
	}
	return false;
}

bool Scene::IsInsideLava() {
	vector<int> eliminations;

	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i] != NULL && elements[i]->GetType() == Interactive_element::Lava_Floor && elements[i]->IsInsideElement(player->getPosition(), player->getSize())) {
			if (sounds[1]->isFinished())
				sounds[1] = engine->play2D("sounds/Death.mp3", false, false, true);
			else
			{
				sounds[1]->setPlayPosition(0);
				sounds[1]->setIsPaused(false);
			}
			return true;
		}
		for (int j = 0; j < player_copies.size(); j++)
		{
			if (elements[i] != NULL && elements[i]->GetType() == Interactive_element::Lava_Floor && player_copies[j]->GetType() != Player_copy::Red_Copy && elements[i]->IsInsideElement(player_copies[j]->GetPos(), player_copies[j]->GetSize()))
			{
				if (sounds[1]->isFinished())
					sounds[1] = engine->play2D("sounds/Death.mp3", false, false, true);
				else
				{
					sounds[1]->setPlayPosition(0);
					sounds[1]->setIsPaused(false);
				}
				eliminations.push_back(j);
			}
		}
	}

	vector<Player_copy*> copies;
	for (int k = 0; k < player_copies.size(); k++)
	{
		if (!(any_of(eliminations.begin(), eliminations.end(), [&](int i) { return i == k; }))) copies.push_back(player_copies[k]);
	}
	player_copies = copies;
	player->setCopies(copies);
	return false;
}

void Scene::CanOpenGateWithKeys() {
	vector<Interactive_element*> elementscopy;
	for (int i = 0; i < elements.size(); i++) {
		if (elements[i] != NULL && elements[i]->GetType() == Interactive_element::Silver_Key_First) {
			for (int j = 0; j < elements.size(); j++) {
				if (elements[j] != NULL && elements[j]->GetType() == Interactive_element::Silver_Key_Second) {
					int posXi = elements[i]->getPosition().x + elements[i]->getSize().x;
					int posYi = elements[i]->getPosition().y;
					int posXj = elements[j]->getPosition().x;
					int posYj = elements[j]->getPosition().y;

					if (!Silver_Key && abs(posYi - posYj) < elements[i]->getSize().y / 2.f && abs(posXj + 1 - posXi) < elements[i]->getSize().x / 2.f) {
						Silver_Key = true;
						int offsetX = elements[i]->getSize().x;

						elements[i]->setPosition(glm::ivec2(posXj - offsetX, posYj));

						gate->ChangeGate(textureQuadProgram, true);
						if (sounds[6]->isFinished()) sounds[6] = engine->play2D("sounds/Door_open.wav", false, false, true);
						else
						{
							sounds[6]->setPlayPosition(0);
							sounds[6]->setIsPaused(false);
						}
						win = true;
					}
					else if (Silver_Key && (abs(posYi - posYj) > elements[i]->getSize().y / 2.f || abs(posXj + 1 - posXi) > elements[i]->getSize().x / 2.f))
					{
						Silver_Key = false;
						elements[i]->setPosition(glm::ivec2(elements[i]->getPosition().x - 1, elements[i]->getPosition().y));
						gate->ChangeGate(textureQuadProgram, false);
						win = false;
					}
				}
			}
		}
		else if (elements[i] != NULL && elements[i]->GetType() == Interactive_element::Purple_Key_First)
		{
			for (int j = 0; j < elements.size(); j++) {
				if (elements[j] != NULL && elements[j]->GetType() == Interactive_element::Purple_Key_Second) {
					int posXi = elements[i]->getPosition().x + elements[i]->getSize().x;
					int posYi = elements[i]->getPosition().y;
					int posXj = elements[j]->getPosition().x;
					int posYj = elements[j]->getPosition().y;

					if (!Purple_Key && abs(posYi - posYj) < elements[i]->getSize().y / 2.f && abs(posXj + 1 - posXi) < elements[i]->getSize().x / 2.f) {
						Purple_Key = true;
						int offsetX = elements[i]->getSize().x;

						elements[i]->setPosition(glm::ivec2(posXj - offsetX, posYj));

						ChangeQuads(Player_copy::Purple_Copy);
					}
					else if (Purple_Key && (abs(posYi - posYj) > elements[i]->getSize().y / 2.f || abs(posXj + 1 - posXi) > elements[i]->getSize().x / 2.f))
					{
						Purple_Key = false;
						elements[i]->setPosition(glm::ivec2(elements[i]->getPosition().x - 1, elements[i]->getPosition().y));

						ChangeCopies(Interactive_element::Quadrat_Lila);
					}
				}
			}
		}
		else if (elements[i] != NULL && elements[i]->GetType() == Interactive_element::Red_Key_First)
		{
			for (int j = 0; j < elements.size(); j++) {
				if (elements[j] != NULL && elements[j]->GetType() == Interactive_element::Red_Key_Second) {
					int posXi = elements[i]->getPosition().x + elements[i]->getSize().x;
					int posYi = elements[i]->getPosition().y;
					int posXj = elements[j]->getPosition().x;
					int posYj = elements[j]->getPosition().y;

					if (!Red_Key && abs(posYi - posYj) < elements[i]->getSize().y / 2.f && abs(posXj + 1 - posXi) < elements[i]->getSize().x / 2.f) {
						Red_Key = true;
						int offsetX = elements[i]->getSize().x;

						elements[i]->setPosition(glm::ivec2(posXj - offsetX, posYj));

						ChangeQuads(Player_copy::Red_Copy);
					}
					else if (Red_Key && (abs(posYi - posYj) > elements[i]->getSize().y / 2.f || abs(posXj + 1 - posXi) > elements[i]->getSize().x / 2.f))
					{
						Red_Key = false;
						elements[i]->setPosition(glm::ivec2(elements[i]->getPosition().x - 1, elements[i]->getPosition().y));

						ChangeCopies(Interactive_element::Quadrat_Vermell);
					}
				}
			}
		}
		else if (elements[i] != NULL && elements[i]->GetType() == Interactive_element::Yellow_Key_First)
		{
			for (int j = 0; j < elements.size(); j++) {
				if (elements[j] != NULL && elements[j]->GetType() == Interactive_element::Yellow_Key_Second) {
					int posXi = elements[i]->getPosition().x + elements[i]->getSize().x;
					int posYi = elements[i]->getPosition().y;
					int posXj = elements[j]->getPosition().x;
					int posYj = elements[j]->getPosition().y;

					if (!Yellow_Key && abs(posYi - posYj) < elements[i]->getSize().y / 2.f && abs(posXj + 1 - posXi) < elements[i]->getSize().x / 2.f) {
						Yellow_Key = true;
						int offsetX = elements[i]->getSize().x;

						elements[i]->setPosition(glm::ivec2(posXj - offsetX, posYj));

						ChangeQuads(Player_copy::Yellow_Copy);
					}
					else if (Yellow_Key && (abs(posYi - posYj) > elements[i]->getSize().y / 2.f || abs(posXj + 1 - posXi) > elements[i]->getSize().x / 2.f))
					{
						Yellow_Key = false;
						elements[i]->setPosition(glm::ivec2(elements[i]->getPosition().x - 1, elements[i]->getPosition().y));

						ChangeCopies(Interactive_element::Quadrat_Groc);
					}
				}
			}
		}
	}
}


