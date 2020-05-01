#pragma once
#include "Header.h"

#include <SFML/Graphics.hpp>
#include "Object.h"

class Hero : public Object
{
public:
	Hero(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, const Stats& stats);
	~Hero();

private:
	float currentFrameAttackX{ 0 }; float currentFrameAttackY{ 0 };
	
	bool temp{ false };
	int numberTield{ 1 };
	double speedOneFrame;
	bool healthChange;
	virtual int actionCollisionObjects(Object* obj) override;
	float attackTime;
protected:
	Stats stats;
	bool deathResolution{ true };
public:

	double getSpeed();
	// Унаследовано через Object
	virtual bool animation(int direction) override;
	virtual int update(sf::Event) override;
	void resetAnimationAttack();
	const Stats& getStats() { return stats; };
	void setMaxHealthPoints(const int maxHP) { this->stats.maxHealthPoints = maxHP; };
	void setHealthPoints(const int hp) { this->stats.healthPoints = hp; };
	const int getHealthPoints() { return stats.healthPoints; };
	const int getMaxHealthPoints() { return stats.maxHealthPoints; };
	void changeHealthPoints(int addHP);
	void setHealthChange(bool ok);
};

