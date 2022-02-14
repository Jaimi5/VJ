#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include <vector>
#include "Sprite.h"
#include "TileMap.h"
#include "Interactive_element.h"
#include "Player_copy.h"
#include <irrKlang.h>


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	Player::~Player();

	void init(const glm::ivec2 &tileMapPos, glm::ivec2 size, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void SetWinAnimation(int deltaTime, int currentTime);
	bool WinAnimationFinished();
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setElement(vector<Interactive_element*> &elements);
	void setCopies(vector<Player_copy*> &copies);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	glm::ivec2 getSize();
	int PlayerVelocity;
	int AnimationWinLoop;
	
private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer, size;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	vector<Interactive_element*> elements;
	vector<Player_copy*> copies;
	glm::ivec2 RealPlayerSize = glm::ivec2(20, 16);
	glm::ivec2 RealOffsetToPlayer = glm::ivec2(6, 16);
	irrklang::ISoundEngine* engine; // aixo es un punter a el que te tots els metodes per fer servir ISounds
	vector<irrklang::ISound*> sounds; // aquí guarda els sons, mira't el codi exemple i entendras
	bool hit;
};


#endif // _PLAYER_INCLUDE


