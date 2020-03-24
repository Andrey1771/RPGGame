#include "Shell.h"

#include <iostream>
#include "Hero.h"
extern float mainTime;
extern double speedAnimation;
Shell::Shell(sf::String ImageFileAttack, int maxFrameAttackX, int maxFrameAttackY, double speed, bool enemyKill) : Object(ImageFileAttack, maxFrameAttackX, maxFrameAttackY, speed)
{
	this->enemyKill = enemyKill;
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
{// speed * range
	//double attackTime = 3;
	double way = sqrt(pow(getPosition().x - x0, 2) + pow(getPosition().y - y0, 2));
	if (way > range)
		return -1;
	// Да, проверка именно здесь, чтобы игрок увидел, последний показывающийся спрайт
	switch (directionAttack)
	{
	case 1:// 1 - left
	{
		this->move(-(speed), 0);
		if (animation(1))
		{
			return -1;
		}
		break;
	}
	case 2:// 2 - right
	{
		this->move(speed, 0);
		if (animation(2))
		{
			return -1;
		}
		break;
	}
	case 3://3 - up
	{
		this->move(0, -(speed));
		if (animation(3))
		{
			return -1;
		}
		break;
	}
	case 4://4 - down
	{
		this->move(0, speed);
		if (animation(4))
		{
			return -1;
		}
		break;
	}
	default:
		break;
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