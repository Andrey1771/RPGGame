#include "AnimatedTield.h"
extern double  speedAnimation;
extern float mainTime;

void AnimatedTield::animation()
{
	currentFrameX += speedAnimation * mainTime;
	if (currentFrameX > movementTexture.maxFrameX)
		currentFrameX -= movementTexture.maxFrameX;
	movementTexture.sprite->setTextureRect(sf::IntRect((valueSizeXY.sizeX) * int(currentFrameX), valueSizeXY.sizeY * int(currentFrameY), valueSizeXY.sizeX, valueSizeXY.sizeY));//(sizeX) * int(currentFrameY) + sizeX
}

AnimatedTield::AnimatedTield(const TextureData movementTexture, const SizeXY& valueSizeXY, int currentFrameY/*Не хочу просить Пашка переделывать, тк он неправильно структуризировал стенки*/)
{
	this->valueSizeXY.sizeX = valueSizeXY.sizeX;
	this->valueSizeXY.sizeY = valueSizeXY.sizeY;

	this->movementTexture.image = new sf::Image;
	this->movementTexture.texture = new sf::Texture;
	this->movementTexture.sprite = new sf::Sprite;

	*this->movementTexture.image = *movementTexture.image;
	this->movementTexture.maxFrameX = movementTexture.maxFrameX;
	this->movementTexture.maxFrameY = movementTexture.maxFrameY;// не имеет смысла
	*this->movementTexture.sprite = *movementTexture.sprite;
	*this->movementTexture.texture = *movementTexture.texture;

	this->currentFrameY = currentFrameY;// эх
}

AnimatedTield::~AnimatedTield()
{
}

int AnimatedTield::update()
{
	animation();
	return 0;
}
