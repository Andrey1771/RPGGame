#pragma once
#include "Header.h"

#include <SFML/Graphics.hpp>
#include "Object.h"

class Hero : public Object
{
public:
	Hero(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed = 0, double attackTime = 0);
	~Hero();
	float currentFrameAttackX{ 0 }; float currentFrameAttackY{ 0 };
	double attackTime;
	struct textureData attackTexture;
	virtual void attack(int direction);
	bool temp{ false };
	int tempK{ 1 };
	sf::Clock clock;

	// Унаследовано через Object
	virtual void animation(int direction) override;
	virtual void update(sf::Event) override;
};

