#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Interactive_element.h"
#include "Player_copy.h"
#include <irrKlang.h>


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(int level, bool repeat);
	bool update(int deltaTime);
	void render();
	void stop_sound();
	bool win;
	int actualLevel;

private:
	void initShaders();
	void CoinsFunc();
	void ChangeQuads(int type);
	void ChangeCopies(int type);
	void CanOpenGateWithKeys();

	bool NextLevel();
	bool IsInsideLava();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram, textureQuadProgram;
	float currentTime;
	glm::mat4 projection;
	vector<Interactive_element*> elements;
	Interactive_element* gate;
	vector<Player_copy*> player_copies;
	bool Silver_Key, Purple_Key, Red_Key, Yellow_Key, CoinsEffect;
	int CoinsLeft;
	irrklang::ISoundEngine* engine;
	vector<irrklang::ISound*> sounds;

};


#endif // _SCENE_INCLUDE

