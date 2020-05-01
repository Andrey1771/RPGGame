#include "DodgeBar.h"
#include <iostream>
DodgeBar::DodgeBar(sf::View* view, int range, int value, XY xy, SizeXY sizeXY) : ProgressBar(view, "resource\\Player\\ProgressBar\\Energy.png", range, value, xy, sizeXY, 5, 1)
{
	maxFrameX = 5;
}

int DodgeBar::update()
{
	Player* player = dynamic_cast<Player*>(hero);
	if (player != nullptr)
	{
		range = 1;//Energy.png
		std::cout << player->getClockDodgeDelay().getElapsedTime().asMilliseconds() << "  " << player->getDodgeDelay() << std::endl;
		value = player->getClockDodgeDelay().getElapsedTime().asMilliseconds() / (player->getDodgeDelay() / maxFrameX) - 1;// ���� ��� temp
		//if (value >= range)
		//	value = range - 1;
	}
	return ProgressBar::update();
}
