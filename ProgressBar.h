#pragma once
#include "Header.h"
#include "Player.h"

class ProgressBar
{
	TextureData movementTexture;
	int range, value;
	XY xy; SizeXY sizeXY;
	Player* player;
	sf::View* view;
public:
	ProgressBar(sf::View* view, sf::String ImageFile, int range, int value, XY xy, SizeXY sizeXY);
	void setValue(int newValue);
	virtual int update();
	const std::vector<sf::Sprite>& getSpritesBar();
	void setView(sf::View* view);
private:
	void updatePosition();
	std::vector<sf::Sprite> spritesBar;
};

