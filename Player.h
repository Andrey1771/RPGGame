#pragma once
#include "Hero.h"
#include <SFML/Graphics.hpp>
class Player :
	public Hero
{
private:
	sf::View* camera{nullptr};
	int keyPressed{ 0 };
public:
	Player(sf::View& view, sf::String ImageFile, int maxFrameX, int maxFrameY, float x, float y, float speed = 0);
	~Player();
	void MoveHero();
	void setCoordinationCamera(float x0, float y0, float width, float height);

	// Унаследовано через Hero
	virtual void animation(int direction) override;

};

