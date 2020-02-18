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
	setCoordinationCamera(this->x, this->y);

}

void Player::setCoordinationCamera(float x, float y)
{
	camera->setCenter(sprite->getPosition().x + sprite->getTextureRect().width/2.0, sprite->getPosition().y + sprite->getTextureRect().height/2.0);
	
}

void Player::animation(int direction)// 1 - left, 2 - right, 3 - up, 4 - down
{
	Hero::animation(direction);
}
