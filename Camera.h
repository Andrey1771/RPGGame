#pragma once
#include "Header.h"
#include "ProgressBar.h"
#include "Hero.h"
class Camera
{
	//sf::View* camera{ nullptr };
	
	ProgressBar* progressBarHP;
	sf::View* view{ nullptr };
	Hero* hero{ nullptr };
	float x0, y0, tieldsWidth, tieldsHeight, width, height;
	void setCoordinationCamera(float x0, float y0, float width, float height);
public:
	Camera(Hero* hero, sf::View* view, float tieldsWidth, float tieldsHeight, float width, float height);
	const sf::View* getView();
	void setHero(Hero* hero);
	void setView(sf::View* view);
	void setMapXYAndSize(float x0, float y0, float width, float height) { this->x0 = x0; this->y0 = y0; this->width = width; this->height = height; };
	ProgressBar* getProgressBar();
	void update();
};

