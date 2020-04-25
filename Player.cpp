#include "Player.h"
#include "Shell.h"
#include "ProgressBar.h"
#include <iostream>
#include "Header.h"
extern float mainTime;
extern double speedAnimation;

Player::Player(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, const Stats& stats) : Hero(ImageFile, ImageFileAttack, maxFrameX, maxFrameY, x, y, stats)
{
	players.push_back(this);
}

Player::~Player()
{
	players.clear();
}

bool Player::moveHero(sf::Event event)
{
	if (event.type == sf::Event::EventType::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W)
			dy = 0;
		if (event.key.code == sf::Keyboard::S)
			dy = 0;
		if (event.key.code == sf::Keyboard::A)
			dx = 0;
		if (event.key.code == sf::Keyboard::D)
			dx = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			move(-speed * mainTime / sqrt(2), -speed * mainTime / sqrt(2));

			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
				animation(3);

			//dx = -speed * mainTime / sqrt(2);
			//dy = -speed * mainTime / sqrt(2);

			return true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			move(speed * mainTime / sqrt(2), -speed * mainTime / sqrt(2));

			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
				animation(3);

			//dx = speed * mainTime / sqrt(2);
			//dy = -speed * mainTime / sqrt(2);

			return true;
		}

		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			animation(3);
		move(0, -speed * mainTime);

		//dy = -speed * mainTime;

		return true;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{

			move(-speed * mainTime / sqrt(2), speed * mainTime / sqrt(2));

			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
				animation(4);

			//dx = -speed * mainTime / sqrt(2);
			//dy = speed * mainTime / sqrt(2);

			return true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			move(speed * mainTime / sqrt(2), speed * mainTime / sqrt(2));

			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
				animation(4);

			//dx = speed * mainTime / sqrt(2);
			//dy = speed * mainTime / sqrt(2);

			return true;

		}

		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			animation(4);
		move(0, speed * mainTime);

		//dy = speed * mainTime;

		return true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{

		move(-speed * mainTime, 0);
		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			animation(1);
		//dx = -speed * mainTime;

		return true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move(speed * mainTime, 0);

		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			animation(2);
		//dx = speed * mainTime;

		return true;
	}

	return false;
}
void Player::attackHero(sf::Event event, bool ok)
{
	if (event.type == sf::Event::EventType::KeyReleased && (event.key.code == sf::Keyboard::Key::Left || event.key.code == sf::Keyboard::Key::Right || event.key.code == sf::Keyboard::Key::Up || event.key.code == sf::Keyboard::Key::Down))
	{
		resetAnimationAttack();
	}

	//if(dx < 0)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (animation(8))//8 - attack left
		{
			Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, true, *this, 1);
			resetAnimationAttack();
		}
		return;
	}
	//if (dx > 0)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//2
	{
		if (animation(9))//9 - attack right
		{
			Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, true, *this, 2);
			resetAnimationAttack();
		}
		return;
	}
	//if (dy > 0)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//3
	{
		if (animation(10))//10 - attack up
		{
			Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, true, *this, 3);
			resetAnimationAttack();
		}
		return;
	}
	//if (dy <= 0)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//4
	{
		if (animation(7))//7 - attack down
		{
			Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, true, *this, 4);
			resetAnimationAttack();
		}
		return;
	}

	if (event.type == sf::Event::EventType::KeyReleased && !ok)
	{
		animation(5);
		resetAnimationAttack();
		return;
	}
}

int Player::update(sf::Event event)
{
	int temp = Hero::update(event);
	if (temp == -1)
	{
		this->~Player();
		return temp;
	}
	if(temp != -2)
		attackHero(event, moveHero(event));
	return temp;
}

// 1 - left, 2 - right, 3 - up, 4 - down
bool Player::animation(int direction)
{
	return Hero::animation(direction);
}
