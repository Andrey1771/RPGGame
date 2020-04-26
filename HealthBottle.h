#pragma once
#include "Item.h"
class HealthBottle :
	public Item
{
	int healthPoints;
public:
	HealthBottle(int x, int y, int healthPoints = 2);
	~HealthBottle();
	// Унаследовано через Item
	virtual int action(Object* obj) override;
};

