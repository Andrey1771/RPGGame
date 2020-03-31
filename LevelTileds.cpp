#include "LevelTileds.h"

LevelTileds::LevelTileds(int heightMap, int widthMap, sf::String* tileMap)
{
	this->height = heightMap; this->widthMap = widthMap; this->tileMap = tileMap;

}

void LevelTileds::setTileds(int heightMap, int widthMap, sf::String* tileMap)
{
	this->height = heightMap; this->widthMap = widthMap; this->tileMap = tileMap;
}
