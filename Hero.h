#pragma once
#include "Header.h"
class Hero
{
protected:
	sf::Image *image;
	sf::Texture *texture;
	sf::Sprite* sprite;


	double x, y, dx, dy, speed;
	float currentFrameX{ 0 }; float currentFrameY{ 0 }; int maxFrameX{ 1 }; int maxFrameY{ 1 }; int countX{ 1 }; int countY{ 1 }; int x0{ 0 }; int y0{ 0 };

public:
	Hero(sf::String ImageFile, int maxFrameX, int maxFrameY, float x, float y, float speed = 0);
	~Hero();
	sf::Sprite getSprite();
	bool setPos(double x, double y);
	bool setMaxFrames(int countX, int countY);
	virtual void move(double x, double y);
	virtual void animation(int direction);
};

