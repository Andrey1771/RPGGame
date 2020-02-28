#include "Hero.h"

#include <iostream>
extern float mainTime;
extern double speedAnimation;
Hero::Hero(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed, double attackTime) : Object(ImageFile, maxFrameX, maxFrameY, x, y, speed)
{

	//Attack
	attackTexture.image = new sf::Image;
	attackTexture.texture = new sf::Texture;
	attackTexture.sprite = new sf::Sprite;

	attackTexture.image->loadFromFile(ImageFileAttack);
	attackTexture.texture->loadFromImage(*attackTexture.image);
	attackTexture.sprite->setTexture(*attackTexture.texture);

	int sizeX = attackTexture.image->getSize().x / maxFrameAttackX;// Можно оптимизировать
	int sizeY = attackTexture.image->getSize().y / maxFrameAttackY;//
	attackTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameX), 0, sizeX, sizeY));

	attackTexture.maxFrameX = maxFrameAttackX;
	attackTexture.maxFrameY = maxFrameAttackY;
	//Attack

	this->attackTime = attackTime;

}
Hero::~Hero()
{
}

void Hero::attack(int direction)
{
}

void Hero::update(sf::Event event)
{
}

void Hero::animation(int direction)// 1 - left, 2 - right, 3 - up, 4 - down
{
	int sizeX = movementTexture.image->getSize().x / movementTexture.maxFrameX;// Можно оптимизировать
	int sizeY = movementTexture.image->getSize().y / movementTexture.maxFrameY;//

	switch (direction)
	{
	case 1:// 1 - left
	{
		currentFrameX += speedAnimation * mainTime;
		if (currentFrameX > movementTexture.maxFrameX)
			currentFrameX -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameX), sizeY, sizeX, sizeY));//(sizeX) * int(currentFrameY) + sizeX
		break;
	}
	case 2:// 2 - right
	{
		currentFrameX += speedAnimation * mainTime;
		if (currentFrameX > movementTexture.maxFrameX)
			currentFrameX -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameX), 2 * sizeX, sizeX, sizeY));
		break;
	}
	case 3://3 - up
	{
		currentFrameY += speedAnimation * mainTime;
		if (currentFrameY > movementTexture.maxFrameX)
			currentFrameY -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameY), 3 * sizeX, sizeX, sizeY));
		break;
	}
	case 4://4 - down
	{
		currentFrameY += speedAnimation * mainTime;
		if (currentFrameY > movementTexture.maxFrameX)
			currentFrameY -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((sizeY) * int(currentFrameY), 0, sizeX, sizeY));
		break;
	}
	case 5://5 - inactive
	{

		movementTexture.sprite->setTextureRect(sf::IntRect((sizeY) * 3, 0, sizeX, sizeY));//temp

		break;
	}
	case 6://6 - special inactive
	{
		currentFrameY += speedAnimation * mainTime;
		if (currentFrameY > movementTexture.maxFrameX)
			currentFrameY -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameY), 5 * sizeX, sizeX, sizeY));
		break;
	}
	case 7://7 - attack down
	{
		if (!temp)
		{
			clock.restart();//currentFrameAttackY += speedAnimation * mainTime;
			temp = true;
			tempK = 1;
			currentFrameAttackY = 0;
		}

		double speedOneFrame = attackTime / movementTexture.maxFrameX;
		if (clock.getElapsedTime().asSeconds() < tempK * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(tempK - 1), 6 * sizeX, sizeX, sizeY));
		}
		else
		{
			if (clock.getElapsedTime().asSeconds() > attackTime)
				temp = false;
			else
			{
				currentFrameAttackY -= movementTexture.maxFrameX;
				tempK++;
			}
		}
		break;
	}
	case 8://8 - attack left
	{

		if (!temp)
		{
			clock.restart();//currentFrameAttackY += speedAnimation * mainTime;
			temp = true;
			tempK = 1;
			currentFrameAttackX = 0;
		}

		double speedOneFrame = attackTime / movementTexture.maxFrameX;
		if (clock.getElapsedTime().asSeconds() < tempK * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(tempK - 1), 7 * sizeX, sizeX, sizeY));
		}
		else
		{
			if (clock.getElapsedTime().asSeconds() > attackTime)
				temp = false;
			else
			{
				currentFrameAttackX -= movementTexture.maxFrameX;
				tempK++;
			}
		}
		break;

	}
	case 9://9 - attack right
	{
		if (!temp)
		{
			clock.restart();//currentFrameAttackY += speedAnimation * mainTime;
			temp = true;
			tempK = 1;
			currentFrameAttackX = 0;
		}

		double speedOneFrame = attackTime / movementTexture.maxFrameX;
		if (clock.getElapsedTime().asSeconds() < tempK * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(tempK - 1), 8 * sizeX, sizeX, sizeY));
		}
		else
		{
			if (clock.getElapsedTime().asSeconds() > attackTime)
				temp = false;
			else
			{
				currentFrameAttackX -= movementTexture.maxFrameX;
				tempK++;
			}
		}
		break;

	}
	case 10://10 - attack up
	{
		if (!temp)
		{
			clock.restart();//currentFrameAttackY += speedAnimation * mainTime;
			temp = true;
			tempK = 1;
			currentFrameAttackY = 0;
		}

		double speedOneFrame = attackTime / movementTexture.maxFrameX;
		if (clock.getElapsedTime().asSeconds() < tempK * speedOneFrame)
		{
			movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(tempK - 1), 9 * sizeX, sizeX, sizeY));
		}
		else
		{
			if (clock.getElapsedTime().asSeconds() > attackTime)
				temp = false;
			else
			{
				currentFrameAttackY -= movementTexture.maxFrameX;
				tempK++;
			}
		}
		break;

	}
	case 11://11 - death
	{
		currentFrameY += speedAnimation * mainTime;
		if (currentFrameY > movementTexture.maxFrameX)
			currentFrameY -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameY), 10 * sizeX, sizeX, sizeY));
		break;
	}
	default:
		break;
	}

}