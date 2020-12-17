#pragma once
#include "ProgressBar.h"
class HealthBar :
	public ProgressBar
{
public:
	HealthBar(sf::View* view, int range, int value, UtilitiesGame::XY xy, UtilitiesGame::SizeXY sizeXY);
	virtual int update() override;
};

