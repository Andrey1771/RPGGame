#include "Player.h"

extern float mainTime;
extern double speedAnimation;
Player::Player(sf::String ImageFile, int maxFrameX, int maxFrameY, float x, float y, float speed):Hero(ImageFile, maxFrameX, maxFrameY, x, y, speed)
{

}
Player::~Player()
{

}
void Player::MoveHero()
{
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

}

void Player::animation(int direction)// 1 - left, 2 - right, 3 - up, 4 - down
{
	Hero::animation(direction);
}
