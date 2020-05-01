#pragma once
#include "ProgressBar.h"
class HealthBar :
	public ProgressBar
{
public:
	HealthBar(sf::View* view, int range, int value, XY xy, SizeXY sizeXY);
	virtual int update() override;
};

