#include "Map.h"
#include <vector>
Map::Map(sf::String ImageFolder)
{
	this->image.loadFromFile(ImageFolder);
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);

	//std::vector<std::vector<std::string>> mapMassive;
	//mapMassive.push_back()
}
Map::~Map()
{

}

bool Map::setPosBG(int w, int h)
{
	//this->sprite.setPosition(w - image.getSize().x / 2, h - image.getSize().y / 2);
	this->sprite.setPosition(w - 8192/2, h - 4096/2);
	return true;
}

sf::Sprite Map::getSprite()
{
	return sprite;
}
