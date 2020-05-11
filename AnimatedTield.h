#pragma once
#include "Header.h"

class AnimatedTield
{
	float currentFrameX{ 0 }; float currentFrameY{ 0 };
	TextureData movementTexture; SizeXY valueSizeXY; sf::Sprite sprite;
	double speedAnimation;
	void animation();
public:
	AnimatedTield(const TextureData movementTexture, const SizeXY& valueSizeXY, int currentFrameY/*Ќе хочу просить ѕашка переделывать, тк он неправильно структуризировал стенки*/, double speedAnimation);
	~AnimatedTield();
	int update();
	const sf::Sprite& getSprite() { return *movementTexture.sprite; };
};

