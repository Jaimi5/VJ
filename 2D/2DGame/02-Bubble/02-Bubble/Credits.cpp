#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include "Credits.h"

Credits::Credits()
{
	sprite = NULL;
}

Credits::~Credits()
{
	if (sprite != NULL) delete sprite;
	for (int i = 0; i < 7; i++)
		if (game_by[i] != NULL)
			delete game_by[i];
	for (int i = 0; i < 11; i++)
		if (nom1[i] != NULL)
			delete nom1[i];
	for (int i = 0; i < 10; i++)
		if (nom2[i] != NULL)
			delete nom2[i];
	if (engine != NULL)
	{
		engine->drop();
	}
}

void Credits::init()
{
	glm::vec2 geom[2];
	glm::vec2 texCoords[2];

	Credits::initShaders();

	//load frase "Game by:"
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(50.f, 50.f);
	//lletra G
	texCoords[0] = glm::vec2(6 * (1.f / 26.f), 1 * (1.f / 5.f)); texCoords[1] = glm::vec2(7 * (1.f / 26.f), 2 * (1.f / 5.f));
	game_by[0] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra a
	texCoords[0] = glm::vec2(0 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(1 * (1.f / 26.f), 3 * (1.f / 5.f));
	game_by[1] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra m
	texCoords[0] = glm::vec2(12 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(13 * (1.f / 26.f), 3 * (1.f / 5.f));
	game_by[2] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra e
	texCoords[0] = glm::vec2(4 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(5 * (1.f / 26.f), 3 * (1.f / 5.f));
	game_by[3] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra b
	texCoords[0] = glm::vec2(1 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(2 * (1.f / 26.f), 3 * (1.f / 5.f));
	game_by[4] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra y
	texCoords[0] = glm::vec2(24 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(25 * (1.f / 26.f), 3 * (1.f / 5.f));
	game_by[5] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra :
	texCoords[0] = glm::vec2(16 * (1.f / 26.f), 4 * (1.f / 5.f)); texCoords[1] = glm::vec2(17 * (1.f / 26.f), 5 * (1.f / 5.f));
	game_by[6] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);

	//load frase "Víctor Luque"
	//lletra V
	texCoords[0] = glm::vec2(21 * (1.f / 26.f), 1 * (1.f / 5.f)); texCoords[1] = glm::vec2(22 * (1.f / 26.f), 2 * (1.f / 5.f));
	nom1[0] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra í
	texCoords[0] = glm::vec2(15 * (1.f / 26.f), 3 * (1.f / 5.f)); texCoords[1] = glm::vec2(16 * (1.f / 26.f), 4 * (1.f / 5.f));
	nom1[1] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra c
	texCoords[0] = glm::vec2(2 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(3 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom1[2] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra t
	texCoords[0] = glm::vec2(19 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(20 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom1[3] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra o
	texCoords[0] = glm::vec2(14 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(15 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom1[4] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra r
	texCoords[0] = glm::vec2(17 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(18 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom1[5] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra L
	texCoords[0] = glm::vec2(11 * (1.f / 26.f), 1 * (1.f / 5.f)); texCoords[1] = glm::vec2(12 * (1.f / 26.f), 2 * (1.f / 5.f));
	nom1[6] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra u
	texCoords[0] = glm::vec2(20 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(21 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom1[7] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra q
	texCoords[0] = glm::vec2(16 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(17 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom1[8] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra u
	texCoords[0] = glm::vec2(20 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(21 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom1[9] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra e
	texCoords[0] = glm::vec2(4 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(5 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom1[10] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);

	//load frase "Joan Miquel"
	//lletra J
	texCoords[0] = glm::vec2(9 * (1.f / 26.f), 1 * (1.f / 5.f)); texCoords[1] = glm::vec2(10 * (1.f / 26.f), 2 * (1.f / 5.f));
	nom2[0] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra o
	texCoords[0] = glm::vec2(14 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(15 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom2[1] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra a
	texCoords[0] = glm::vec2(0 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(1 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom2[2] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra n
	texCoords[0] = glm::vec2(13 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(14 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom2[3] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra M
	texCoords[0] = glm::vec2(12 * (1.f / 26.f), 1 * (1.f / 5.f)); texCoords[1] = glm::vec2(13 * (1.f / 26.f), 2 * (1.f / 5.f));
	nom2[4] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra i
	texCoords[0] = glm::vec2(8 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(9 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom2[5] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra q
	texCoords[0] = glm::vec2(16 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(17 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom2[6] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra u
	texCoords[0] = glm::vec2(20 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(21 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom2[7] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra e
	texCoords[0] = glm::vec2(4 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(5 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom2[8] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	//lletra l
	texCoords[0] = glm::vec2(11 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(12 * (1.f / 26.f), 3 * (1.f / 5.f));
	nom2[9] = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);

	abecedari.loadFromFile("images/letras.png", TEXTURE_PIXEL_FORMAT_RGBA);

	spriteSheet.loadFromFile("images/credits.jpg", TEXTURE_PIXEL_FORMAT_RGBA);

	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(0.25, 0.25), &spriteSheet, &textureProgram);
	sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(0, glm::vec2(0.25f, 0.f));
		sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(0, glm::vec2(0.75f, 0.f));
		sprite->addKeyframe(0, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(0, glm::vec2(0.25f, 0.25f));
		sprite->addKeyframe(0, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(0, glm::vec2(0.75f, 0.25f));
		sprite->addKeyframe(0, glm::vec2(0.f, 0.5f));
		sprite->addKeyframe(0, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(0, glm::vec2(0.5f, 0.5f));
		sprite->addKeyframe(0, glm::vec2(0.75f, 0.5f));
		sprite->addKeyframe(0, glm::vec2(0.f, 0.75f));
		sprite->addKeyframe(0, glm::vec2(0.25f, 0.75f));
		sprite->addKeyframe(0, glm::vec2(0.5f, 0.75f));
		sprite->addKeyframe(0, glm::vec2(0.75f, 0.75f));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(0.f));

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	engine = irrklang::createIrrKlangDevice();
	sound = engine->play2D("sounds/fire.mp3", true, false, true);
}

void Credits::update(int deltaTime)
{
	currentTime += deltaTime;
	sprite->update(deltaTime);
}

void Credits::render()
{

	glm::mat4 modelview = glm::mat4(1.0f);

	textureProgram.use();
	textureProgram.setUniformMatrix4f("projection", projection);
	textureProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	textureProgram.setUniformMatrix4f("modelview", modelview);
	textureProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	
	sprite->render();

	modelview = glm::mat4(1.0f);
	textureQuadProgram.use();
	textureQuadProgram.setUniformMatrix4f("projection", projection);
	textureQuadProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	

	//render "Game by:"
	int x = 0;
	float offset = CAMERA_WIDTH/2.f - (4 * (50.f - 12.f));
	for (int i = 0; i < 8; i++)
	{
		if (i == 0) modelview = glm::translate(glm::mat4(1.0f), glm::vec3(offset + i * (50.f) - (i + 1) * (12.f/2.f), 160.f, 0.f));
		else modelview = glm::translate(glm::mat4(1.0f), glm::vec3(offset + i * (50.f) - (i + 1) * (12.f), 160.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		if (i != 4) {
			game_by[x]->render(abecedari);
			x++;
		}
	}

	//render "Víctor luque"
	x = 0;
	offset = CAMERA_WIDTH / 2.f - (6 * (50.f - 12.f));
	for (int i = 0; i < 12; i++)
	{
		if (i == 0) modelview = glm::translate(glm::mat4(1.0f), glm::vec3(offset + i * (50.f) - (i + 1) * (12.f / 2.f), 240.f, 0.f));
		else modelview = glm::translate(glm::mat4(1.0f), glm::vec3(offset + i * (50.f) - (i + 1) * (12.f), 240.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		if (i != 6) {
			nom1[x]->render(abecedari);
			x++;
		}
	}

	//render "Joan Miquel"
	x = 0;
	offset = CAMERA_WIDTH / 2.f - (5.5f * (50.f - 12.f));
	for (int i = 0; i < 11; i++)
	{
		if (i == 0) modelview = glm::translate(glm::mat4(1.0f), glm::vec3(offset + i * (50.f) - (i + 1) * (12.f / 2.f), 300.f, 0.f));
		else modelview = glm::translate(glm::mat4(1.0f), glm::vec3(offset + i * (50.f) - (i + 1) * (12.f), 300.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		if (i != 4) {
			nom2[x]->render(abecedari);
			x++;
		}
	}

}

void Credits::stop_sound()
{
	sound->stop();
}

void Credits::initShaders()
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