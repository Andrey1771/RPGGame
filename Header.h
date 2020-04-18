#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
//#include <SFML/>
struct TextureData
{
	sf::Image* image{ nullptr };
	sf::Texture* texture{ nullptr };
	sf::Sprite* sprite{ nullptr };
	int maxFrameX{ 1 };
	int maxFrameY{ 1 };
};
struct SizeXY
{
	SizeXY(int sizeX = 0, int sizeY = 0) { this->sizeX = sizeX; this->sizeY = sizeY; };
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
struct XY
{
	int x, y;
	XY(int x = 0, int y = 0) { this->x = x, this->y = y; };
};