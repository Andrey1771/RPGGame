#pragma once
#include "ProgressBar.h"

class DodgeBar :
	public ProgressBar
{
	int maxFrameX;
public:
	DodgeBar(sf::View* view, int range, int value, XY xy, SizeXY sizeXY);
	virtual int update() override;
};

