#pragma once
#include "Header.h"

#include <SFML/Graphics.hpp>

struct textureData
{
	sf::Image* image;
	sf::Texture* texture;
	sf::Sprite* sprite;
	int maxFrameX{ 1 };
	int maxFrameY{ 1 };
};
struct sizeXY
{
	int sizeX;
	int sizeY;
};

class Object
{
protected:

	double dx, dy, speed;
	int countX{ 1 }; int countY{ 1 }; int x0{ 0 }; int y0{ 0 };
	float currentFrameX{ 0 }; float currentFrameY{ 0 };
	textureData movementTexture; sizeXY valueSizeXY;
public:
	

	Object(sf::String ImageFile, int maxFrameX, int maxFrameY, double speed = 0);
	~Object();
	sf::Sprite getSprite();
	bool setPos(double x, double y);
	bool setMaxFrames(int countX, int countY);
	virtual void move(double x, double y);
	virtual bool animation(int direction) = 0;
	virtual int update(sf::Event) = 0;
	const sf::Vector2f& getPosition();

	const sizeXY& getSizeXY();
};

