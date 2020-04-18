#include "Camera.h"

Camera::Camera(Hero* hero, sf::View* view, float tieldsWidth, float tieldsHeight, float width, float height)
{
	this->hero = hero; this->view = view; this->tieldsWidth = tieldsWidth; this->tieldsHeight = tieldsHeight; this->width = width; this->height = height;
	progressBarHP = new ProgressBar(view, "resource\\Player\\ProgressBar\\hearts.png", 6, 3, XY(), SizeXY(tieldsWidth, tieldsHeight));
}

void Camera::setCoordinationCamera(float x0, float y0, float width, float height)
{
	float lastX = view->getCenter().x, lastY = view->getCenter().y;
	view->setCenter(hero->getSprite().getPosition().x + hero->getSprite().getLocalBounds().width / 2.0, hero->getSprite().getPosition().y + hero->getSprite().getLocalBounds().height / 2.0);

	if (view->getCenter().x - view->getSize().x / 2 < x0 || view->getCenter().x + view->getSize().x / 2 > x0 + width)
	{
		view->setCenter(lastX, view->getCenter().y);
	}
	if (view->getCenter().y - view->getSize().y / 2 < y0 || view->getCenter().y + view->getSize().y / 2 > y0 + height)
	{
		view->setCenter(view->getCenter().x, lastY);
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
	setCoordinationCamera(0, 0, width, height);
	progressBarHP->update();
}
