#include "Player.h"
#include "Shell.h"
#include "ProgressBar.h"
#include <iostream>
#include "Header.h"
extern float mainTime;
extern double speedAnimation;
extern float teleportDistance;

Player::Player(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, const UtilitiesGame::Stats& stats, int dodgeDelay) : Hero(ImageFile, ImageFileAttack, maxFrameX, maxFrameY, x, y, stats)
{
	players.push_back(this);
	this->dodgeDelay = dodgeDelay;
	resetAnimationAttack();
}

Player::~Player()
{
	for (int j = 0; j < Player::players.size(); ++j)
	{
		if (this == Player::players[j])
		{
			Player::players.erase(Player::players.begin() + j);
			break;
		}
	}
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
			Shell::makeShell("resource\\Player\\Player\\Projectile\\shadowHeroAttack.png", 4, 4, 100, 1, true, *this, 1, 0, 0);
			resetAnimationAttack();
		}
		return;
	}
	//if (dx > 0)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//2
	{
		if (animation(9))//9 - attack right
		{
			Shell::makeShell("resource\\Player\\Player\\Projectile\\shadowHeroAttack.png", 4, 4, 100, 1, true, *this, 2, 0, 0);
			resetAnimationAttack();
		}
		return;
	}
	//if (dy > 0)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//3
	{
		if (animation(10))//10 - attack up
		{
			Shell::makeShell("resource\\Player\\Player\\Projectile\\shadowHeroAttack.png", 4, 4, 100, 1, true, *this, 0, 1, 90);
			resetAnimationAttack();
		}
		return;
	}
	//if (dy <= 0)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//4
	{
		if (animation(7))//7 - attack down
		{
			Shell::makeShell("resource\\Player\\Player\\Projectile\\shadowHeroAttack.png", 4, 4, 100, 1, true, *this, 0, 2, 90);
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
	if (temp != -2)
	{
		if(dodge(event) == 0)
			attackHero(event, moveHero(event));
	}
	return temp;
}

// 1 - left, 2 - right, 3 - up, 4 - down
bool Player::animation(int direction)
{
	return Hero::animation(direction);
}

int Player::dodge(sf::Event event)
{
	dodgeDelayTime += mainTime;
	if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Space)
	{
		if (dodgeTime != 0)
		{
			dodgeTime = 0;
			teleportUsed = false;
			dodgeDelayTime = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && dodgeDelayTime / 1000 > dodgeDelay)
	{
		dodgeTime += mainTime;
		if ((dodgeTime / 1000 > maxTimeDodge) || teleportUsed)
		{
			this->setHealthChange(true);
			dodgeDelayTime = 0;
			return 0;
		}

		this->setHealthChange(false);
		animation(6);// ��� ������ ���� 12 ��������
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->teleport(-teleportDistance, 0);
			teleportUsed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->teleport(teleportDistance, 0);
			teleportUsed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->teleport(0, -teleportDistance);
			teleportUsed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->teleport(0, teleportDistance);
			teleportUsed = true;
		}
		return 1;
	}
	this->setHealthChange(true);
	return 0;
}

const float Player::getDodgeDelayTime()
{
	return dodgeDelayTime;
}

void Player::setDodgeDelay(const int dodgeDelay)
{
	this->dodgeDelay = dodgeDelay;
}

const int Player::getDodgeDelay()
{
	return dodgeDelay;
}

