#include "HealthBottle.h"
#include "Player.h"
HealthBottle::HealthBottle(int x, int y, int healthPoints) : Item("resource\\Items\\Star.png", 1, 1, 0)
{
	setPos(x, y);
	this->healthPoints = healthPoints;
}

HealthBottle::~HealthBottle()
{
}

int HealthBottle::action(Object* obj)
{
	Player* player = dynamic_cast<Player*>(obj);
	if(player != nullptr)
	{
		player->changeHealthPoints(healthPoints);
		return -1;
	}
	return 0;
}
