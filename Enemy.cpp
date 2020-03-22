#include "Enemy.h"

Enemy::Enemy(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, double speed, double attackTime, double attackRange, double attackSpeed) : Hero(ImageFile, ImageFileAttack, maxFrameX, maxFrameY, x, y, speed, attackTime, attackRange, attackSpeed)
{
}

void Enemy::artificialIntelligence(std::string styleAction)
{

}

void Enemy::attack(std::string styleAttack)
{
}

void Enemy::move(std::string styleMove)
{
	if (styleMove == "Slave")
	{

	}
}

int Enemy::updateEnemy(sf::Event, Player* player)
{
	return 0;
}

int Enemy::update(sf::Event event)
{
	return Hero::update(event);
}
