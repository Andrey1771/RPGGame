#include "DodgeBar.h"
#include <iostream>
DodgeBar::DodgeBar(sf::View* view, int range, int value, UtilitiesGame::XY xy, UtilitiesGame::SizeXY sizeXY) : ProgressBar(view, "resource\\Player\\ProgressBar\\Energy.png", range, value, xy, sizeXY, 5, 1)
{
	maxFrameX = 5;
}

int DodgeBar::update()
{
	Player* player = dynamic_cast<Player*>(hero);
	if (player != nullptr)
	{
		range = 1;//Energy.png
		value = player->getDodgeDelayTime() / (player->getDodgeDelay() * 1000 / maxFrameX) - 1;// пока так temp
	}
	return ProgressBar::update();
}
