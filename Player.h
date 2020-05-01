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
	Player(sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, double x, double y, const Stats& stats, int dodgeDelay);
	~Player();
	static std::vector<Player*> players;
	// Унаследовано через Hero
	virtual int update(sf::Event event) override;
	void setDodgeDelay(const int dodgeDelay);
	const int getDodgeDelay();
	sf::Clock& getClockDodgeDelay();
private:
	bool moveHero(sf::Event event);
	void attackHero(sf::Event event, bool ok);
	// Унаследовано через Hero
	virtual bool animation(int direction) override;
	int dodge(sf::Event event);
	float maxTimeDodge{ maxTimeDodgePlayer };
	sf::Clock* clockDodge{ nullptr };
	sf::Clock clockDodgeDelay;
	bool teleportUsed{ false };
	
	
};

