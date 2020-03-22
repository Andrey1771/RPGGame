#pragma once
#include "Hero.h"
#include "Player.h"
class Enemy :
	public Hero
{
public:
	Enemy(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, double speed = 0, double attackTime = 0, double attackRange = 0, double attackSpeed = 0);

	virtual void artificialIntelligence(std::string styleAction);
	virtual void attack(std::string styleAttack);
	virtual void move(std::string styleMove);
	virtual int updateEnemy(sf::Event, Player* player);

	virtual int update(sf::Event) override;
};

