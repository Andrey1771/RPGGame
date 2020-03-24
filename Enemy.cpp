#include "Enemy.h"
#include <iostream>

extern float mainTime;
extern std::vector<Shell*> shells;

Enemy::Enemy(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, double speed, double attackTime, double attackRange, double attackSpeed, Player* player) : Hero(ImageFile, ImageFileAttack, maxFrameX, maxFrameY, x, y, speed, attackTime, attackRange, attackSpeed)
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
			if (abs(correlationX) >= abs(correlationY))// 7 - attack down 8 - attack left 9 - attack right 10 - attack up
			{
				if (differenceX > 0)
				{
					if (animation(9))//9 - attack right
					{
						shells.push_back(new Shell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, false));//Player player(*camera, "resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, 1, 1, 500, 500, speedPlayer, speedPlayerAttack);
						shells.back()->startShot((this->movementTexture.sprite->getPosition().x + this->getSizeXY().sizeX), this->movementTexture.sprite->getPosition().y, 2, attackRange, attackSpeed);
						resetAnimationAttack();
					}
				}
				else
				{
					if (animation(8))//8 - attack left
					{
						shells.push_back(new Shell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, false));//Player player(*camera, "resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, 1, 1, 500, 500, speedPlayer, speedPlayerAttack);
						shells.back()->startShot((this->movementTexture.sprite->getPosition().x - this->getSizeXY().sizeX), this->movementTexture.sprite->getPosition().y, 1, attackRange, attackSpeed);
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
						shells.push_back(new Shell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, false));//Player player(*camera, "resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, 1, 1, 500, 500, speedPlayer, speedPlayerAttack);
						shells.back()->startShot(this->movementTexture.sprite->getPosition().x, (this->movementTexture.sprite->getPosition().y + this->getSizeXY().sizeY), 4, attackRange, attackSpeed);
						resetAnimationAttack();
					}
				}
				else
				{
					if (animation(10))//10 - attack up
					{
						shells.push_back(new Shell("resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 4, 100, false));//Player player(*camera, "resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, 1, 1, 500, 500, speedPlayer, speedPlayerAttack);
						shells.back()->startShot(this->movementTexture.sprite->getPosition().x, (movementTexture.sprite->getPosition().y - getSizeXY().sizeY), 3, attackRange, attackSpeed);
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
			double distance = attackRange - attackTime * player->getSpeed();
			std::cout << distance << std::endl;
			std::cout << player->getSpeed() << std::endl;
			if ((difference < distance - (distance / attackSpeed))/* && (attackRange >= distance)*/)
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
	artificialIntelligence("move"); //attack
	artificialIntelligence("attack");
	return Hero::update(event);
}
