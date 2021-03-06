#pragma once
#include "Hero.h"
#include <SFML/Graphics.hpp>

extern float maxTimeDodgePlayer;

class Player :
	public Hero
{
private:
	int keyPressed{ 0 }; int dodgeDelay;
public:
	Player(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, const UtilitiesGame::Stats& stats, int dodgeDelay);
	~Player();
	static std::vector<Player*> players;
	// ������������ ����� Hero
	virtual int update(sf::Event event) override;
	void setDodgeDelay(const int dodgeDelay);
	const int getDodgeDelay();
	const float getDodgeDelayTime();

private:
	bool moveHero(sf::Event event);
	void attackHero(sf::Event event, bool ok);
	// ������������ ����� Hero
	virtual bool animation(int direction) override;
	int dodge(sf::Event event);
	float maxTimeDodge{ maxTimeDodgePlayer };
	float dodgeTime{ 0 };
	float dodgeDelayTime{ 0 };
	bool teleportUsed{ false };
	
	
};

