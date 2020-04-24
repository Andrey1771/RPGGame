#pragma once

#include "Object.h"
#include "Hero.h"

class Shell : public Object
{
public:
	Shell(sf::String ImageFileAttack, int maxFrameAttackX, int maxFrameAttackY, double speed = 0, int damage = 1 , bool enemyKill = false);
	~Shell();
	bool enemyKill{ false };
	static std::vector<Shell*> shells;
private:
	int directionAttack; float range; double speed; double x0; double y0;
	int numberTield{ 1 }; int damage;
	sf::Clock clock;
	double currentFrameAttackX; double currentFrameAttackY; double attackTime{3};
	virtual int actionCollisionObjects() override;
	int updateAnimation();
public:
	void startShot(double x0, double y0, int directionAttack, double range, double speed);

	// Унаследовано через Object
	virtual bool animation(int direction) override;
	virtual int update(sf::Event) override;
	const int getDamage() { return damage; };
	void setDamage(const int newDamage) { this->damage = newDamage; };

	// 1 - left, 2 - right, 3 - up, 4 - down
	static void makeShell(sf::String ImageFileAttack, int maxFrameAttackX, int maxFrameAttackY, double speed, int damage, bool enemyKill, Hero& hero, int direction);
	static void checkIntersectsObjectsUpdate(const sf::Event& event);
};

