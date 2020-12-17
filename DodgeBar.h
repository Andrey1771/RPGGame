#pragma once
#include "ProgressBar.h"

class DodgeBar :
	public ProgressBar
{
	int maxFrameX;
public:
	DodgeBar(sf::View* view, int range, int value, UtilitiesGame::XY xy, UtilitiesGame::SizeXY sizeXY);
	virtual int update() override;
};

