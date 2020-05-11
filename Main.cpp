//#include <SFML/Graphics.hpp>
#include "Header.h"
#include "Player.h"
#include "Map.h"
#include "Shell.h"
#include "Enemy.h"
#include "Camera.h"
#include "Item.h"
#include "HealthBottle.h"
#include "HealthBar.h"
#include "DodgeBar.h"
//#include <iostream>
//void start(sf::RenderWindow& window, Hero& hero);
int verticalHeight = 1200;
int horizontalHeight = 800;
float mainTime;
double speedAnimation = 9 * pow(10, -6);//����������� ����������� �������� �������� �� ��������
double speedPlayer = 0.00033;//
double speedPlayerAttack = 1.5;
double attackPlayerRange = 400;
double attackPlayerSpeed = 3;
double repulsiveForce = 1;// unused
int tieldsWidth = 64;
int tieldsHeight = 64;
int levelHeight = 25;
const int distanceAttackingObject = 10;
float maxTimeDodgePlayer = 1000; // 1000 ���������� = 1 �������
float teleportDistance = 200;
int dodgeDelay = 5000;

sf::String level[] = {// ��������� �� ����
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0   3        0                         0",
	"0                                      0",
	"0                   51                 0",
	"0        0          23                 0",
	"0                                      0",
	"0            0                         0",
	"0                   0                  0",
	"0       0       0                      0",
	"0                                      0",
	"0                      6               0",
	"0       0                              0",
	"0                                      0",
	"0            000             5         0",
	"0             0                        0",
	"0                                      0",
	"0                                      0",
	"0                       00000          0",
	"0                       00000          0",
	"0                       00000          0",
	"0                       00000          0",
	"0                       00000          0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

std::vector<Shell*> Shell::shells;
std::vector<Enemy*> Enemy::enemies;
std::vector<Object*> Object::objectsAll;
std::vector<Player*> Player::players;
std::vector<Item*> Item::items;
Map map("resource\\Map_Tileds\\Dungeon\\Hell.png", 25, 40, 9);//C:\Users\Andrey\Desktop\RPGGame\resource\Map_Tileds\Dungeon

std::vector<sf::Sprite*> debugIntersects;
void updateEnemies(const sf::Event& event, sf::RenderWindow& window);
void updateIntersects();
void funRandomizer(int countEnemies, Player& player);
int updateIntersectsWalls(Player&);

int main()
{
	sf::RenderWindow window(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork");
	
	window.setVerticalSyncEnabled(true); // ��������� ��� ���� ���, ����� �������� ����
	Stats statsPlayer(speedPlayer, speedPlayerAttack, attackPlayerRange, attackPlayerSpeed, 6, 5);
	Player player("resource\\Player\\Player\\Character\\shadowHero.png", "resource\\Player\\Player\\Projectile\\shadowHeroAttack.png", 8, 11, 500, 500, statsPlayer, dodgeDelay);
	Camera camera(&player, new sf::View, tieldsWidth, tieldsHeight, verticalHeight, horizontalHeight);
	camera.setMapXYAndSize(0, 0, level[0].getSize() * tieldsWidth, levelHeight * tieldsHeight);
	funRandomizer(1, player);
	HealthBottle hPBottle(250, 250, 2);
	map.setMap(level, 25, 40);
	map.setPosBG(verticalHeight, horizontalHeight);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;//setCoordinationCamera(0, 0, 40 * 64, 64 * 25);

		mainTime = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
			{
				window.close();
				return 0;
			}
		}

		window.setView(*(camera.getView()));
		for (Player* var : Player::players)
			var->update(event);

		window.clear();
		map.updateMap(&window);

		for (Item* var : Item::items)
		{
			var->update(event);
			window.draw(var->getSprite());
		}
		camera.update();
		for (sf::Sprite var : camera.getHPProgressBar()->getSpritesBar())
			window.draw(var);

		for (sf::Sprite var : camera.getDodgeProgressBar()->getSpritesBar())
			window.draw(var);

		updateIntersects();
		for (Player* var : Player::players)
		{
			window.draw(var->getSprite());
			
		}
		
		updateEnemies(event, window);
		Shell::checkIntersectsObjectsUpdate(event);
		for (Shell* var : Shell::shells)
			window.draw(var->getSprite());

		for (sf::Sprite* var : debugIntersects)
			window.draw(*var);

		window.display();
	}
	return 0;
}

void updateEnemies(const sf::Event& event, sf::RenderWindow& window)
{
	for (int i = 0; i < Enemy::enemies.size(); ++i)
	{
		if (Enemy::enemies.at(i)->update(event) == -1)
		{
			--i;
			continue;
		}
		window.draw(Enemy::enemies.at(i)->getSprite());
	}
}

void updateIntersects()
{
	sf::IntRect rect2;
	sf::IntRect rect3;
	for (int i = 0; i < Enemy::enemies.size(); ++i) // O(n^2) ����� �������������� � �������
	{
		rect2.left = Enemy::enemies[i]->getSprite().getPosition().x;
		rect2.top = Enemy::enemies[i]->getSprite().getPosition().y;
		rect2.width = Enemy::enemies[i]->getSprite().getLocalBounds().width;
		rect2.height = Enemy::enemies[i]->getSprite().getLocalBounds().height;
		for (int j = 0; j < Shell::shells.size(); ++j)
		{
			rect3.left = Shell::shells[j]->getSprite().getPosition().x;
			rect3.top = Shell::shells[j]->getSprite().getPosition().y;
			rect3.width = Shell::shells[j]->getSprite().getLocalBounds().width;
			rect3.height = Shell::shells[j]->getSprite().getLocalBounds().height;
			if (rect3.intersects(rect2) && Shell::shells[j]->enemyKill)// ���� ���� �������� � ���� �� ����������� ����� ����� � ����, ��� ����
			{
				Enemy::enemies[i]->changeHealthPoints(-Shell::shells[j]->getDamage());
				delete Shell::shells[j];
				Shell::shells.erase(Shell::shells.begin() + j);
				--j;
				break;
			}
		}
	}

	for (int i = 0; i < Player::players.size(); ++i) // O(n^2) ����� �������������� � �������
	{
		rect2.left = Player::players[i]->getSprite().getPosition().x;
		rect2.top = Player::players[i]->getSprite().getPosition().y;
		rect2.width = Player::players[i]->getSprite().getLocalBounds().width;
		rect2.height = Player::players[i]->getSprite().getLocalBounds().height;
		for (int j = 0; j < Shell::shells.size(); ++j)
		{
			rect3.left = Shell::shells[j]->getSprite().getPosition().x;
			rect3.top = Shell::shells[j]->getSprite().getPosition().y;
			rect3.width = Shell::shells[j]->getSprite().getLocalBounds().width;
			rect3.height = Shell::shells[j]->getSprite().getLocalBounds().height;
			if (rect3.intersects(rect2) && !Shell::shells[j]->enemyKill)// ���� ���� �������� � ���� �� ����������� ����� ����� � ����, ��� ����
			{
				Player::players[i]->changeHealthPoints(-Shell::shells[j]->getDamage());
				delete Shell::shells[j];
				Shell::shells.erase(Shell::shells.begin() + j);
				--j;
				break;
			}
		}
	}
}

void funRandomizer(int countEnemies, Player& player)
{
	int positionX;
	int positionY;
	srand(time_t(0));
	for (int i = 0; i < countEnemies; ++i)
	{
		positionX = rand() % 1000 + 200;
		positionY = rand() % 1000 + 200;
		Enemy::enemies.push_back(new Enemy("resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, positionX, positionY, Stats(speedPlayer / 2, speedPlayerAttack, attackPlayerRange, attackPlayerSpeed * 2, 1, 1), &player));
	}
}

/*void start(sf::RenderWindow &window, Hero &hero)
{
	//hero.setPos(100, 100);
}*/