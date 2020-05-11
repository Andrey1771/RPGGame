#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
//#include <SFML/>
#define PI 3.14159265
extern const int distanceAttackingObject;
struct TextureData
{
	sf::Image* image{ nullptr };
	sf::Texture* texture{ nullptr };
	sf::Sprite* sprite{ nullptr };
	int maxFrameX{ 1 };
	int maxFrameY{ 1 };
	//TextureData(const TextureData& texDat){}
	TextureData()
	{

	}
	/*TextureData(const TextureData& var) // оставить утечки памяти - хорошая идея?- нет, но времени мало
	{
		this->image = new sf::Image;
		this->texture = new sf::Texture;
		this->sprite = new sf::Sprite;
		*this->image = *var.image;
		*this->texture = *var.texture;
		*this->sprite = *var.sprite;
	}
	~TextureData()
	{
		delete sprite;
		delete texture;
		delete image;
	}*/
};

struct SizeXY
{
	SizeXY(int sizeX = 0, int sizeY = 0) { this->sizeX = sizeX; this->sizeY = sizeY; };
	int sizeX;
	int sizeY;
	SizeXY& operator=(const SizeXY& right)
	{
		sizeX = right.sizeX;
		sizeY = right.sizeY;
		return *this;
	}
};
struct SpeedXY
{
	double x;
	double y;
	SpeedXY(const double x = 0, const double y = 0) { this->x = x; this->y = y; };
	SpeedXY(const SpeedXY& speedXY) { this->x = speedXY.x; this->y = speedXY.y; };
};
struct XY
{
	int x, y;
	XY(int x = 0, int y = 0) { this->x = x, this->y = y; };
};
struct Stats
{
	double speed, attackTime, attackRange, attackSpeed;
	int maxHealthPoints, healthPoints;

	Stats(double speed = 0, double attackTime = 0, double attackRange = 0, double attackSpeed = 0, int maxHealthPoints = 0, int healthPoints = 0)
	{
		this->speed = speed; this->attackTime = attackTime; this->attackRange = attackRange;
		this->attackSpeed = attackSpeed; this->maxHealthPoints = maxHealthPoints; this->healthPoints = healthPoints;
	};

	Stats& operator=(const Stats& stats)
	{
		this->speed = stats.speed; this->attackTime = stats.attackTime; this->attackRange = stats.attackRange;
		this->attackSpeed = stats.attackSpeed; this->maxHealthPoints = stats.maxHealthPoints; this->healthPoints = stats.healthPoints;
		return *this;
	}
};
