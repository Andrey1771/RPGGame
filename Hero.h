#pragma once
#include "Header.h"

#include <SFML/Graphics.hpp>
#include "Object.h"

class Hero : public Object
{
public:
	Hero(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, double speed = 0, double attackTime = 0, double attackRange = 0, double attackSpeed = 0);
	~Hero();
private:
	float currentFrameAttackX{ 0 }; float currentFrameAttackY{ 0 };
	
	bool temp{ false };
	int numberTield{ 1 };
	sf::Clock clock;
	double speedOneFrame;

	virtual int actionCollisionObjects() override;
protected:
	double attackTime{ 0 }; double attackRange{ 0 }; double attackSpeed{ 0 };
	double healthPoints;
public:

	double getSpeed();
	// Унаследовано через Object
	virtual bool animation(int direction) override;
	virtual int update(sf::Event) override;
	void resetAnimationAttack();

	//static bool attackAnimation(bool& temp, sf::Clock& clock, int& tempK, float& currentFrameAttackX, float& currentFrameAttackY, double attackTime, textureData& movementTexture, int& sizeX, int& sizeY, int direction);
};

