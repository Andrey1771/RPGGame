#pragma once
#include "Hero.h"
#include <SFML/Graphics.hpp>

class Player :
	public Hero
{
private:
	int keyPressed{ 0 };
public:
	Player(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, double speed = 0, double attackTime = 0, double attackRange = 0, double attackSpeed = 0);
	~Player();
	
	// Унаследовано через Hero
	virtual int update(sf::Event event) override;
private:
	bool moveHero(sf::Event event);
	void attackHero(sf::Event event, bool ok);
	// Унаследовано через Hero
	virtual bool animation(int direction) override;

};

