#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "Menu.h"
#include "Credits.h"
#include "Instructions.h"
#include <irrKlang.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button, int state, int x, int y);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	bool getOnce(int key) const;

private:
	enum { STATE_MENU, STATE_PLAY, STATE_CREDITS, STATE_INSTRUCTIONS};
	int state;
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	Menu menu;
	Credits credits;
	Instructions instructions;
	bool keys[256], specialKeys[256]; // Store key states so that 
	bool once[256] = { false };
	                                  // we can have access at any time
	irrklang::ISoundEngine* engine;
	irrklang::ISound* music;
};


#endif // _GAME_INCLUDE


