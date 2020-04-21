#include "Shell.h"

#include <iostream>
#include "Hero.h"
extern float mainTime;
extern double speedAnimation;
Shell::Shell(sf::String ImageFileAttack, int maxFrameAttackX, int maxFrameAttackY, double speed, int damage, bool enemyKill) : Object(ImageFileAttack, maxFrameAttackX, maxFrameAttackY, speed)
{
	this->enemyKill = enemyKill;
	this->damage = damage;
	this->setCollisionTieldsFlag(1);
	this->setCollisionObjectsFlag(0);
}

Shell::~Shell()
{
}

/*
1 - left
2 - right
3 - up
4 - down
*/
void Shell::startShot(double x0, double y0, int directionAttack, double range, double speed)
{
	setPos(x0, y0);
	this->directionAttack = directionAttack;
	this->range = range;
	this->speed = speed;
	this->x0 = x0;
	this->y0 = y0;

	animation(directionAttack);
}

int Shell::update(sf::Event)
{
	
	return updateAnimation();
}


void Shell::makeShell(sf::String ImageFileAttack, int maxFrameAttackX, int maxFrameAttackY, double speed, int damage, bool enemyKill, Hero& hero, int direction)
{
	shells.push_back(new Shell(ImageFileAttack, maxFrameAttackX, maxFrameAttackY, speed, damage, enemyKill));//Player player(*camera, "resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, 1, 1, 500, 500, speedPlayer, speedPlayerAttack);
	switch (direction)
	{
	case 1:// left
	{
		shells.back()->startShot((hero.getSprite().getPosition().x - hero.getSizeXY().sizeX + distanceAttackingObject), hero.getSprite().getPosition().y, 1, hero.getStats().attackRange, hero.getStats().attackSpeed);
		break;
	}
	case 2:// right
	{
		shells.back()->startShot((hero.getSprite().getPosition().x + hero.getSizeXY().sizeX - distanceAttackingObject), hero.getSprite().getPosition().y, 2, hero.getStats().attackRange, hero.getStats().attackSpeed);
		break;
	}
	case 3:// up
	{
		shells.back()->startShot(hero.getSprite().getPosition().x, (hero.getSprite().getPosition().y - hero.getSizeXY().sizeY + distanceAttackingObject), 3, hero.getStats().attackRange, hero.getStats().attackSpeed);
		break;
	}
	case 4:// down
	{
		shells.back()->startShot(hero.getSprite().getPosition().x, (hero.getSprite().getPosition().y + hero.getSizeXY().sizeY - distanceAttackingObject), 4, hero.getStats().attackRange, hero.getStats().attackSpeed);
		break;
	}
	default:
		break;
	}
	
}

void Shell::checkIntersectsObjectsUpdate(const sf::Event& event)
{
	for (int i = 0; i < shells.size(); ++i)
	{
		if (shells.at(i)->update(event) == -1)
		{
			delete shells[i];
			shells.erase(shells.begin() + i);

			--i;
			continue;
		}
	}
}

/*1
1 - left
2 - right
3 - up
4 - down
*/
bool Shell::animation(int direction)
{
	double way = sqrt(pow(getPosition().x - x0, 2) + pow(getPosition().y - y0, 2));

	switch (direction)
	{
	case 1:// 1 - left
	{
		// если появится противник с неогр дальностью, может пригодиться 
		//currentFrameX += 9 * pow(10, -7) * mainTime; // magicNumbers - timeFly
		//if (currentFrameX > movementTexture.maxFrameX)
		//{
		//	currentFrameX = 0;
		//	return true;
		//}
		//std::cout << getPosition().x << " " << getPosition().y << " " << x0 << " " << y0 << std::endl << pow(getPosition().x - x0, 2) << " " << pow(getPosition().y - y0, 2) << std::endl;

		if (way > ((currentFrameX + 1) * range) / this->movementTexture.maxFrameX)
			++currentFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(currentFrameX), getSizeXY().sizeY, getSizeXY().sizeX, getSizeXY().sizeY));//(sizeX) * int(currentFrameY) + sizeX
		break;
	}
	case 2:// 2 - right
	{
		if (way > ((currentFrameX + 1) * range) / this->movementTexture.maxFrameX)
			++currentFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(currentFrameX), 2 * getSizeXY().sizeY, getSizeXY().sizeX, getSizeXY().sizeY));//(sizeX) * int(currentFrameY) + sizeX
		break;
	}
	case 3://3 - up
	{
		if (way > ((currentFrameY + 1) * range) / this->movementTexture.maxFrameX)
			++currentFrameY;
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(currentFrameY), 3 * getSizeXY().sizeY, getSizeXY().sizeX, getSizeXY().sizeY));//(sizeX) * int(currentFrameY) + sizeX
		break;
	}
	case 4://4 - down
	{
		if (way > ((currentFrameY + 1) * range) / this->movementTexture.maxFrameX)
			++currentFrameY;
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(currentFrameY), 0, getSizeXY().sizeX, getSizeXY().sizeY));//(sizeX) * int(currentFrameY) + sizeX
		break;
	}
	}
	return false;
}

int Shell::actionCollisionObjects()
{
	return 0;
}

int Shell::updateAnimation()
{
	// speed * range
	//double attackTime = 3;
	double way = sqrt(pow(getPosition().x - x0, 2) + pow(getPosition().y - y0, 2));
	if (way > range)
		return -1;
	// Да, проверка именно здесь, чтобы игрок увидел, последний показывающийся спрайт
	switch (directionAttack)
	{
	case 1:// 1 - left
	{
		animation(1);
		return this->move(-(speed), 0);
	}
	case 2:// 2 - right
	{
		animation(2);
		return this->move(speed, 0);
	}
	case 3://3 - up
	{
		animation(3);
		return this->move(0, -(speed));
	}
	case 4://4 - down
	{
		animation(4);
		return this->move(0, speed);
	}
	default:
		break;
	}
	return -100;
}
