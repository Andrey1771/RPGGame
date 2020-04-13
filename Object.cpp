#include "Object.h"
#include "Map.h"
#include <iostream>

extern Map map;
extern float mainTime;
extern double speedAnimation;

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
void Object::move(double x, double y)
{
	//dx = x; dy = y;
	float iObject = (movementTexture.sprite->getPosition().x + x) / map.getTieldWidth();
	float jObject = (movementTexture.sprite->getPosition().y + y) / map.getTieldHeight();
	//std::cout << "iObject = " << iObject << " jObject = " << jObject << std::endl;

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

	std::cout << "i = " << i << " j = " << j << std::endl;
	//map.magicTieldsVector.at(0).at(0);// i like Challenges

	int number ; //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
	SpeedXY speedXY(x, y);

	if (x == 0 || y == 0)
	{
		number = i + (map.getWidthMap() * j); //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
		sf::IntRect rect(movementTexture.sprite->getPosition().x + x, movementTexture.sprite->getPosition().y + y, movementTexture.sprite->getLocalBounds().width, movementTexture.sprite->getLocalBounds().height);
		sf::IntRect rect2;
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		
		if(x == 0)
			magicFun2(speedXY, rect, rect2, number, 1);
		if(y == 0)
			magicFun2(speedXY, rect, rect2, number, 2);
		movementTexture.sprite->move(speedXY.x, speedXY.y);
	}
	else
	{
		if (x > 0 && y > 0)
		{
			magicFun(speedXY, i, j, 1);
			//number = i + (map.getWidthMap() * j); //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
		}
		if (x < 0 && y > 0)
		{
			magicFun(speedXY, i, j, 2);
			//number = i + 1 + (map.getWidthMap() * j); //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
		}
		if (x > 0 && y < 0)
		{
			magicFun(speedXY, i, j, 3);
			//number = i + (map.getWidthMap() * (j)); //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
		}
		if (x < 0 && y < 0)
		{
			magicFun(speedXY, i, j, 0);
			//number = i + 1 + (map.getWidthMap() * (j)); //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
		}
		movementTexture.sprite->move(speedXY.x, speedXY.y);
	}

	

	

	//if (x >= 0)
	//{
	//	number = i + (map.getWidthMap() * j); //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
	//	rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
	//	rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
	//	rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
	//	rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
	//}
	//else
	//{
	//	number = i + 1 + (map.getWidthMap() * j); //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
	//	rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
	//	rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
	//	rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
	//	rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
	//}

	//if (y >= 0)
	//{
	//	number = i + (map.getWidthMap() * (j)); //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
	//	rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
	//	rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
	//	rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
	//	rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
	//}
	//else
	//{
	//	number = i + (map.getWidthMap() * (j + 1)); //+ ((map.magicTieldsVector.size() - 1) * (j - 1));
	//	rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
	//	rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
	//	rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
	//	rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
	//}
	

	
}


const double Object::magicFun(SpeedXY& speedXY, int i, int j, int direction)
{
	sf::IntRect rect(movementTexture.sprite->getPosition().x + speedXY.x, movementTexture.sprite->getPosition().y + speedXY.y, movementTexture.sprite->getLocalBounds().width, movementTexture.sprite->getLocalBounds().height);
	sf::IntRect rect2; // 01 up
	sf::IntRect rect3; // 11 left and up
	sf::IntRect rect4; // 10 left
	int number = i + (map.getWidthMap() * j);
	SpeedXY speedXYBuf(speedXY);

	switch (direction)
	{
	case 0://left-up
	{
		/*rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect3, number, 0);*/
		number = i + 1 + (map.getWidthMap() * j);
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect2, number, 1);
		number = i + (map.getWidthMap() * (j + 1));
		rect4.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect4.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect4.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect4.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect4, number, 2);
		break;
	}
	case 1://right-down
	{
		/*rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect3, number, 0);*/
		number = i - 1 + (map.getWidthMap() * j);
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect2, number, 1);
		number = i + (map.getWidthMap() * (j - 1));
		rect4.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect4.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect4.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect4.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect4, number, 2);
		break;
	}
	case 2://left-down
	{
		/*rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect3, number, 0);*/
		number = i + 1 + (map.getWidthMap() * j);
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect2, number, 1);
		number = i + (map.getWidthMap() * (j - 1));
		rect4.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect4.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect4.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect4.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect4, number, 2);
		break;
	}case 3://right-up
	{
		/*rect3.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect3.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect3.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect3.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect3, number, 0);*/
		number = i - 1 + (map.getWidthMap() * j);
		rect2.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect2.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect2.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect2.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect2, number, 1);
		number = i + (map.getWidthMap() * (j + 1));
		rect4.left = map.magicTieldsVector.at(number).first.getPosition().x;
		rect4.top = map.magicTieldsVector.at(number).first.getPosition().y;
		rect4.width = map.magicTieldsVector.at(number).first.getLocalBounds().width;
		rect4.height = map.magicTieldsVector.at(number).first.getLocalBounds().height;
		magicFun2(speedXY, rect, rect4, number, 2);
		break;
	}
	default:
	{

		break;
	}
	}
	
	//std::cout << "PlayerX = " << rect.left << " PlayerY = " << rect.top << " Sprite X = " << rect3.left << " Sprite Y = " << rect3.top << std::endl;
	//if ((!rect3.intersects(rect)) || (map.magicTieldsVector.at(number).second != 1))
	//{
	//	movementTexture.sprite->move(speedXY.x, speedXY.y);
	//}
	//else
	//{
	//	double newX, newY;
	//	double rangeX, rangeY;
	//	rangeX = abs(abs(rect3.left - rect.left) - rect3.width);
	//	rangeY = abs(abs(rect3.top - rect.top) - rect3.height);
	//	std::cout << "RangeX = " << rangeX << " RangeY = " << rangeY << std::endl;
	//	// Скрытая ошибка с размерами, но тк размеры игрока и тайлов одинаковые, она не проявляется
	//	newX = std::min(rangeX, abs(speedXY.x)) * (speedXY.x / abs(speedXY.x));//rect3.top
	//	newY = std::min(rangeY, abs(speedXY.y)) * (speedXY.y / abs(speedXY.y));

	//	if (speedXY.x == 0)
	//		newX = 0;
	//	if (speedXY.y == 0)
	//		newY = 0;
	//	if (rangeX <= 15)
	//		newX = 0;
	//	if (rangeY <= 15)
	//		newY = 0;

	//	std::cout << "newX = " << newX << " newY = " << newY << " X = " << speedXY.x << " Y = " << speedXY.y << std::endl;

	//	movementTexture.sprite->move(newX, newY);
	//}
	return true;
}

bool Object::magicFun2(SpeedXY &speedXY, sf::IntRect rect, sf::IntRect rect2, int number, int directionFlag/*0 - не блокирует координаты, 1 - блокирует X, 2 - блокирует Y*/)
{
	if ((!rect2.intersects(rect)) || (map.magicTieldsVector.at(number).second != 1))
	{
		return true;
	}
	else
	{
		double newX, newY;
		double rangeX, rangeY;
		rangeX = abs(abs(rect2.left - rect.left) - rect2.width);
		rangeY = abs(abs(rect2.top - rect.top) - rect2.height);
		std::cout << "RangeX = " << rangeX << " RangeY = " << rangeY << std::endl;
		// Скрытая ошибка с размерами, но тк размеры игрока и тайлов одинаковые, она не проявляется
		newX = std::min(rangeX, abs(speedXY.x)) * (speedXY.x / abs(speedXY.x));//rect3.top
		newY = std::min(rangeY, abs(speedXY.y)) * (speedXY.y / abs(speedXY.y));
		if (speedXY.x == 0)
			newX = 0;
		if (speedXY.y == 0)
			newY = 0;
		switch (directionFlag)
		{
		case 0:
		{
			/*if (rangeX <= 45)
				newX = 0;
			if (rangeY <= 45)
				newY = 0;*/
			break;
		}
		case 1:
		{
			if (rangeY <= 15)
				newY = 0;
			break;
		}
		case 2:
		{
			if (rangeX <= 15)
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

		std::cout << "newX = " << newX << " newY = " << newY << " X = " << speedXY.x << " Y = " << speedXY.y << std::endl;
		return false;
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


//void Object::IntersectsWalls(std::vector<Object*>& vector)
//{
//	sf::IntRect rect2;
//	sf::IntRect rect3;
//
//	for (int i = 0; i < vector.size(); ++i) // O(n^2) Можно оптимизировать в будущем
//	{
//		rect2.left = vector[i]->getSprite().getPosition().x;
//		rect2.top = vector[i]->getSprite().getPosition().y;
//		rect2.width = vector[i]->getSprite().getLocalBounds().width;
//		rect2.height = vector[i]->getSprite().getLocalBounds().height;
//
//		for (sf::Sprite var : map.magicTieldsVector)
//		{
//			rect3.left = var.getPosition().x;
//			rect3.top = var.getPosition().y;
//			rect3.width = var.getLocalBounds().width;
//			rect3.height = var.getLocalBounds().height;
//			if (rect3.intersects(rect2))
//			{
//				vector[i]->move(-vector[i]->dx, -vector[i]->dy);
//				break;
//			}
//		}
//	}
//}
