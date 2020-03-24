#pragma once
#include "Hero.h"
#include "Player.h"
#include "Shell.h"

class Enemy :
	public Hero
{
public:
	Enemy(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, double speed = 0, double attackTime = 0, double attackRange = 0, double attackSpeed = 0, Player* player = nullptr);

	Player* player{ nullptr };
	std::string styleMove{ "" };
	std::string styleAttack{ "" };
	static int tickets;// разрешение на спец прием для врага, позволяет регулировать сложность

	virtual bool artificialIntelligence(std::string styleAction);
	void setMoveStyle(std::string styleMove) { this->styleMove = styleMove; };
	void setAttackStyle(std::string styleAttack) { this->styleAttack = styleAttack; };
	void setTickets(const int tickets) { this->tickets = tickets; };
	void setPlayer(Player* player) { this->player = player; };

	virtual int update(sf::Event) override;
};

