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
	
	void setMap(sf::String* tieldMaps, int sizeWidht, int sizeHeight);
	sf::Sprite getSprite();
	std::vector<sf::Sprite> magicTieldsVector;
private:
	void tieldsSettings(int amountTieldsMap);
	
};

