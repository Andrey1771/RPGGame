#pragma once
#include "Header.h"

class AnimatedTield
{
	float currentFrameX{ 0 }; float currentFrameY{ 0 };
	TextureData movementTexture; SizeXY valueSizeXY; sf::Sprite sprite;
	void animation();
public:
	AnimatedTield(const TextureData movementTexture, const SizeXY& valueSizeXY, int currentFrameY/*�� ���� ������� ����� ������������, �� �� ����������� ���������������� ������*/);
	~AnimatedTield();
	int update();
	const sf::Sprite& getSprite() { return *movementTexture.sprite; };
};

