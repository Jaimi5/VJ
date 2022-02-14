#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include "Menu.h"

Menu::Menu()
{
	background = NULL;
	quad = NULL;
}

void Menu::init()
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	Menu::initShaders();
	quad = Quad::createQuad(0.f, 0.f, 128.f, 128.f, simpleProgram);
	background = TexturedQuad::createTexturedQuad(geom, texCoords, textureProgram);
	image_background.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

}

void Menu::render()
{
	glm::mat4 modelview = glm::mat4(1.0f);

	textureProgram.use();
	textureProgram.setUniformMatrix4f("projection", projection);
	textureProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	textureProgram.setUniformMatrix4f("modelview", modelview);

	background->render(image_background);
	/*
	simpleProgram.use();
	simpleProgram.setUniformMatrix4f("projection", projection);
	simpleProgram.setUniform4f("color", 0.8f, 0.2f, 0.8f, 1.0f);
	modelview = glm::mat4(1.0f);
	simpleProgram.setUniformMatrix4f("modelview", modelview);
	quad->render();
	*/
}

void Menu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	simpleProgram.init();
	simpleProgram.addShader(vShader);
	simpleProgram.addShader(fShader);
	simpleProgram.link();
	if (!simpleProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleProgram.log() << endl << endl;
	}
	simpleProgram.bindFragmentOutput("outColor");

	vShader.free();
	fShader.free();
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
	textureProgram.init();
	textureProgram.addShader(vShader);
	textureProgram.addShader(fShader);
	textureProgram.link();
	if (!textureProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << textureProgram.log() << endl << endl;
	}
	textureProgram.bindFragmentOutput("outColor");
}