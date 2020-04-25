#include "Object.h"
#include "Map.h"
#include <iostream>

extern Map map;
extern float mainTime;
extern double speedAnimation;

const int minDistance = 0;

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
	this->setCollisionTieldsFlag(0);
	this->setCollisionObjectsFlag(1);
	objectsAll.push_back(this);
}
Object::~Object()
{
	for (int j = 0; j < Object::objectsAll.size(); ++j)
	{
		if (this == Object::objectsAll[j])
		{
			Object::objectsAll.erase(Object::objectsAll.begin() + j);
			break;
		}
	}

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
	bool ok = false;
	int i0 = movementTexture.sprite->getPosition().x / map.getTieldWidth();
	int j0 = movementTexture.sprite->getPosition().y / map.getTieldHeight();
	if ((i0 <= 0 || j0 <= 0) || (i0 >= map.getWidthMap() - 1 || j0 >= map.getHeightMap() - 1)) // Обработка исключения, когда какой-то объект выходит за пределы карты
	{
		ok = true;// Для удаления снаряда вышедшего за пределы карты
		if (ok)
			return actionCollisionTields();
		return -10;
	}

	float iObject = (movementTexture.sprite->getPosition().x + x) / map.getTieldWidth();
	float jObject = (movementTexture.sprite->getPosition().y + y) / map.getTieldHeight();
	int i = iObject;
	int j = jObject;

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

	int number; //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
	SpeedXY speedXY(x, y);
	
	if (x == 0 || y == 0)
	{
		number = i + (map.getWidthMap() * j); //+ ((map.magicTieldsVector.size() - 1) * (j - 1));

		if (x > 0)
			number++;

		if (y > 0)
			number = i + 1 + (map.getWidthMap() * (j + 1));
		if (y < 0)
			number = i + 1 + (map.getWidthMap() * (j));

		sf::FloatRect rect(movementTexture.sprite->getPosition().x + x, movementTexture.sprite->getPosition().y + y, movementTexture.sprite->getLocalBounds().width, movementTexture.sprite->getLocalBounds().height);
		sf::FloatRect rect2;
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (x == 0)
		{
			if (checkTieldsIntersection(speedXY, rect, rect2, number, 1))
				ok = true;
		}
		if (y == 0)
		{
			if (checkTieldsIntersection(speedXY, rect, rect2, number, 2))
				ok = true;
		}

		if (i != iObject && x != 0)
		{
			number = i + (map.getWidthMap() * (j + 1));
			if (x > 0)
				number++;
			rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
			rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
			rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
			rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

			if (checkTieldsIntersection(speedXY, rect, rect2, number, 2))
				ok = true;
		}

		if (j != jObject && y != 0)
		{
			if (y > 0)
				number = i + (map.getWidthMap() * (j + 1));
			if (y < 0)
				number = i+ (map.getWidthMap() * (j));

			rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
			rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
			rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
			rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

			if (checkTieldsIntersection(speedXY, rect, rect2, number, 1))
				ok = true;
		}
		//movementTexture.sprite->move(speedXY.x, speedXY.y);


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

	}
	dx = speedXY.x; dy = speedXY.y;

	checkObjectsCollision(speedXY);
	movementTexture.sprite->move(speedXY.x, speedXY.y);

	if (ok)
		return actionCollisionTields();
}

bool Object::checkManyTieldsIntersection(SpeedXY& speedXY, int i, int j, int direction)
{
	sf::FloatRect rect(movementTexture.sprite->getPosition().x + speedXY.x, movementTexture.sprite->getPosition().y + speedXY.y, movementTexture.sprite->getLocalBounds().width, movementTexture.sprite->getLocalBounds().height);
	sf::FloatRect rect2; // 01 up
	sf::FloatRect rect3; // 11 left and up
	sf::FloatRect rect4; // 10 left
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

		if (!ok)
		{
			number = i + (map.getWidthMap() * j);
			rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
			rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
			rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
			rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

			if (checkTieldsIntersection(speedXY, rect, rect3, number, 0))
				ok = true;
		}
		break;
	}
	case 1://right-down
	{

		number = i + (map.getWidthMap() * (j + 1));
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect2, number, 1))
			ok = true;
		number = i + 1 + (map.getWidthMap() * (j));
		rect4.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect4.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect4.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect4.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect4, number, 2))
			ok = true;

		if (!ok)
		{
			number = i + 1 + (map.getWidthMap() * (j + 1));
			rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
			rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
			rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
			rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

			if (checkTieldsIntersection(speedXY, rect, rect3, number, 0))
				ok = true;
		}
		break;
	}
	case 2://left-down
	{

		number = i + 1 + (map.getWidthMap() * (j + 1));
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect2, number, 1))
			ok = true;
		number = i + (map.getWidthMap() * (j));
		rect4.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect4.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect4.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect4.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect4, number, 2))
			ok = true;

		if (!ok)
		{
			number = i + (map.getWidthMap() * (j + 1));
			rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
			rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
			rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
			rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

			if (checkTieldsIntersection(speedXY, rect, rect3, number, 0))
				ok = true;

		}
		break;
	}case 3://right-up
	{

		number = i + (map.getWidthMap() * (j));
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect2, number, 1))
			ok = true;
		number = i + 1 + (map.getWidthMap() * (j + 1));
		rect4.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect4.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect4.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect4.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

		if (checkTieldsIntersection(speedXY, rect, rect4, number, 2))
			ok = true;

		if (!ok)
		{
			number = i + 1 + (map.getWidthMap() * j);
			rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
			rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
			rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
			rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;

			if (checkTieldsIntersection(speedXY, rect, rect3, number, 0))
				ok = true;
		}
		break;
	}
	default:
	{
		break;
	}
	}
	return ok;
}

bool Object::checkTieldsIntersection(SpeedXY& speedXY, sf::FloatRect rect, sf::FloatRect rect2, int number, int directionFlag/*0 - не блокирует координаты, 1 - блокирует X, 2 - блокирует Y*/)
{
	if ((!rect2.intersects(rect)) || (map.magicTieldsVector.at(number).second >> 1 != 1))
	{

		return false;
	}
	else
	{
		changeIntersection(speedXY, rect2, directionFlag);
		return true;
	}

}

bool Object::checkObjectsCollision(SpeedXY& speedXY)
{
	switch (collisionObjectsFlag)
	{
	case 0:// Пересечение разрешено
	{
		break;
	}
	case 1:// Пересечение запрещено
	{
		sf::FloatRect rect(getSprite().getPosition().x + speedXY.x, getSprite().getPosition().y + speedXY.y, getSprite().getLocalBounds().width, getSprite().getLocalBounds().height);
		sf::FloatRect rect2;
		sf::FloatRect rect3(getSprite().getPosition().x, getSprite().getPosition().y, getSprite().getLocalBounds().width, getSprite().getLocalBounds().height);
		for (Object* var : objectsAll) // O(n) Можно оптимизировать в будущем
		{
			if (var == this || var->collisionObjectsFlag == 0)
				continue;

			rect2.left = var->getSprite().getPosition().x;
			rect2.top = var->getSprite().getPosition().y;
			rect2.width = var->getSprite().getLocalBounds().width;
			rect2.height = var->getSprite().getLocalBounds().height;

			if (rect.intersects(rect2))
			{
				if (speedXY.x == 0)
				{
					changeIntersection(speedXY, rect2, 1);
					continue;
				}
				if (speedXY.y == 0)
				{
					changeIntersection(speedXY, rect2, 2);
					continue;
				}

				if (speedXY.x > 0 && speedXY.y > 0)
				{
					if (abs(rect3.top - rect2.top) == abs(rect3.left - rect2.left))
					{
						changeIntersection(speedXY, rect2, 0);
					}

					if (abs(rect3.top - rect2.top) > abs(rect3.left - rect2.left))
					{
						changeIntersection(speedXY, rect2, 1);

					}
					if (abs(rect3.top - rect2.top) < abs(rect3.left - rect2.left)/* && speedXY.y > 0*/)
					{
						changeIntersection(speedXY, rect2, 2);
					}
				}
				if (speedXY.x < 0 && speedXY.y > 0)
				{
					if (abs(rect3.top - rect2.top) == abs(rect3.left - rect2.left))
					{
						changeIntersection(speedXY, rect2, 0);
					}

					if (abs(rect3.top - rect2.top) > abs(rect3.left - rect2.left))
					{
						changeIntersection(speedXY, rect2, 1);
					}
					if (abs(rect3.top - rect2.top) < abs(rect3.left - rect2.left)/* && speedXY.y > 0*/)
					{
						changeIntersection(speedXY, rect2, 2);
					}
				}
				if (speedXY.x > 0 && speedXY.y < 0)
				{
					if (abs(rect3.top - rect2.top) == abs(rect3.left - rect2.left))
					{
						changeIntersection(speedXY, rect2, 0);
					}

					if (abs(rect3.top - rect2.top) > abs(rect3.left - rect2.left))
					{
						changeIntersection(speedXY, rect2, 1);
					}
					if (abs(rect3.top - rect2.top) < abs(rect3.left - rect2.left)/* && speedXY.y > 0*/)
					{
						changeIntersection(speedXY, rect2, 2);
					}
				}
				if (speedXY.x < 0 && speedXY.y < 0)
				{
					if (abs(rect3.top - rect2.top) == abs(rect3.left - rect2.left))
					{
						changeIntersection(speedXY, rect2, 0);
					}

					if (abs(rect3.top - rect2.top) > abs(rect3.left - rect2.left))
					{
						changeIntersection(speedXY, rect2, 1);
					}
					if (abs(rect3.top - rect2.top) < abs(rect3.left - rect2.left)/* && speedXY.y > 0*/)
					{
						changeIntersection(speedXY, rect2, 2);
					}
				}
			}
		}

		break;
	}
	default:
	{
		break;
	}
	}
	return false;
}

void Object::changeIntersection(SpeedXY& speedXY, sf::FloatRect rect2, int directionFlag/*0 - не блокирует координаты, 1 - блокирует X, 2 - блокирует Y*/)//, int actionType /*0 - move, 1 - interaction*/
{
	double newX, newY;
	double rangeX, rangeY;
	sf::FloatRect rectNew(movementTexture.sprite->getPosition().x, movementTexture.sprite->getPosition().y, movementTexture.sprite->getLocalBounds().width, movementTexture.sprite->getLocalBounds().height);
	rangeX = abs(abs(rect2.left - rectNew.left) - rect2.width);
	rangeY = abs(abs(rect2.top - rectNew.top) - rect2.height);
	// Скрытая ошибка с размерами, но тк размеры игрока и тайлов одинаковые, она не проявляется
	newX = std::min(rangeX, abs(speedXY.x)) * (speedXY.x / abs(speedXY.x));//rect3.top
	newY = std::min(rangeY, abs(speedXY.y)) * (speedXY.y / abs(speedXY.y));

	if (rangeX <= minDistance)
		newX = 0;
	if (rangeY <= minDistance)
		newY = 0;

	if (speedXY.x == 0)
		newX = 0;
	if (speedXY.y == 0)
		newY = 0;

	switch (directionFlag)
	{
	case 0:
	{
		speedXY.x = newX;
		speedXY.y = newY;
		break;
	}
	case 1:
	{
		speedXY.y = newY;
		break;
	}
	case 2:
	{
		speedXY.x = newX;
		break;
	}
	default:
	{
		break;
	}
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

int Object::actionCollisionTields()
{
	switch (collisionTieldsFlag)
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

void Object::setCollisionTieldsFlag(const int collisionTieldsFlag)
{
	this->collisionTieldsFlag = collisionTieldsFlag;
}

const int Object::getCollisionTieldsFlag()
{
	return collisionTieldsFlag;
}

void Object::setCollisionObjectsFlag(const int collisionObjectsFlag)
{
	this->collisionObjectsFlag = collisionObjectsFlag;
}

const int Object::getCollisionObjectsFlag()
{
	return collisionObjectsFlag;
}
