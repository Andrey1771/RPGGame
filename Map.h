#pragma once
#include <SFML/Graphics.hpp>
class Map
{
private:
	sf::Image image; sf::Texture texture; sf::Sprite sprite;
	int heightMap, widthMap;
	int tieldWidth, tieldHeight;
	sf::String *tieldMaps;
public:
	Map(sf::String ImageFolder, int heightMap, int widthMap, int amountTiledsMap);
	~Map();
	bool setPosBG(int w, int h);
	void loadLevel(const sf::String& mapTiledsPosition, const sf::String& tileds);
	void updateMap(sf::RenderWindow* window);
	void setSizeMap(int heightMap, int widthMap);
	const int getHeightMap();
	const int getWidthMap();
	void setMap(sf::String* tieldMaps, int sizeWidht, int sizeHeight);
	sf::Sprite getSprite();
	std::vector<std::pair<sf::Sprite, int>> magicTieldsVector;//std::pair<sf::Sprite, std::pair<int, int>> action
	//std::vector<sf::Sprite> TieldsVector;

	const int getTieldWidth(); const int getTieldHeight();
private:
	void tieldsSettings(int amountTieldsMap);
	void loadMap();

	
};

