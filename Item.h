#pragma once
#include "Object.h"
class Item :
	public Object
{
public:
	Item(sf::String ImageFile, int maxFrameX, int maxFrameY, double speed);
	~Item();
	static std::vector<Item*> items;
	virtual int action(Object* obj) = 0;
	// Унаследовано через Object
	virtual int actionCollisionObjects(Object *obj) override;
	virtual bool animation(int direction) override;
	virtual int update(sf::Event) override;
};

