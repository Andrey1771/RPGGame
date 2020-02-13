#include "Hero.h"

extern float mainTime;
extern double speedAnimation;
Hero::Hero(sf::String ImageFile, int maxFrameX, int maxFrameY, float x, float y, float speed)
{
	image = new sf::Image;
	texture = new sf::Texture;
	sprite =new sf::Sprite;

	image->loadFromFile(ImageFile);
	texture->loadFromImage(*image);

	sprite->setTexture(*texture);

	int sizeX = image->getSize().x / maxFrameX;// Можно оптимизировать
	int sizeY = image->getSize().y / maxFrameY;//
	sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameX), 0, sizeX, sizeY));

	this->maxFrameX = maxFrameX;
	this->maxFrameY = maxFrameY;
	this->x = x;//пересмотреть
	this->y = y;//
	this->speed = speed;
	//this->dx = dx;//
	//this->dy = dy;//
	this->setPos(x, y);
}
Hero::~Hero()
{
	delete sprite;
	delete texture;
	delete image;
}
sf::Sprite Hero::getSprite()
{
	return *sprite;
}
bool Hero::setPos(int x,int y)
{
	sprite->setPosition(x, y);
	return true;
}
bool Hero::setMaxFrames(int countX, int countY)
{
	this->maxFrameX = countX;
	this->maxFrameY = countY;
	return true;
}
void Hero::move(int x, int y)
{
	sprite->move(x,y);
}

void Hero::animation(int direction)// 1 - left, 2 - right, 3 - up, 4 - down
{
	int sizeX = image->getSize().x / maxFrameX;// Можно оптимизировать
	int sizeY = image->getSize().y / maxFrameY;//

	switch (direction)
	{
	case 1:
	{
		currentFrameX += speedAnimation * mainTime;
		if (currentFrameX > maxFrameX)
			currentFrameX -= maxFrameX;
		sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameX), sizeY, sizeX, sizeY));//(sizeX) * int(currentFrameY) + sizeX
		break;
	}
	case 2:
	{
		currentFrameX += speedAnimation * mainTime;
		if (currentFrameX > maxFrameX)
			currentFrameX -= maxFrameX;
		sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameX), 2 * sizeX, sizeX, sizeY));
		break;
	}
	case 3:
	{
		currentFrameY += speedAnimation * mainTime;
		if (currentFrameY > maxFrameX)
			currentFrameY -= maxFrameX;
		sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameY), 3 * sizeX, sizeX, sizeY));
		break;
	}
	case 4:
	{
		currentFrameY += speedAnimation * mainTime;
		if (currentFrameY > maxFrameX)
			currentFrameY -= maxFrameX;
		sprite->setTextureRect(sf::IntRect((sizeY) * int(currentFrameY), 0, sizeX, sizeY));
		break;
	}
	default:
		break;
	}

}
