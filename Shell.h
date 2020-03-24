#pragma once

#include "Object.h"

class Shell : public Object
{
public:
	Shell(sf::String ImageFileAttack, int maxFrameAttackX, int maxFrameAttackY, double speed = 0, bool enemyKill = false);
	~Shell();
	bool enemyKill{ false };

private:
	int directionAttack; float range; double speed; double x0; double y0;
	int numberTield{ 1 };
	sf::Clock clock;
	double currentFrameAttackX; double currentFrameAttackY; double attackTime{3};

public:
	void startShot(double x0, double y0, int directionAttack, double range, double speed);

	// Унаследовано через Object
	virtual bool animation(int direction) override;
	virtual int update(sf::Event) override;


};

