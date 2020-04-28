//#include <SFML/Graphics.hpp>
#include "Header.h"
#include "Player.h"
#include "Map.h"
#include "Shell.h"
#include "Enemy.h"
#include "Camera.h"
#include "Menu.h"

#include <iostream>
//void start(sf::RenderWindow& window, Hero& hero);
int verticalHeight = 1200;
int horizontalHeight = 800;
float mainTime;
double speedAnimation = 9 * pow(10, -6);//Реализовать зависимость скорости анимации от скорости
double speedPlayer = 0.00033;//
double speedPlayerAttack = 1.5;
double attackPlayerRange = 400;
double attackPlayerSpeed = 3;
double repulsiveForce = 1;
int tieldsWidth = 64;
int tieldsHeight = 64;
int levelHeight = 25;
const int distanceAttackingObject = 10;

sf::String level[] = {// Перенести на файл
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
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

std::vector<Shell*> Shell::shells;
std::vector<Enemy*> enemies;
std::vector<Object*> Object::objectsAll;
std::vector<Player*> Player::players;

Map map("resource\\Map_Tileds\\Dungeon\\Hell.png", 25, 40, 9);//C:\Users\Andrey\Desktop\RPGGame\resource\Map_Tileds\Dungeon

//void updateShells(const sf::Event& event, sf::RenderWindow& window);
void updateEnemies(const sf::Event& event, sf::RenderWindow& window);
void updateIntersects(Player& player);
void funRandomizer(int countEnemies, Player& player);
int updateIntersectsWalls(Player&);

sf::Clock clock3;

int main()
{
	sf::RenderWindow window(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork");
	window.setVerticalSyncEnabled(true); // запустите это один раз, после создания окна
	Stats statsPlayer(speedPlayer, speedPlayerAttack, attackPlayerRange, attackPlayerSpeed, 6, 5);
	Player player("resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, 500, 500, statsPlayer);
	Camera camera(&player, new sf::View, tieldsWidth, tieldsHeight, verticalHeight, horizontalHeight);//dynamic_cast<Hero*>(&player)
	camera.setMapXYAndSize(0, 0, level[0].getSize() * tieldsWidth, levelHeight * tieldsHeight);
	funRandomizer(1, player);

	map.setMap(level, 25, 40);
	map.setPosBG(verticalHeight, horizontalHeight);

	//start(window,hero);
	

	Music music;
	music.openFromFile("resource\\Audio\\1.ogg");//загружаем файл

	Menu menu(window, music, &camera);

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			menu.pauseMenu(window, music);
		}
		if (!menu.isMenuOn())
		{
			//std::cout << "Tyt" << std::endl;
			sf::Event event;//setCoordinationCamera(0, 0, 40 * 64, 64 * 25);

			mainTime = clock3.getElapsedTime().asMicroseconds();
			clock3.restart();
			//time /= 800;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			window.setView(*(camera.getView()));
			//player.MoveHero();
			if (&player != nullptr)
				player.update(event);
			camera.update();
			window.clear();

			map.updateMap(&window);
			window.draw(map.getSprite());

			for (sf::Sprite var : camera.getProgressBar()->getSpritesBar())
				window.draw(var);

			if (&player != nullptr)
				window.draw(player.getSprite());

			updateIntersects(player);
			//updateShells(event, window);

			updateEnemies(event, window);
			Shell::checkIntersectsObjectsUpdate(event);
			for (Shell* var : Shell::shells)
				window.draw(var->getSprite());
			//updateIntersectsHeroes(player);
		}
		
		window.display();
	}

	return 0;
}

//void updateShells(const sf::Event& event, sf::RenderWindow& window)
//{
//	for (int i = 0; i < shells.size(); ++i)
//	{
//		if (shells.at(i)->update(event) == -1)
//		{
//			delete shells[i];
//			shells.erase(shells.begin() + i);
//			
//			--i;
//			continue;
//		}
//		window.draw(shells.at(i)->getSprite());
//	}
//}

void updateEnemies(const sf::Event& event, sf::RenderWindow& window)
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (enemies.at(i)->update(event) == -1)
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			continue;
		}

		window.draw(enemies.at(i)->getSprite());
	}
}

void updateIntersects(Player& player)
{
	if (&player == nullptr)
		return;
	sf::IntRect rect(player.getSprite().getPosition().x, player.getSprite().getPosition().y, player.getSprite().getLocalBounds().width, player.getSprite().getLocalBounds().height);//пока отключил
	sf::IntRect rect2;
	sf::IntRect rect3;
	for (int i = 0; i < enemies.size(); ++i) // O(n^2) Можно оптимизировать в будущем
	{
		rect2.left = enemies[i]->getSprite().getPosition().x;
		rect2.top = enemies[i]->getSprite().getPosition().y;
		rect2.width = enemies[i]->getSprite().getLocalBounds().width;
		rect2.height = enemies[i]->getSprite().getLocalBounds().height;
		for (int j = 0; j < Shell::shells.size(); ++j)
		{
			rect3.left = Shell::shells[j]->getSprite().getPosition().x;
			rect3.top = Shell::shells[j]->getSprite().getPosition().y;
			rect3.width = Shell::shells[j]->getSprite().getLocalBounds().width;
			rect3.height = Shell::shells[j]->getSprite().getLocalBounds().height;
			if (rect3.intersects(rect2) && Shell::shells[j]->enemyKill)// Есть куча способов и идей по оптимизации всего этого и того, что выше
			{
				//delete enemies[i];
				//enemies.erase(enemies.begin() + i);
				enemies[i]->setHealthPoints(enemies[i]->getHealthPoints() - Shell::shells[j]->getDamage());
				break;
			}
		}

	}
	for (int j = 0; j < Shell::shells.size(); ++j)
	{
		rect3.left = Shell::shells[j]->getSprite().getPosition().x;
		rect3.top = Shell::shells[j]->getSprite().getPosition().y;
		rect3.width = Shell::shells[j]->getSprite().getLocalBounds().width;
		rect3.height = Shell::shells[j]->getSprite().getLocalBounds().height;
		if (rect3.intersects(rect) && !Shell::shells[j]->enemyKill)// Есть куча способов и идей по оптимизации всего этого и того, что выше
		{
			//delete enemies[i];
			//enemies.erase(enemies.begin() + i);
			player.setHealthPoints(player.getHealthPoints() - Shell::shells[j]->getDamage());
			delete Shell::shells[j];
			Shell::shells.erase(Shell::shells.begin() + j);

			--j;
			//break;
		}
	}
	//std::cout << "intersects: " << rect.intersects(rect2) << std::endl;
}

void funRandomizer(int countEnemies, Player& player)
{
	int positionX;
	int positionY;
	//srand();
	srand(time_t(0));
	for (int i = 0; i < countEnemies; ++i)
	{

		positionX = rand() % 1000 + 200;
		positionY = rand() % 1000 + 200;
		enemies.push_back(new Enemy("resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, positionX, positionY, Stats(speedPlayer / 2, speedPlayerAttack, attackPlayerRange, attackPlayerSpeed * 2, 1, 1), &player));

	}
}


/*void start(sf::RenderWindow &window, Hero &hero)
{
	//hero.setPos(100, 100);
}*/