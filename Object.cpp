#include "Object.h"
#include "Map.h"
#include <iostream>

extern Map map;
extern float mainTime;
extern double speedAnimation;

const int bad = 15;// разобраться с этим Shit-ом в будущем

Object::Object(sf::String ImageFile, int maxFrameX, int maxFrameY, double speed)
{
	//Movement
	movementTexture.image = new sf::Image;
	movementTexture.texture = new sf::Texture;
	movementTexture.sprite = new sf::Sprite;

	movementTexture.image->loadFromFile(ImageFile);//sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed, double attackTime)
	movementTexture.texture->loadFromImage(*movementTexture.image);
	movementTexture.sprite->setTexture(*movementTexture.texture);


	valueSizeXY.sizeX = movementTexture.image->getSize().x / maxFrameX;// Можно оптимизировать
	valueSizeXY.sizeY = movementTexture.image->getSize().y / maxFrameY;//
	movementTexture.sprite->setTextureRect(sf::IntRect((valueSizeXY.sizeX) * int(currentFrameX), 0, valueSizeXY.sizeX, valueSizeXY.sizeY));

	movementTexture.maxFrameX = maxFrameX;
	movementTexture.maxFrameY = maxFrameY;
	//Movement

	this->speed = speed;
	//this->dx = dx;//
	//this->dy = dy;//
	this->setCollisionFlag(0);
}
Object::~Object()
{
	delete movementTexture.sprite;
	delete movementTexture.texture;
	delete movementTexture.image;
}
sf::Sprite Object::getSprite()
{
	return *movementTexture.sprite;
}
bool Object::setPos(double x, double y)
{
	movementTexture.sprite->setPosition(x, y);
	return true;
}
bool Object::setMaxFrames(int countX, int countY)
{
	this->movementTexture.maxFrameX = countX;
	this->movementTexture.maxFrameY = countY;
	return true;
}
int Object::move(double x, double y)
{
	float iObject = (movementTexture.sprite->getPosition().x + x) / map.getTieldWidth();
	float jObject = (movementTexture.sprite->getPosition().y + y) / map.getTieldHeight();

	int i, j;

	if (abs(x) < 1)
	{
		i = (iObject); // j = (jObject + y);
	}
	else
	{
		i = (iObject + (x / abs(x)));
	}

	if (abs(y) < 1)
	{
		j = (jObject); // j = (jObject + y);

	}
	else
	{
		j = (jObject + (y / abs(y)));
	}


	if (i < 0)
	{
		i = 0;
	}
	if (j < 0)
	{
		j = 0;
	}
	if (j >= map.getHeightMap())
	{
		j = map.getHeightMap() - 1;
	}
	if (i >= map.getWidthMap())
	{
		i = map.getWidthMap() - 1;
	}
	//std::cout << "i = " << i << " j = " << j << std::endl;

	int number ; //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
	SpeedXY speedXY(x, y);
	bool ok = false;
	if (x == 0 || y == 0)
	{
		number = i + (map.getWidthMap() * j); //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
		sf::IntRect rect(movementTexture.sprite->getPosition().x + x, movementTexture.sprite->getPosition().y + y, movementTexture.sprite->getLocalBounds().width, movementTexture.sprite->getLocalBounds().height);
		sf::IntRect rect2;
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		
		if (x == 0)
		{
			ok = checkTieldsIntersection(speedXY, rect, rect2, number, 1);
		}
		if (y == 0)
		{
			ok = checkTieldsIntersection(speedXY, rect, rect2, number, 2);
		}
		movementTexture.sprite->move(speedXY.x, speedXY.y);
	}
	else
	{
		if (x > 0 && y > 0)
		{
			ok = checkManyTieldsIntersection(speedXY, i, j, 1);
		}
		if (x < 0 && y > 0)
		{
			ok = checkManyTieldsIntersection(speedXY, i, j, 2);
		}
		if (x > 0 && y < 0)
		{
			ok = checkManyTieldsIntersection(speedXY, i, j, 3);
		}
		if (x < 0 && y < 0)
		{
			ok = checkManyTieldsIntersection(speedXY, i, j, 0);
		}
		movementTexture.sprite->move(speedXY.x, speedXY.y);
	}
	dx = speedXY.x; dy = speedXY.y;
	//std::cout << "ok = " << ok << std::endl;
	if(ok)
		return actionCollisionObject();
}

bool Object::checkManyTieldsIntersection(SpeedXY& speedXY, int i, int j, int direction)
{
	sf::IntRect rect(movementTexture.sprite->getPosition().x + speedXY.x, movementTexture.sprite->getPosition().y + speedXY.y, movementTexture.sprite->getLocalBounds().width, movementTexture.sprite->getLocalBounds().height);
	sf::IntRect rect2; // 01 up
	sf::IntRect rect3; // 11 left and up
	sf::IntRect rect4; // 10 left
	int number = i + (map.getWidthMap() * j);
	SpeedXY speedXYBuf(speedXY);
	bool ok = false;

	switch (direction)
	{
	case 0://left-up
	{
		number = i + 1 + (map.getWidthMap() * j);
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect2, number, 1))
			ok = true;
		number = i + (map.getWidthMap() * (j + 1));
		rect4.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect4.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect4.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect4.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect4, number, 2))
			ok = true;
		break;
	}
	case 1://right-down
	{
		number = i - 1 + (map.getWidthMap() * j);
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect2, number, 1))
			ok = true;
		number = i + (map.getWidthMap() * (j - 1));
		rect4.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect4.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect4.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect4.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect4, number, 2))
			ok = true;
		break;
	}
	case 2://left-down
	{
		number = i + 1 + (map.getWidthMap() * j);
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect2, number, 1))
			ok = true;
		number = i + (map.getWidthMap() * (j - 1));
		rect4.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect4.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect4.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect4.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect4, number, 2))
			ok = true;
		break;
	}case 3://right-up
	{
		number = i - 1 + (map.getWidthMap() * j);
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect2, number, 1))
			ok = true;
		number = i + (map.getWidthMap() * (j + 1));
		rect4.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect4.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect4.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect4.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect4, number, 2))
			ok = true;
		break;
	}
	default:
	{
		break;
	}
	}
	return ok;
}

bool Object::checkTieldsIntersection(SpeedXY &speedXY, sf::IntRect rect, sf::IntRect rect2, int number, int directionFlag/*0 - не блокирует координаты, 1 - блокирует X, 2 - блокирует Y*/)
{
	if ((!rect2.intersects(rect)) || (map.magicTieldsVector.at(number).second != 1))
	{
		return false;
	}
	else
	{
		double newX, newY;
		double rangeX, rangeY;
		rangeX = abs(abs(rect2.left - rect.left) - rect2.width);
		rangeY = abs(abs(rect2.top - rect.top) - rect2.height);
		//std::cout << "RangeX = " << rangeX << " RangeY = " << rangeY << std::endl;
		// Скрытая ошибка с размерами, но тк размеры игрока и тайлов одинаковые, она не проявляется
		newX = std::min(rangeX, abs(speedXY.x)) * (speedXY.x / abs(speedXY.x));//rect3.top
		newY = std::min(rangeY, abs(speedXY.y)) * (speedXY.y / abs(speedXY.y));
		if (speedXY.x == 0)
			newX = 0;
		if (speedXY.y == 0)
			newY = 0;
		switch (directionFlag)
		{
		case 1:
		{
			if (rangeY <= bad)
				newY = 0;
			break;
		}
		case 2:
		{
			if (rangeX <= bad)
				newX = 0;
			break;
		}
		default:
		{
			break;
		}
		}

		speedXY.x = newX;
		speedXY.y = newY;

		//std::cout << "newX = " << newX << " newY = " << newY << " X = " << speedXY.x << " Y = " << speedXY.y << std::endl;
		return true;
	}
	
}


int Object::update(sf::Event event)
{
	return 0;
}

const sf::Vector2f& Object::getPosition()
{
	return this->movementTexture.sprite->getPosition();
}


const SizeXY& Object::getSizeXY()
{
	return valueSizeXY;
}

int Object::actionCollisionObject()
{
	switch (collisionFlag)
	{
	case 0:// Ничего
	{
		return 0;
	}
	case 1:// Удаление
	{
		return -1;
	}
	default:
	{
		return 0;
	}
	}
}

void Object::setCollisionFlag(int collisionFlag)
{
	this->collisionFlag = collisionFlag;
}

const int Object::getCollisionFlag()
{
	return collisionFlag;
}
