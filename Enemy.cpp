#include "Enemy.h"
#include <iostream>
#include <cmath>
#include "Header.h"
extern float mainTime;
//extern const int distanceAttackingObject;

Enemy::Enemy(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, const Stats& stats, Player* player) : Hero(ImageFile, ImageFileAttack, maxFrameX, maxFrameY, x, y, stats)
{
	this->player = player;
	setMoveStyle("range Demon");
	setAttackStyle("range attack");
}

bool Enemy::artificialIntelligence(std::string action)
{
	if (player == nullptr)
	{
		std::cout << "»грок не найден" << std::endl;
		return false;
	}

	double differenceX = (player->getPosition().x - getPosition().x);
	double differenceY = (player->getPosition().y - getPosition().y);
	double difference = sqrt(pow(differenceX, 2) + pow(differenceY, 2));

	double correlationX = differenceX / difference;
	double correlationY = differenceY / difference;

	if (action == "attack")//ƒорогосто€ща€ операци€ 
	{
		if (styleAttack == "close attack")//возможно бессмысленно
		{

		}
		if (styleAttack == "range attack")//возможно бессмысленно
		{
			if (abs(correlationX) >= abs(correlationY))// 7 - attack down 8 - attack left 9 - atck right 10 - attack up
			{
				if (differenceX > 0)
				{
					if (animation(9))//9 - attack right
					{
						if (differenceY >= 0)
						{
							Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, false, *this, 0, 0, atan(abs(differenceY / differenceX)) * 180 / PI);// abs(atan(differenceY / differenceX)) * 180 / PI)
						}
						else
						{
							Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, false, *this, 0, 1, atan(abs(differenceY / differenceX)) * 180 / PI);// abs(atan(differenceY / differenceX)) * 180 / PI)
						}
						resetAnimationAttack();
					}
				}
				else
				{
					if (animation(8))//8 - attack left
					{
						if (differenceY <= 0)
						{
							Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, false, *this, 1, 1, atan(abs(differenceY / differenceX)) * 180 / PI);
						}
						else
						{
							
							Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, false, *this, 1, 0, atan(abs(differenceY / differenceX)) * 180 / PI);
						}
						resetAnimationAttack();
					}
				}
			}
			else
			{
				if (differenceY > 0)
				{
					if (animation(7))//7 - attack down
					{
						if (differenceX >= 0)
						{
							Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, false, *this, 0, 0, abs(atan(abs(differenceY / differenceX)) * 180 / PI));
						}
						else
						{

							Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, false, *this, 1, 0, abs(atan(abs(differenceY / differenceX)) * 180 / PI));
						}
						resetAnimationAttack();
					}
				}
				else
				{
					if (animation(10))//10 - attack up
					{
						if (differenceX >= 0)
						{
							Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, false, *this, 0, 1, abs(atan(abs(differenceY / differenceX)) * 180 / PI));
						}
						else
						{
		
							Shell::makeShell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, 1, false, *this, 1, 1, abs(atan(abs(differenceY / differenceX)) * 180 / PI));
						}
						resetAnimationAttack();
					}
				}
			}


		}
	}
	if (action == "move")//ƒорогосто€ща€ операци€ 
	{
		//std::cout << "move move move" << player->getPosition().x << "  " << this->getPosition().x << std::endl;

		if (difference < 0.5)// ќн должен сто€ть, по хорошему нужно расчитать погрешность O)))
		{
			animation(5);
			return false;// помен€ть
		}

		if (styleMove == "slave")//максимальное сближение
		{
			//std::cout << correlationX << "  " << correlationY << std::endl;
			if (abs(correlationX) >= abs(correlationY))// 1 - left, 2 - right, 3 - up, 4 - down
			{
				if (differenceX > 0)
					animation(2);
				else
					animation(1);
			}
			else
			{
				if (differenceY > 0)
					animation(4);
				else
					animation(3);
			}

			move(speed * mainTime * correlationX, speed * mainTime * correlationY);
		}

		if (styleMove == "range Demon")//—ближение до какой-то точки
		{
			//std::cout << correlationX << "  " << correlationY << std::endl;
			double distance = stats.attackRange - stats.attackTime * player->getSpeed();
			//std::cout << distance << std::endl;
			//std::cout << player->getSpeed() << std::endl;
			if ((difference < distance - (distance / stats.attackSpeed))/* && (attackRange >= distance)*/)
				return false;
			if (abs(correlationX) >= abs(correlationY))// 1 - left, 2 - right, 3 - up, 4 - down
			{
				if (differenceX > 0)
					animation(2);
				else
					animation(1);
			}
			else
			{
				if (differenceY > 0)
					animation(4);
				else
					animation(3);
			}

			move(speed * mainTime * correlationX, speed * mainTime * correlationY);
		}

		return false;
	}
}

int Enemy::update(sf::Event event)
{
	int temp = Hero::update(event);
	if (temp == -1)
	{
		//this->~Enemy();
		return temp;
	}
	if (temp != -2)
	{
		artificialIntelligence("move"); //attack
		artificialIntelligence("attack");
	}
	return temp;

	/*
	int temp = Hero::update(event);
	if (temp == -1)
	{
		this->~Player();
		return temp;
	}
	if(temp != -2)
		attackHero(event, moveHero(event));
	return temp;
	*/
}
