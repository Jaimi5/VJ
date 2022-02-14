#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	state = STATE_MENU;
	menu.init();
	engine = irrklang::createIrrKlangDevice();
	music = engine->play2D("sounds/Music.mp3", true, true, true);
}

bool Game::update(int deltaTime)
{
	switch (state)
	{
	case(STATE_MENU):
		break;
	case(STATE_PLAY):
		if (scene.update(deltaTime))
		{
			int level = scene.actualLevel + 1;
			if (level == 8) {
				music->setIsPaused(true);
				credits.~Credits();
				credits.init();
				Game::state = STATE_CREDITS;
			}
			else
			{
				scene.~Scene();
				scene.init(level, false);
			}
		}
		break;
	case(STATE_INSTRUCTIONS):
		instructions.update(deltaTime);
		break;
	case(STATE_CREDITS):
		credits.update(deltaTime);
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
	case(STATE_INSTRUCTIONS):
		instructions.render();
		break;
	case(STATE_CREDITS):
		credits.render();
		break;
	}
}

void Game::keyPressed(int key)
{
	if (key == 27 && !once[key])// Escape code
	{
		once[key] = true;
		switch (Game::state)
		{
		case(STATE_MENU):
			bPlay = false;
			break;
		case(STATE_PLAY):
			music->setIsPaused(true);
			menu.~Menu();
			menu.init();
			state = STATE_MENU;
			break;
		case(STATE_INSTRUCTIONS):
			menu.~Menu();
			menu.init();
			state = STATE_MENU;
			break;
		case(STATE_CREDITS):
			credits.stop_sound();
			menu.~Menu();
			menu.init();
			state = STATE_MENU;
			break;
		}
	}
	else if (key == 'r' && !once[key])
	{
		once[key] = true;
		if (state == STATE_PLAY)
		{
			scene.~Scene();
			scene.init(scene.actualLevel, true);
		}
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
	once[key] = false;
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
	if (Game::state == STATE_MENU)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (x > 103 && x < 532)
			{
				if (y > 41 && y < 159)
				{
					music->setPlayPosition(0);
					music->setIsPaused(false);
					scene.~Scene();
					scene.init(1, false);
					Game::state = STATE_PLAY;
				}
				else if (y > 160 && y < 278)
				{
					instructions.~Instructions();
					instructions.init(0);
					Game::state = STATE_INSTRUCTIONS;
				}
				else if (y > 278 && y < 396)
				{
					credits.~Credits();
					credits.init();
					Game::state = STATE_CREDITS;
				}
			}
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

bool Game::getOnce(int key) const
{
	return once[key];
}



