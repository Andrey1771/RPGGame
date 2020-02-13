#pragma once
#include <SFML/Graphics.hpp>
class Map
{
private:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Map(sf::String ImageFolder);
	~Map();
	bool setPosBG(int w, int h);
	sf::Sprite getSprite();
};

