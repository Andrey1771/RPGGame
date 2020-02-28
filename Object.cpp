#include "Object.h"

extern float mainTime;
extern double speedAnimation;

Object::Object(sf::String ImageFile, int maxFrameX, int maxFrameY, double x, double y, double speed)
{
	//Movement
	movementTexture.image = new sf::Image;
	movementTexture.texture = new sf::Texture;
	movementTexture.sprite = new sf::Sprite;

	movementTexture.image->loadFromFile(ImageFile);//sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed, double attackTime)
	movementTexture.texture->loadFromImage(*movementTexture.image);
	movementTexture.sprite->setTexture(*movementTexture.texture);


	int sizeX = movementTexture.image->getSize().x / maxFrameX;// Можно оптимизировать
	int sizeY = movementTexture.image->getSize().y / maxFrameY;//
	movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameX), 0, sizeX, sizeY));

	movementTexture.maxFrameX = maxFrameX;
	movementTexture.maxFrameY = maxFrameY;
	//Movement

	this->x = x;//пересмотреть
	this->y = y;//
	this->speed = speed;
	//this->dx = dx;//
	//this->dy = dy;//
	this->setPos(x, y);
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
	movementTexture.sprite->move(x, y);
}

void Object::update(sf::Event event)
{
}