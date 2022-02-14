#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include "Menu.h"

Menu::Menu()
{
	background = NULL;
}

Menu::~Menu()
{
	if (background != NULL) delete background;
	for (int i = 0; i < 9; i++)
		if (lletra[i] != NULL)
			delete lletra[i];
}

void Menu::init()
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	Menu::initShaders();
	background = TexturedQuad::createTexturedQuad(geom, texCoords, textureProgram);
	image_background.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

	//Aquí la frase "ESC to exit"
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(25.f, 25.f);
	//lletra E
	texCoords[0] = glm::vec2(4 * (1.f / 26.f), 1 * (1.f / 5.f)); texCoords[1] = glm::vec2(5 * (1.f / 26.f), 2 * (1.f / 5.f));
	lletra[0] = TexturedQuad::createTexturedQuad(geom, texCoords, textureProgram);
	//lletra S
	texCoords[0] = glm::vec2(18 * (1.f / 26.f), 1 * (1.f / 5.f)); texCoords[1] = glm::vec2(19 * (1.f / 26.f), 2 * (1.f / 5.f));
	lletra[1] = TexturedQuad::createTexturedQuad(geom, texCoords, textureProgram);
	//lletra C
	texCoords[0] = glm::vec2(2 * (1.f / 26.f), 1 * (1.f / 5.f)); texCoords[1] = glm::vec2(3 * (1.f / 26.f), 2 * (1.f / 5.f));
	lletra[2] = TexturedQuad::createTexturedQuad(geom, texCoords, textureProgram);
	//lletra t
	texCoords[0] = glm::vec2(19 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(20 * (1.f / 26.f), 3 * (1.f / 5.f));
	lletra[3] = TexturedQuad::createTexturedQuad(geom, texCoords, textureProgram);
	//lletra o
	texCoords[0] = glm::vec2(14 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(15 * (1.f / 26.f), 3 * (1.f / 5.f));
	lletra[4] = TexturedQuad::createTexturedQuad(geom, texCoords, textureProgram);
	//lletra e
	texCoords[0] = glm::vec2(4 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(5 * (1.f / 26.f), 3 * (1.f / 5.f));
	lletra[5] = TexturedQuad::createTexturedQuad(geom, texCoords, textureProgram);
	//lletra x
	texCoords[0] = glm::vec2(23 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(24 * (1.f / 26.f), 3 * (1.f / 5.f));
	lletra[6] = TexturedQuad::createTexturedQuad(geom, texCoords, textureProgram);
	//lletra i
	texCoords[0] = glm::vec2(8 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(9 * (1.f / 26.f), 3 * (1.f / 5.f));
	lletra[7] = TexturedQuad::createTexturedQuad(geom, texCoords, textureProgram);
	//lletra t
	texCoords[0] = glm::vec2(19 * (1.f / 26.f), 2 * (1.f / 5.f)); texCoords[1] = glm::vec2(20 * (1.f / 26.f), 3 * (1.f / 5.f));
	lletra[8] = TexturedQuad::createTexturedQuad(geom, texCoords, textureProgram);

	abecedari.loadFromFile("images/letras.png", TEXTURE_PIXEL_FORMAT_RGBA);

}

void Menu::render()
{
	glm::mat4 modelview = glm::mat4(1.0f);

	textureProgram.use();
	textureProgram.setUniformMatrix4f("projection", projection);
	textureProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	textureProgram.setUniformMatrix4f("modelview", modelview);

	background->render(image_background);

	int x = 0;
	for (int i = 0; i < 11; i++) {
		if (i == 0) modelview = glm::translate(glm::mat4(1.0f), glm::vec3(i * (25.f) - (i + 1) * (4.f), CAMERA_HEIGHT - 25.f, 0.f));
		else modelview = glm::translate(glm::mat4(1.0f), glm::vec3(i * (25.f) - (i+1) * (8.f), CAMERA_HEIGHT - 25.f, 0.f));
		textureProgram.setUniformMatrix4f("modelview", modelview);
		if (i != 3 && i != 6) {
			lletra[x]->render(abecedari);
			x++;
		}
	}

}

void Menu::initShaders()
{
	Shader vShader, fShader;

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