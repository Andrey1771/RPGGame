#pragma once
#include "Header.h"

#include <SFML/Graphics.hpp>

struct TextureData
{
	sf::Image* image;
	sf::Texture* texture;
	sf::Sprite* sprite;
	int maxFrameX{ 1 };
	int maxFrameY{ 1 };
};
struct SizeXY
{
	int sizeX;
	int sizeY;
};
struct SpeedXY
{
	double x;
	double y;
	SpeedXY(const double x = 0, const double y = 0) { this->x = x; this->y = y; };
	SpeedXY(const SpeedXY& speedXY) { this->x = speedXY.x; this->y = speedXY.y; };
};
class Object
{
protected:

	double speed;
	int countX{ 1 }; int countY{ 1 }; int x0{ 0 }; int y0{ 0 };
	float currentFrameX{ 0 }; float currentFrameY{ 0 };
	TextureData movementTexture; SizeXY valueSizeXY;
public:
	double dx, dy;

	Object(sf::String ImageFile, int maxFrameX, int maxFrameY, double speed = 0);
	~Object();
	sf::Sprite getSprite();
	bool setPos(double x, double y);
	bool setMaxFrames(int countX, int countY);
	virtual void move(double x, double y);
	virtual bool animation(int direction) = 0;// Выбор анимации
	virtual int update(sf::Event) = 0;
	const sf::Vector2f& getPosition();

	const SizeXY& getSizeXY();
	//static void IntersectsWalls(std::vector<Object*> &vector);

private:
	const double magicFun(SpeedXY& speedXY, int i, int j, int direction);
	bool magicFun2(SpeedXY &speedXY, sf::IntRect rect, sf::IntRect rect2, int number, int directionFlag/*0 - не блокирует координаты, 1 - блокирует X, 2 - блокирует Y*/);
};

