#include "ProgressBar.h"
#include <iostream>
ProgressBar::ProgressBar(sf::View* view, sf::String ImageFile, int range, int value, XY xy, SizeXY sizeXY, int maxFrameX, int maxFrameY)
{
	//Movement
	movementTexture.image = new sf::Image;
	movementTexture.texture = new sf::Texture;
	movementTexture.sprite = new sf::Sprite;

	movementTexture.image->loadFromFile(ImageFile);//sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed, double attackTime)
	movementTexture.texture->loadFromImage(*movementTexture.image);
	
	movementTexture.sprite->setTexture(*movementTexture.texture);
	movementTexture.maxFrameX = maxFrameX;
	movementTexture.maxFrameY = maxFrameY;

	movementTexture.sprite->setTextureRect(sf::IntRect(0, 0, movementTexture.image->getSize().x / movementTexture.maxFrameX, movementTexture.image->getSize().y / movementTexture.maxFrameY));
	this->range = range;
	this->value = value;
	this->xy.x = xy.x;// В падлу реализовывать перегрузку оператора из-за 2 строчек) Хотя это easy
	this->xy.y = xy.y;
	this->sizeXY.sizeX = sizeXY.sizeX;
	this->sizeXY.sizeY = sizeXY.sizeY;
	this->view = view;
	updatePosition();
}

void ProgressBar::updatePosition()
{
	spritesBar.clear();
	for (int i = 0; i < range; i += 2)
	{
		for (int k = movementTexture.maxFrameX; k > 0; --k)
		{
			if (value - (i + k - 2) > 0)
			{
				movementTexture.sprite->setPosition(sf::Vector2f(xy.x + view->getCenter().x - view->getSize().x / 2 + (movementTexture.image->getSize().x / movementTexture.maxFrameX) * int(i / 2), xy.y + view->getCenter().y - view->getSize().y / 2));

				movementTexture.sprite->setTextureRect(sf::IntRect((movementTexture.image->getSize().x / movementTexture.maxFrameX) * (movementTexture.maxFrameX - k), 0, movementTexture.image->getSize().x / movementTexture.maxFrameX, movementTexture.image->getSize().y / movementTexture.maxFrameY));
				spritesBar.push_back(*(movementTexture.sprite));
				break;
			}
			if (k == 1)
			{
				movementTexture.sprite->setPosition(sf::Vector2f(xy.x + view->getCenter().x - view->getSize().x / 2 + (movementTexture.image->getSize().x / movementTexture.maxFrameX) * int(i / 2), xy.y + view->getCenter().y - view->getSize().y / 2));
				movementTexture.sprite->setTextureRect(sf::IntRect((movementTexture.image->getSize().x  / movementTexture.maxFrameX) * (movementTexture.maxFrameX - k), 0, movementTexture.image->getSize().x / movementTexture.maxFrameX, movementTexture.image->getSize().y / movementTexture.maxFrameY));
				spritesBar.push_back(*(movementTexture.sprite));
			}
		}
	}
}

void ProgressBar::setValue(int newValue)
{
	value = newValue;
}

int ProgressBar::update()
{
	if (hero != nullptr)
	{
		range = hero->getMaxHealthPoints();
		value = hero->getHealthPoints();
	}

	updatePosition();
	return 0;
}

const std::vector<sf::Sprite>& ProgressBar::getSpritesBar()
{
	return spritesBar;
}

void ProgressBar::setView(sf::View* view)
{
	this->view = view;
}

void ProgressBar::setSizeXY(const SizeXY& sizeXY)
{
	xy.x = sizeXY.sizeX;
	xy.y = sizeXY.sizeY;
}
