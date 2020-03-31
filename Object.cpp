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
	dx = x;
	dy = y;
	movementTexture.sprite->move(x, y);
}

int Object::update(sf::Event event)
{
	return 0;
}

const sf::Vector2f& Object::getPosition()
{
	return this->movementTexture.sprite->getPosition();
}


const sizeXY& Object::getSizeXY()
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
