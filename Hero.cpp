#include "Hero.h"

extern float mainTime;
extern double speedAnimation;
Hero::Hero(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed, double attackTime)
{
	//Movement
	movementTexture.image = new sf::Image;
	movementTexture.texture = new sf::Texture;
	movementTexture.sprite = new sf::Sprite;

	movementTexture.image->loadFromFile(ImageFile);
	movementTexture.texture->loadFromImage(*movementTexture.image);
	movementTexture.sprite->setTexture(*movementTexture.texture);


	int sizeX = movementTexture.image->getSize().x / maxFrameX;// Можно оптимизировать
	int sizeY = movementTexture.image->getSize().y / maxFrameY;//
	movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameX), 0, sizeX, sizeY));

	movementTexture.maxFrameX = maxFrameX;
	movementTexture.maxFrameY = maxFrameY;
	//Movement

	//Attack
	attackTexture.image = new sf::Image;
	attackTexture.texture = new sf::Texture;
	attackTexture.sprite = new sf::Sprite;

	attackTexture.image->loadFromFile(ImageFileAttack);
	attackTexture.texture->loadFromImage(*attackTexture.image);
	attackTexture.sprite->setTexture(*attackTexture.texture);


	sizeX = attackTexture.image->getSize().x / maxFrameAttackX;// Можно оптимизировать
	sizeY = attackTexture.image->getSize().y / maxFrameAttackY;//
	attackTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameX), 0, sizeX, sizeY));

	attackTexture.maxFrameX = maxFrameAttackX;
	attackTexture.maxFrameY = maxFrameAttackY;
	//Attack

	this->x = x;//пересмотреть
	this->y = y;//
	this->speed = speed;
	//this->dx = dx;//
	//this->dy = dy;//
	this->setPos(x, y);
}
Hero::~Hero()
{
	delete movementTexture.sprite;
	delete movementTexture.texture;
	delete movementTexture.image;

	delete attackTexture.sprite;
	delete attackTexture.texture;
	delete attackTexture.image;
}
sf::Sprite Hero::getSprite()
{
	return *movementTexture.sprite;
}
bool Hero::setPos(double x, double y)
{
	movementTexture.sprite->setPosition(x, y);
	return true;
}
bool Hero::setMaxFrames(int countX, int countY)
{
	this->movementTexture.maxFrameX = countX;
	this->movementTexture.maxFrameY = countY;
	return true;
}
void Hero::move(double x, double y)
{
	movementTexture.sprite->move(x,y);
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
		currentFrameY += speedAnimation * mainTime;
		if (currentFrameY > movementTexture.maxFrameX)
			currentFrameY -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameY), 4 * sizeX, sizeX, sizeY));
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
		
		currentFrameAttackY += speedAnimation * mainTime;
		if (currentFrameAttackY > movementTexture.maxFrameX)
			currentFrameAttackY -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameAttackY), 6 * sizeX, sizeX, sizeY));
		
		break;
	}
	case 8://8 - attack left
	{
		currentFrameAttackX += speedAnimation * mainTime;
		if (currentFrameAttackX > movementTexture.maxFrameX)
			currentFrameAttackX -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameAttackX), 7 * sizeX, sizeX, sizeY));
		break;
	}
	case 9://9 - attack right
	{
		currentFrameAttackX += speedAnimation * mainTime;
		if (currentFrameAttackX > movementTexture.maxFrameX)
			currentFrameAttackX -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameAttackX), 8 * sizeX, sizeX, sizeY));
		break;
	}
	case 10://10 - attack up
	{
		currentFrameAttackY += speedAnimation * mainTime;
		if (currentFrameAttackY > movementTexture.maxFrameX)
			currentFrameAttackY -= movementTexture.maxFrameX;
		movementTexture.sprite->setTextureRect(sf::IntRect((sizeX) * int(currentFrameAttackY), 9 * sizeX, sizeX, sizeY));
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

void Hero::attack(int direction)
{

}
