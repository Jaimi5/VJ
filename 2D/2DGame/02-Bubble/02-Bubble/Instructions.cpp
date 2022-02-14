#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Instructions.h"
#include "Game.h"

Instructions::Instructions()
{
	background = NULL;
}

Instructions::~Instructions()
{
	if (background != NULL)
	{
		delete background;
		background = NULL;
	}
	for (int i = 0; i < elements.size(); i++)
		if (elements[i] != NULL) delete elements[i];
	
	if (engine != NULL)
	{
		engine->drop();
	}
}

void Instructions::init(int page)
{
	Instructions::page = page;
	currentTime = 0.f;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	initShaders();
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

	background = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);

	image_background = vector<Texture>(4);
	image_background[MAIN_RULES].loadFromFile("images/main_rules.png", TEXTURE_PIXEL_FORMAT_RGBA);
	image_background[PURPLE_COPY].loadFromFile("images/purple_copy.png", TEXTURE_PIXEL_FORMAT_RGBA);
	image_background[RED_COPY].loadFromFile("images/red_copy.png", TEXTURE_PIXEL_FORMAT_RGBA);
	image_background[YELLOW_COPY].loadFromFile("images/yellow_copy.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//elements[0] = gate closed
	//[1] = gate opened
	//[2] = pj
	//[3] = Silver_key_first
	//[4] = Silver_key_second
	//[5] = Silver_key
	//[6] = lava
	//[7] = Purple_key_first
	//[8] = Purple_key_second
	//[9] = Purple_key
	//[10] = Quadrat_lila
	//[11] = pj_lila
	//[12] = Red_key_first
	//[13] = Red_key_second
	//[14] = Red_key
	//[15] = Quadrat_vermell
	//[16] = pj_rojo
	//[17] = Yellow_key_first
	//[18] = Yellow_key_second
	//[19] = Yellow_key
	//[20] = Quadrat_groc
	//[21] = pj_amarillo
	//[22] = coin
	elements = vector<TexturedQuad*>(23);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(30.f, 30.f);

	texCoords[0] = glm::vec2(11.f * 1.f / 13.f, 0.f * 1.f / 1.f); texCoords[1] = glm::vec2(13.f * 1.f / 13.f, 2.f * 1.f / 7.f);
	TexturedQuad* quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[0] = quad;

	texCoords[0] = glm::vec2(11.f * 1.f / 13.f, 2.f * 1.f / 7.f); texCoords[1] = glm::vec2(13.f * 1.f / 13.f, 4.f * 1.f / 7.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[1] = quad;

	texCoords[0] = glm::vec2(1.f / 18.f, 0.f); texCoords[1] = glm::vec2(glm::vec2(2.f / 18.f, 0.25f));
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[2] = quad;

	texCoords[0] = glm::vec2(6.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(8.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[5] = quad;

	texCoords[0] = glm::vec2(0.f * 1.f / 8.f, 5.f * 1.f / 6.f); texCoords[1] = glm::vec2(1.f * 1.f / 8.f, 6.f * 1.f / 6.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[6] = quad;

	texCoords[0] = glm::vec2(0.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(2.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[9] = quad;

	texCoords[0] = glm::vec2(2.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(4.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[14] = quad;

	texCoords[0] = glm::vec2(4.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(6.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[19] = quad;

	texCoords[0] = glm::vec2(2.f * 1.f / 8.f, 2.f * 1.f / 6.f); texCoords[1] = glm::vec2(3.f * 1.f / 8.f, 3.f * 1.f / 6.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[10] = quad;

	texCoords[0] = glm::vec2(1.f / 18.f, 0.f); texCoords[1] = glm::vec2(glm::vec2(2.f / 18.f, 0.25f));
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[11] = quad;

	texCoords[0] = glm::vec2(2.f * 1.f / 8.f, 1.f * 1.f / 6.f); texCoords[1] = glm::vec2(3.f * 1.f / 8.f, 2.f * 1.f / 6.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[20] = quad;

	texCoords[0] = glm::vec2(4.f * 1.f / 8.f, 5.f * 1.f / 6.f); texCoords[1] = glm::vec2(5.f * 1.f / 8.f, 6.f * 1.f / 6.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[15] = quad;

	texCoords[0] = glm::vec2(1.f / 18.f, 0.f); texCoords[1] = glm::vec2(glm::vec2(2.f / 18.f, 0.25f));
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[16] = quad;

	texCoords[0] = glm::vec2(1.f / 18.f, 0.f); texCoords[1] = glm::vec2(glm::vec2(2.f / 18.f, 0.25f));
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[21] = quad;

	texCoords[0] = glm::vec2(0.f / 6.f, 0.f); texCoords[1] = glm::vec2(glm::vec2(1.f / 6.f, 1.f));
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[22] = quad;

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(15.f, 30.f);
	texCoords[0] = glm::vec2(6.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(7.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[3] = quad;

	texCoords[0] = glm::vec2(7.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(8.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[4] = quad;

	texCoords[0] = glm::vec2(0.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(1.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[7] = quad;

	texCoords[0] = glm::vec2(1.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(2.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[8] = quad;

	texCoords[0] = glm::vec2(2.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(3.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[12] = quad;

	texCoords[0] = glm::vec2(3.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(4.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[13] = quad;

	texCoords[0] = glm::vec2(4.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(5.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[17] = quad;

	texCoords[0] = glm::vec2(5.f * 1.f / 8.f, 0.f * 1.f / 2.f); texCoords[1] = glm::vec2(6.f * 1.f / 8.f, 2.f * 1.f / 2.f);
	quad = TexturedQuad::createTexturedQuad(geom, texCoords, textureQuadProgram);
	elements[18] = quad;

	//images_elems[0] = gates
	//[1] = pj
	//[2] = keys
	//[3] = tiles_floor
	//[4] = pj_lila
	//[5] = pj_rojo

	images_elems = vector<Texture>(8);
	images_elems[0].loadFromFile("images/spr_Greenlands_orth_0.png", TEXTURE_PIXEL_FORMAT_RGBA);
	images_elems[1].loadFromFile("images/pj.png", TEXTURE_PIXEL_FORMAT_RGBA);
	images_elems[2].loadFromFile("images/KeyIcons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	images_elems[3].loadFromFile("images/tiles_floor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	images_elems[4].loadFromFile("images/pj_lila.png", TEXTURE_PIXEL_FORMAT_RGBA);
	images_elems[5].loadFromFile("images/pj_rojo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	images_elems[6].loadFromFile("images/pj_amarillo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	images_elems[7].loadFromFile("images/coin.png", TEXTURE_PIXEL_FORMAT_RGBA);

	engine = irrklang::createIrrKlangDevice();
	sound = engine->play2D("sounds/Page_Pass.mp3", false, true, true);
}

void Instructions::update(int deltaTime)
{
	int initial_page = page;
	currentTime += deltaTime;
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !once[0] && page != MAIN_RULES)
	{
		page--;
		once[0] = true;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !once[1] && page != YELLOW_COPY)
	{
		page++;
		once[1] = true;
	}

	if (!Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		once[0] = false;
	if (!Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		once[1] = false;

	if (initial_page != page)
	{
		sound->stop();
		sound->drop();
		sound = engine->play2D("sounds/Page_Pass.mp3", false, false, true);
	}
}

void Instructions::render()
{
	glm::mat4 modelview = glm::mat4(1.0f);

	textureQuadProgram.use();
	textureQuadProgram.setUniformMatrix4f("projection", projection);
	textureQuadProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	textureQuadProgram.setUniformMatrix4f("modelview", modelview);

	background->render(image_background[page]);

	if (page == MAIN_RULES)
	{
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(300.f, 98.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[2]->render(images_elems[1]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(379.f, 98.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[0]->render(images_elems[0]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(451.f, 98.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[0]->render(images_elems[0]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(552.f, 98.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[1]->render(images_elems[0]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(246.f, 170.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[3]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(320.f, 170.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[4]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(70.f, 200.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[5]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(185.f, 200.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[0]->render(images_elems[0]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(208.f, 240.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[6]->render(images_elems[3]);
	}
	else if (page == PURPLE_COPY)
	{
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(253.f, 100.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[7]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(327.f, 100.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[8]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(105.f, 131.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[9]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(300.f, 131.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[9]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(62.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[9]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(248.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[10]->render(images_elems[3]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(422.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[11]->render(images_elems[4]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(495.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[11]->render(images_elems[4]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(145.f, 220.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[2]->render(images_elems[1]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(537.f, 285.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[6]->render(images_elems[3]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(597.f, 327.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[1]->render(images_elems[0]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(62.f, 357.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[2]->render(images_elems[1]);
	}
	else if (page == RED_COPY)
	{
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(256.f, 100.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[12]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(330.f, 100.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[13]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(113.f, 131.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[14]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(300.f, 131.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[14]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(62.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[14]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(248.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[15]->render(images_elems[3]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(422.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[16]->render(images_elems[5]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(495.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[16]->render(images_elems[5]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(145.f, 220.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[2]->render(images_elems[1]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(226.f, 315.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[6]->render(images_elems[3]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(180.f, 340.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[1]->render(images_elems[0]);
	}
	else if (page == YELLOW_COPY)
	{
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(256.f, 100.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[17]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(330.f, 100.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[18]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(113.f, 131.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[19]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(300.f, 131.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[19]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(62.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[19]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(248.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[20]->render(images_elems[3]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(422.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[21]->render(images_elems[6]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(495.f, 195.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[21]->render(images_elems[6]);
		
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(145.f, 220.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[2]->render(images_elems[1]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(556.f, 285.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[6]->render(images_elems[3]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(284.f, 330.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[22]->render(images_elems[7]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(326.f, 360.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[3]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(375.f, 365.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[8]->render(images_elems[2]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(410.f, 360.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[15]->render(images_elems[3]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(194.f, 400.f, 0.f));
		textureQuadProgram.setUniformMatrix4f("modelview", modelview);
		elements[22]->render(images_elems[7]);
	}
}

void Instructions::initShaders()
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