#pragma once
#include "Header.h"

class Object
{
protected:

	double speed;
	int countX{ 1 }; int countY{ 1 }; int x0{ 0 }; int y0{ 0 };
	float currentFrameX{ 0 }; float currentFrameY{ 0 };
	UtilitiesGame::TextureData movementTexture; UtilitiesGame::SizeXY valueSizeXY;

	virtual int actionCollisionTields();
	virtual int actionCollisionObjects(Object* obj) = 0;
public:
	double dx, dy;

	Object(const sf::String& ImageFile, int maxFrameX, int maxFrameY, double speed = 0);
	~Object();
	sf::Sprite getSprite();
	bool setPos(double x, double y);
	bool setMaxFrames(int countX, int countY);
	virtual int move(double x, double y);
	virtual int teleport(double x, double y);
	virtual bool animation(int direction) = 0;// ����� ��������
	virtual int update(sf::Event) = 0;
	const sf::Vector2f& getPosition();

	const UtilitiesGame::SizeXY& getSizeXY();
	//static void IntersectsWalls(std::vector<Object*> &vector);
	void setCollisionTieldsFlag(const int collisionTieldsFlag);
	const int getCollisionTieldsFlag();
	void setCollisionObjectsFlag(const int collisionObjectsFlag);
	const int getCollisionObjectsFlag();
	
	static std::vector<Object*> objectsAll;
private:
	bool checkManyTieldsIntersection(UtilitiesGame::SpeedXY& speedXY, int i, int j, int direction);
	bool checkTieldsIntersection(UtilitiesGame::SpeedXY &speedXY, sf::FloatRect rect, sf::FloatRect rect2, int number, int directionFlag/*0 - �� ��������� ����������, 1 - ��������� X, 2 - ��������� Y*/);
	int collisionTieldsFlag, collisionObjectsFlag;
	
	bool checkObjectsCollision(UtilitiesGame::SpeedXY& speedXY);
	void changeIntersection(UtilitiesGame::SpeedXY& speedXY, sf::FloatRect rect2, int directionFlag/*0 - �� ��������� ����������, 1 - ��������� X, 2 - ��������� Y*/);

	bool checkTeleportIntersects(double& x, double& y);
	void checkAndChangeIJ(int& i, int& j);
};

