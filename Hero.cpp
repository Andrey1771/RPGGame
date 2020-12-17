#include "Hero.h"
#include <iostream>

extern float mainTime;
extern double speedAnimation;

Hero::Hero(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, const UtilitiesGame::Stats& stats) : Object(ImageFile, maxFrameX, maxFrameY, stats.speed)
{
	this->stats = stats;
	speedOneFrame = stats.attackTime / movementTexture.maxFrameX;
	this->setPos(x, y);
	healthChange = true;
	//resetAnimationAttack();
}
Hero::~Hero()
{
}

int Hero::update(sf::Event event)
{
	if (stats.healthPoints <= 0 && deathResolution)
	{
		if (animation(11))
			return -1;
		return -2;
	}
	return 0;
}

void Hero::resetAnimationAttack()
{
	numberTield = 1;
	currentFrameAttackX = 0;
	currentFrameAttackY = 0;
	attackTime = 0;
}

void Hero::changeHealthPoints(int addHP)
{
	if (healthChange)
	{
		stats.healthPoints += addHP;
		if (stats.healthPoints > stats.maxHealthPoints)
			stats.healthPoints = stats.maxHealthPoints;
		if (stats.healthPoints < 0)
			stats.healthPoints = 0;
	}
}

void Hero::setHealthChange(bool ok)
{
	this->healthChange = ok;
}

double Hero::getSpeed()
{
	return speed;
}
// 1 - left, 2 - right, 3 - up, 4 - down
bool Hero::animation(int direction)
{
	switch (direction)
	{
	case 1:// 1 - left
	{
		currentFrameX += speedAnimation * mainTime;
		if (currentFrameX > movementTexture.maxFrameX)
			currentFrameX -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(currentFrameX), getSizeXY().sizeY, getSizeXY().sizeX, getSizeXY().sizeY));//(sizeX) * int(currentFrameY) + sizeX
		break;
	}
	case 2:// 2 - right
	{
		currentFrameX += speedAnimation * mainTime;
		if (currentFrameX > movementTexture.maxFrameX)
			currentFrameX -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(currentFrameX), 2 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		break;
	}
	case 3://3 - up
	{
		currentFrameY += speedAnimation * mainTime;
		if (currentFrameY > movementTexture.maxFrameX)
			currentFrameY -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(currentFrameY), 3 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		break;
	}
	case 4://4 - down
	{
		currentFrameY += speedAnimation * mainTime;
		if (currentFrameY > movementTexture.maxFrameX)
			currentFrameY -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeY) * int(currentFrameY), 0, getSizeXY().sizeX, getSizeXY().sizeY));
		break;
	}
	case 5://5 - inactive
	{
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeY) * 3, 0, getSizeXY().sizeX, getSizeXY().sizeY));//temp
		break;
	}
	case 6://6 - special inactive
	{
		currentFrameY += speedAnimation * mainTime;
		if (currentFrameY > movementTexture.maxFrameX)
			currentFrameY -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(currentFrameY), 5 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		break;
	}
	case 7://7 - attack down
	{
		attackTime += mainTime;
		if (attackTime/pow(10, 6) < numberTield * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(numberTield - 1), 6 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		}
		else
		{
			if (attackTime / pow(10, 6) > stats.attackTime)
			{
				resetAnimationAttack();
				return true;
			}
			else
			{
				currentFrameAttackY -= movementTexture.maxFrameX;
				numberTield++;
			}
		}
		break;
	}
	case 8://8 - attack left
	{
		attackTime += mainTime;
		if (attackTime / pow(10, 6) < numberTield * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(numberTield - 1), 7 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		}
		else
		{
			if (attackTime / pow(10, 6) > stats.attackTime)
			{
				resetAnimationAttack();
				return true;
			}
			else
			{
				currentFrameAttackX -= movementTexture.maxFrameX;
				numberTield++;
			}
		}
		break;
	}
	case 9://9 - attack right
	{
		attackTime += mainTime;
		if (attackTime / pow(10, 6) < numberTield * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(numberTield - 1), 8 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		}
		else
		{
			if (attackTime / pow(10, 6) > stats.attackTime)
			{
				resetAnimationAttack();
				return true;
			}
			else
			{
				currentFrameAttackX -= movementTexture.maxFrameX;
				numberTield++;
			}
		}
		break;

	}
	case 10://10 - attack up
	{
		attackTime += mainTime;
		if (attackTime / pow(10, 6) < numberTield * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(numberTield - 1), 9 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		}
		else
		{
			if (attackTime / pow(10, 6) > stats.attackTime)
			{
				resetAnimationAttack();
				return true;
			}
			else
			{
				currentFrameAttackY -= movementTexture.maxFrameX;
				numberTield++;
			}
		}
		break;

	}
	case 11://11 - death
	{
		currentFrameY += speedAnimation * mainTime;
		if (currentFrameY > movementTexture.maxFrameX)
		{
			currentFrameY -= movementTexture.maxFrameX;
			return true;
		}
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(currentFrameY), 10 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		break;
	}
	default:
		break;
	}
	return false;

}

int Hero::actionCollisionObjects(Object* obj)
{
	return 0;
}