#include "Player.h"

extern float mainTime;
extern double speedAnimation;
Player::Player(sf::View& view, sf::String ImageFile, int maxFrameX, int maxFrameY, float x, float y, float speed):Hero(ImageFile, maxFrameX, maxFrameY, x, y, speed)
{
	this->camera = &view;
}
Player::~Player()
{

}
void Player::MoveHero()
{
	//sf::Event event;
	//event.type == sf::Event::KeyReleased;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->animation(3);
		this->move(0, -speed * mainTime);
		this->y -= speed * mainTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->animation(4);
		this->move(0, speed * mainTime);
		this->y += speed * mainTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->animation(1);
		this->move(-speed * mainTime, 0);
		this->x -= speed * mainTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->animation(2);
		this->move(speed * mainTime, 0);
		this->x += speed * mainTime;
	}
	setCoordinationCamera(0, 0, 40*64, 64*25);

}

void Player::setCoordinationCamera(float x0, float y0, float width, float height)
{
	float lastX = camera->getCenter().x, lastY = camera->getCenter().y;

	
	camera->setCenter(sprite->getPosition().x + sprite->getTextureRect().width/2.0, sprite->getPosition().y + sprite->getTextureRect().height/2.0);
	 
	if (camera->getCenter().x - camera->getSize().x / 2 < x0 || camera->getCenter().x + camera->getSize().x / 2 > x0 + width)
	{
		camera->setCenter(lastX, camera->getCenter().y);
	}
	if (camera->getCenter().y - camera->getSize().y / 2 < y0 || camera->getCenter().y + camera->getSize().y / 2 > y0 + height)
	{
		camera->setCenter(camera->getCenter().x, lastY);
	}




	//if ((camera->getCenter().x - camera->getSize().x / 2 < x0 || camera->getCenter().y - camera->getSize().y / 2 < y0) || (camera->getCenter().x + camera->getSize().x / 2 > x0 + width || camera->getCenter().y + camera->getSize().y / 2 > y0 + height))
		//camera->setCenter(lastX, lastY);
}

void Player::animation(int direction)// 1 - left, 2 - right, 3 - up, 4 - down
{
	Hero::animation(direction);
}
