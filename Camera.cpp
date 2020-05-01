#include "Camera.h"

Camera::Camera(Hero* hero, sf::View* view, float tieldsWidth, float tieldsHeight, float width, float height)
{
	x0 = 0; y0 = 0;
	this->hero = hero; this->view = view; this->tieldsWidth = tieldsWidth; this->tieldsHeight = tieldsHeight; this->width = width; this->height = height;

	view->setSize(sf::Vector2f(width, height));
	view->setCenter(width / 2, height / 2);
	progressBarHP = new ProgressBar(view, "resource\\Player\\ProgressBar\\hearts.png", 0, 0, XY(), SizeXY(tieldsWidth, tieldsHeight), 3, 1);
	progressBarHP->setTrackingHero(hero);
}

void Camera::setCoordinationCamera(float x0, float y0, float width, float height)
{
	view->setCenter(hero->getSprite().getPosition().x + hero->getSprite().getLocalBounds().width / 2.0, hero->getSprite().getPosition().y + hero->getSprite().getLocalBounds().height / 2.0);
	if (view->getCenter().x - view->getSize().x / 2 < x0)
	{
		view->setCenter(x0 + view->getSize().x / 2, view->getCenter().y);
	}
	if (view->getCenter().x + view->getSize().x / 2 > x0 + width)
	{
		view->setCenter(x0 + width - view->getSize().x / 2, view->getCenter().y);
	}
	if (view->getCenter().y - view->getSize().y / 2 < y0)
	{
		view->setCenter(view->getCenter().x, y0 + view->getSize().y / 2);
	}
	if (view->getCenter().y + view->getSize().y / 2 > y0 + height)
	{
		view->setCenter(view->getCenter().x, y0 + height - view->getSize().y / 2);
	}
}

const sf::View* Camera::getView()
{
	return view;
}

void Camera::setHero(Hero* hero)
{
	this->hero = hero;
}

void Camera::setView(sf::View* view)
{
	this->view = view;
	progressBarHP->setView(view);
}

ProgressBar* Camera::getProgressBar()
{
	return progressBarHP;
}

void Camera::update()
{
	progressBarHP->update();
	setCoordinationCamera(0, 0, width, height);
	
}
