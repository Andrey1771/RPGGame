#pragma once
#include "Hero.h"
#include "Player.h"
#include "Shell.h"

class Enemy :
	public Hero
{
public:
	Enemy(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, const UtilitiesGame::Stats& stats, Player* player = nullptr);
	~Enemy();
	Player* player{ nullptr };
	std::string styleMove{ "" };
	std::string styleAttack{ "" };
	static std::vector<Enemy*> enemies;
	static int tickets;// разрешение на спец прием для врага, позволяет регулировать сложность

	virtual bool artificialIntelligence(std::string styleAction);
	void setMoveStyle(std::string styleMove) { this->styleMove = styleMove; };
	void setAttackStyle(std::string styleAttack) { this->styleAttack = styleAttack; };
	void setTickets(const int tickets) { this->tickets = tickets; };
	void setPlayer(Player* player) { this->player = player; };

	virtual int update(sf::Event) override;
};

