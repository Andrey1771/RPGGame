#pragma once
#include "Hero.h"
#include <SFML/Graphics.hpp>
class Player :
	public Hero
{
private:
	sf::View* camera;
public:
	Player(sf::View& view, sf::String ImageFile, int maxFrameX, int maxFrameY, float x, float y, float speed = 0);
	~Player();
	void MoveHero();
	void setCoordinationCamera(float x, float y);

	// ������������ ����� Hero
	virtual void animation(int direction) override;

};

