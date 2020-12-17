#pragma once
#include "Header.h"
#include "Player.h"

class ProgressBar
{
	UtilitiesGame::TextureData movementTexture;
	UtilitiesGame::XY xy; UtilitiesGame::SizeXY sizeXY;
	sf::View* view{ nullptr };
protected:
	int range, value;
	Hero* hero{ nullptr };
public:
	ProgressBar(sf::View* view, sf::String ImageFile, int range, int value, UtilitiesGame::XY xy, UtilitiesGame::SizeXY sizeXY, int maxFrameX, int maxFrameY);
	void setValue(int newValue);
	virtual int update();
	const std::vector<sf::Sprite>& getSpritesBar();
	void setView(sf::View* view);
	void setSizeXY(const UtilitiesGame::SizeXY& sizeXY);
	void setTrackingHero(Hero* hero) { this->hero = hero; };

private:
	void updatePosition();
	std::vector<sf::Sprite> spritesBar;
};

