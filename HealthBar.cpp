#include "HealthBar.h"

HealthBar::HealthBar(sf::View* view, int range, int value, XY xy , SizeXY sizeXY) : ProgressBar(view, "resource\\Player\\ProgressBar\\hearts.png", range, value, xy, sizeXY, 3, 1)
{
}

int HealthBar::update()
{
	if (hero != nullptr)
	{
		range = hero->getMaxHealthPoints();
		value = hero->getHealthPoints();
	}
	return ProgressBar::update();
}
