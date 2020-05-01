#pragma once
#include "Header.h"
#include "Player.h"

class ProgressBar
{
	TextureData movementTexture;
	XY xy; SizeXY sizeXY;
	sf::View* view{ nullptr };
protected:
	int range, value;
	Hero* hero{ nullptr };
public:
	ProgressBar(sf::View* view, sf::String ImageFile, int range, int value, XY xy, SizeXY sizeXY, int maxFrameX, int maxFrameY);
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

