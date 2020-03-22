#include "Hero.h"

#include <iostream>
extern float mainTime;
extern double speedAnimation;
Hero::Hero(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed, double attackTime, double attackRange, double attackSpeed) : Object(ImageFile, maxFrameX, maxFrameY, speed)
{
	this->attackTime = attackTime;
	this->attackRange = attackRange;
	this->attackSpeed = attackSpeed;
	speedOneFrame = attackTime / movementTexture.maxFrameX;
	this->setPos(x, y);
}
Hero::~Hero()
{
}

int Hero::update(sf::Event event)
{
	return 0;
}

void Hero::resetAnimationAttack()
{
	clock.restart();//currentFrameAttackY += speedAnimation * mainTime;
	numberTield = 1;
	currentFrameAttackX = 0;
	currentFrameAttackY = 0;
}

bool Hero::animation(int direction)// 1 - left, 2 - right, 3 - up, 4 - down
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
		if (clock.getElapsedTime().asSeconds() < numberTield * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(numberTield - 1), 6 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		}
		else
		{
			if (clock.getElapsedTime().asSeconds() > attackTime)
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
		if (clock.getElapsedTime().asSeconds() < numberTield * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(numberTield - 1), 7 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		}
		else
		{
			if (clock.getElapsedTime().asSeconds() > attackTime)
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
		if (clock.getElapsedTime().asSeconds() < numberTield * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(numberTield - 1), 8 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		}
		else
		{
			if (clock.getElapsedTime().asSeconds() > attackTime)
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
		if (clock.getElapsedTime().asSeconds() < numberTield * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(numberTield - 1), 9 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		}
		else
		{
			if (clock.getElapsedTime().asSeconds() > attackTime)
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
			currentFrameY -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((getSizeXY().sizeX) * int(currentFrameY), 10 * getSizeXY().sizeX, getSizeXY().sizeX, getSizeXY().sizeY));
		break;
	}
	default:
		break;
	}
	return false;

}
