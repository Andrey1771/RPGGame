#pragma once
#include "Hero.h"
class Player :
	public Hero
{
private:

public:
	Player(sf::String ImageFile, int maxFrameX, int maxFrameY, float x, float y, float speed = 0);
	~Player();
	void MoveHero();


	// Унаследовано через Hero
	virtual void animation(int direction) override;

};

