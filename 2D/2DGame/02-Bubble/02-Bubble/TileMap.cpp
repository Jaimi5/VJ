#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;


TileMap* TileMap::createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& texProgram)
{
	TileMap* map = new TileMap(levelFile, minCoords, texProgram);

	return map;
}


TileMap::TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& texProgram)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, texProgram);
}

TileMap::~TileMap()
{
	if (map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string& levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	map = new int[mapSize.x * mapSize.y];
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			fin.get(tile);
			if (tile == ' ') {
				map[j * mapSize.x + i] = int('a') - int('0');
			}
			else
				map[j * mapSize.x + i] = tile - int('0');
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();

	return true;
}

void TileMap::prepareArrays(const glm::vec2& minCoords, ShaderProgram& texProgram)
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile) % 13) / tilesheetSize.x, float((tile) / 13) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = texProgram.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = texProgram.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (isCollisionable(map[y * mapSize.x + x]))
			return true;
	}

	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (isCollisionable(map[y * mapSize.x + x]))
			return true;
	}

	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = pos.y / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (isCollisionable(map[y * mapSize.x + x]))
		{
			return true;
		}
	}

	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (isCollisionable(map[y * mapSize.x + x]))
		{
			return true;
		}
	}

	return false;
}

bool TileMap::isCollisionable(int pos) const
{
	if (pos == (int('a') - int('0')) ||
		pos == (int('E') - int('0')) ||
		pos == (int('m') - int('0')) ||		
		pos == (int('?') - int('0')) ||
		pos == (int('i') - int('0'))) return false;
	return true;
}

void TileMap::ChangeMapforLevel5(const glm::vec2& minCoords, ShaderProgram& texProgram, int x, int y, int level) {
	map[y * mapSize.x + x] = int('K') - int('0');	
	map[y * mapSize.x + x + 1] = int('a') - int('0');	
	map[y * mapSize.x + x + 2] = int('a') - int('0');
	map[y * mapSize.x + x + 3] = int('a') - int('0');
	map[y * mapSize.x + x + 4] = int('M') - int('0');	
	y++;
	map[y * mapSize.x + x] = int('K') - int('0');	
	map[y * mapSize.x + x + 1] = int('a') - int('0');	
	map[y * mapSize.x + x + 2] = int('a') - int('0');
	map[y * mapSize.x + x + 3] = int('a') - int('0');
	map[y * mapSize.x + x + 4] = int('M') - int('0');	
	y++;
	map[y * mapSize.x + x] = int('K') - int('0');	
	map[y * mapSize.x + x + 1] = int('a') - int('0');
	map[y * mapSize.x + x + 2] = int('a') - int('0');
	map[y * mapSize.x + x + 3] = int('a') - int('0');
	map[y * mapSize.x + x + 4] = int('M') - int('0');	
	y++;
	map[y * mapSize.x + x] = int('K') - int('0');	
	map[y * mapSize.x + x + 1] = int('a') - int('0');
	map[y * mapSize.x + x + 2] = int('a') - int('0');
	map[y * mapSize.x + x + 3] = int('a') - int('0');
	map[y * mapSize.x + x + 4] = int('M') - int('0');	
	y++;
	map[y * mapSize.x + x] = int('a') - int('0');
	map[y * mapSize.x + x + 1] = int('a') - int('0');
	map[y * mapSize.x + x + 2] = int('a') - int('0');
	map[y * mapSize.x + x + 3] = int('a') - int('0');
	map[y * mapSize.x + x + 4] = int('a') - int('0');

	if (level == 4) {
		x = 31;
		map[y * mapSize.x + x] = int('?') - int('0');
		y++;
		map[y * mapSize.x + x] = int('a') - int('0');
		y++;
		map[y * mapSize.x + x] = int('a') - int('0');
		y++;
		map[y * mapSize.x + x] = int('a') - int('0');
	}
	prepareArrays(minCoords, texProgram);
}






























