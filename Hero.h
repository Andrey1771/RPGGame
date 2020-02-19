#pragma once
#include "Header.h"

#include <SFML/Graphics.hpp>


class Hero
{
protected:
	struct textureData
	{
		sf::Image* image;
		sf::Texture* texture;
		sf::Sprite* sprite;
		int maxFrameX{ 1 };
		int maxFrameY{ 1 };
	}movementTexture, attackTexture;
	
	//sf::Image* imageAttack;
	//sf::Texture* textureAttack;
	//sf::Sprite* spriteAttack;

	double x, y, dx, dy, speed, attackTime;
	float currentFrameX{ 0 }; float currentFrameY{ 0 }; float currentFrameAttackX{ 0 }; float currentFrameAttackY{ 0 }; int countX{ 1 }; int countY{ 1 }; int x0{ 0 }; int y0{ 0 };

public:
	Hero(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed = 0, double attackTime = 0);
	~Hero();
	sf::Sprite getSprite();
	bool setPos(double x, double y);
	bool setMaxFrames(int countX, int countY);
	virtual void move(double x, double y);
	virtual void animation(int direction);
	virtual void attack(int direction);
	virtual void update(sf::Event) = 0;

};

