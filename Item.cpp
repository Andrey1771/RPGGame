#include "Item.h"
extern double speedAnimation;
extern float mainTime;
Item::Item(sf::String ImageFile, int maxFrameX, int maxFrameY, double speed) : Object(ImageFile, maxFrameX, maxFrameY, speed)
{
	items.push_back(this);
}
Item::~Item()
{
	for (int j = 0; j < Item::items.size(); ++j)
	{
		if (this == Item::items[j])
		{
			Item::items.erase(Item::items.begin() + j);
			break;
		}
	}
}
int Item::actionCollisionObjects(Object* obj)
{
	int temp = action(obj);
	this->~Item();
	return temp;
}

bool Item::animation(int direction)
{
	currentFrameX += speedAnimation * mainTime;
	if (currentFrameX > movementTexture.maxFrameX)
		currentFrameX -= movementTexture.maxFrameX;
	movementTexture.sprite->setTextureRect(sf::IntRect((valueSizeXY.sizeX) * int(currentFrameX), valueSizeXY.sizeY * int(currentFrameY), valueSizeXY.sizeX, valueSizeXY.sizeY));//(sizeX) * int(currentFrameY) + sizeX
	return false;
}

int Item::update(sf::Event)
{
	animation(0);
	return 0;
}
