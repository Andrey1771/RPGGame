#include "Shell.h"
#include "Header.h"
#include <iostream>
#include "Hero.h"
#include <cmath>


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
X:
1 - left
2 - right
Y:
1 - up
2 - down
*/
void Shell::startShot(double x0, double y0, int directionAttackX, int directionAttackY, double range, double speed, float angle)
{
	setPos(x0, y0);
	this->directionAttackX = directionAttackX;
	this->directionAttackY = directionAttackY;
	this->range = range;
	this->speed = speed;
	this->x0 = x0;
	this->y0 = y0;
	this->angle = angle;

	//updateAnimation();
}

int Shell::update(sf::Event)
{

	return updateAnimation();
}


void Shell::makeShell(sf::String ImageFileAttack, int maxFrameAttackX, int maxFrameAttackY, double speed, int damage, bool enemyKill, Hero& hero, int directionX, int directionY, float angle)
{
	shells.push_back(new Shell(ImageFileAttack, maxFrameAttackX, maxFrameAttackY, speed, damage, enemyKill));//Player player(*camera, "resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, 1, 1, 500, 500, speedPlayer, speedPlayerAttack);

	float tan = std::tan(angle * PI / 180.0);
	float speedX = sqrt(pow(speed, 2) / (1 + pow(tan, 2)));
	float speedY = sqrt(pow(speed, 2) - pow(speedX, 2));

	if (directionY == 1)// 1 - left
		speedY = -speedY;

	if (directionX == 1)// 1 - up
		speedX = -speedX;

	if (abs(speedX) > abs(speedY))
	{
		if (speedX < 0)
			shells.back()->startShot((hero.getSprite().getPosition().x - hero.getSizeXY().sizeX + distanceAttackingObject), hero.getSprite().getPosition().y, directionX, directionY, hero.getStats().attackRange, hero.getStats().attackSpeed, angle);
		else
			shells.back()->startShot((hero.getSprite().getPosition().x + hero.getSizeXY().sizeX - distanceAttackingObject), hero.getSprite().getPosition().y, directionX, directionY, hero.getStats().attackRange, hero.getStats().attackSpeed, angle);
	}
	else
	{
		if (speedY < 0)
			shells.back()->startShot(hero.getSprite().getPosition().x, (hero.getSprite().getPosition().y - hero.getSizeXY().sizeY + distanceAttackingObject), directionX, directionY, hero.getStats().attackRange, hero.getStats().attackSpeed, angle);
		else
			shells.back()->startShot(hero.getSprite().getPosition().x, (hero.getSprite().getPosition().y + hero.getSizeXY().sizeY - distanceAttackingObject), directionX, directionY, hero.getStats().attackRange, hero.getStats().attackSpeed, angle);
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

int Shell::actionCollisionObjects(Object* obj)
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
	float speedX, speedY;

	float tan = std::tan(angle * PI / 180.0);
	speedX = sqrt(pow(speed, 2) / (1 + pow(tan, 2)));
	speedY = sqrt(pow(speed, 2) - pow(speedX, 2));


	if (directionAttackY == 1)// 1 - up
	{
		speedY = -speedY;
	}

	if (directionAttackX == 1)// 1 - left
	{
		speedX = -speedX;
	}

	if (abs(speedX) > abs(speedY))
	{
		if (speedX < 0)// if (angle < 0)
			animation(1);
		else
			animation(2);
	}
	else
	{
		if (speedY > 0)
			animation(4);
		else
			animation(3);
	}
	return this->move(speedX, speedY);
}
