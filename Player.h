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
	Player(sf::View& view, sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed = 0, double attackTime = 0);
	~Player();
	
	void setCoordinationCamera(float x0, float y0, float width, float height);

	// Унаследовано через Hero
	virtual void update(sf::Event event) override;
	
private:
	bool moveHero(sf::Event event);
	void attackHero(sf::Event event, bool ok);
	// Унаследовано через Hero
	virtual void animation(int direction) override;

};

