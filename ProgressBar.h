#pragma once
#include "Header.h"
#include "Player.h"

class ProgressBar
{
	TextureData movementTexture;
	int range, value;
	XY xy; SizeXY sizeXY;
	sf::View* view{ nullptr };
	Hero* hero{ nullptr };
public:
	ProgressBar(sf::View* view, sf::String ImageFile, int range, int value, XY xy, SizeXY sizeXY);
	void setValue(int newValue);
	virtual int update();
	const std::vector<sf::Sprite>& getSpritesBar();
	void setView(sf::View* view);
	void setSizeXY(const SizeXY& sizeXY);
	void setTrackingHero(Hero* hero) { this->hero = hero; };
private:
	void updatePosition();
	std::vector<sf::Sprite> spritesBar;
};

