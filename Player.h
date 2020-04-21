#pragma once
#include "Hero.h"
#include <SFML/Graphics.hpp>

class Player :
	public Hero
{
private:
	int keyPressed{ 0 };
public:
	Player(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, const Stats& stats);
	~Player();
	
	// ������������ ����� Hero
	virtual int update(sf::Event event) override;
private:
	bool moveHero(sf::Event event);
	void attackHero(sf::Event event, bool ok);
	// ������������ ����� Hero
	virtual bool animation(int direction) override;

	static std::vector<Player*> players;
};

