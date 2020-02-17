#pragma once
#include <SFML\Graphics.hpp>

class LevelTileds
{
public:
	LevelTileds(int heightMap = -1, int widthMap = -1, sf::String* tileMap = nullptr);
	void setTileds(int heightMap, int widthMap, sf::String* tileMap);
private:

	int height, widthMap;
	sf::String* tileMap{nullptr};

};

