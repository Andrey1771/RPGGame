#include "AnimatedTield.h"
extern float mainTime;

void AnimatedTield::animation()
{
	currentFrameX += speedAnimation * mainTime + rand() / 3'000'000.0;
	if (currentFrameX > movementTexture.maxFrameX)
		currentFrameX -= movementTexture.maxFrameX;
	movementTexture.sprite->setTextureRect(sf::IntRect((valueSizeXY.sizeX) * int(currentFrameX), valueSizeXY.sizeY * int(currentFrameY), valueSizeXY.sizeX, valueSizeXY.sizeY));//(sizeX) * int(currentFrameY) + sizeX
}

AnimatedTield::AnimatedTield(const UtilitiesGame::TextureData movementTexture, const UtilitiesGame::SizeXY& valueSizeXY, int currentFrameY/*�� ���� ������� ����� ������������, �� �� ����������� ���������������� ������*/, double speedAnimation)
{
	this->valueSizeXY.sizeX = valueSizeXY.sizeX;
	this->valueSizeXY.sizeY = valueSizeXY.sizeY;

	this->movementTexture.image = new sf::Image;
	this->movementTexture.texture = new sf::Texture;
	this->movementTexture.sprite = new sf::Sprite;

	*this->movementTexture.image = *movementTexture.image;
	this->movementTexture.maxFrameX = movementTexture.maxFrameX;
	this->movementTexture.maxFrameY = movementTexture.maxFrameY;// �� ����� ������
	*this->movementTexture.sprite = *movementTexture.sprite;
	*this->movementTexture.texture = *movementTexture.texture;

	this->currentFrameY = currentFrameY;// ��
	this->speedAnimation = speedAnimation;
}

AnimatedTield::~AnimatedTield()
{
}

int AnimatedTield::update()
{
	animation();
	return 0;
}
