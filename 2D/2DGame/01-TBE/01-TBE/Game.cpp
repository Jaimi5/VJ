#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	state = STATE_MENU;
	menu.init();
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
}

bool Game::update(int deltaTime)
{
	//scene.update(deltaTime);

	switch (state)
	{
	case(STATE_MENU):
		//menu.update();
		break;
	case(STATE_PLAY):
		scene.update(deltaTime);
		break;
	}
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (state)
	{
	case(STATE_MENU):
		menu.render();
		break;
	case(STATE_PLAY):
		scene.render();
		break;
	}
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		switch (Game::state)
		{
			case(STATE_MENU):
				bPlay = false;
				break;
			case(STATE_PLAY):
				state = STATE_MENU;
				break;
		}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (x > 103 && x < 532 && y > (41) && y < (150)) {
			Game::state = STATE_PLAY;
		}
	}
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





