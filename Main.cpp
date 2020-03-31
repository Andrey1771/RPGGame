//#include <SFML/Graphics.hpp>
#include "Header.h"
#include "Player.h"
#include "Map.h"
#include "Shell.h"
#include "Enemy.h"
#include <iostream>
//void start(sf::RenderWindow& window, Hero& hero);
int verticalHeight = 1200;
int horizontalHeight = 800;
float mainTime;
double speedAnimation = 9 * pow(10, -6);//Реализовать зависимость скоросити анимации от скорости
double speedPlayer = 0.00033;//
double speedPlayerAttack = 1.5;
double attackPlayerRange = 400;
double attackPlayerSpeed = 3;
double repulsiveForce = 1;

sf::String level[] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0   3                                  0",
	"0                                      0",
	"0                   51                 0",
	"0                   23                 0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                      6               0",
	"0                                      0",
	"0                                      0",
	"0                            5         0",
	"0                                      0",
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

std::vector<Shell*> shells;
std::vector<Enemy*> enemies;

Map map("resource\\Map_Tileds\\Dungeon\\Hell.png", 25, 40, 9);//C:\Users\Andrey\Desktop\RPGGame\resource\Map_Tileds\Dungeon

void updateShells(const sf::Event& event, sf::RenderWindow& window);
void updateEnemies(const sf::Event& event, sf::RenderWindow& window);
void updateIntersects(Player& player);
void funRandomizer(int countEnemies, Player& player);
int updateIntersectsWalls(Player&);
int updateIntersectsHeroes(Player& player);

int main()
{
	sf::RenderWindow window(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork");
	window.setVerticalSyncEnabled(true); // запустите это один раз, после создания окна
	sf::View* camera = new sf::View;
	//camera->setSize(verticalHeight, horizontalHeight);

	//sf::View view = const_cast<sf::View&> (window.getView());
	Player player(*camera, "resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, 500, 500, speedPlayer, speedPlayerAttack, attackPlayerRange, attackPlayerSpeed);
	//enemies.push_back(new Enemy("resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, 500, 500, speedPlayer/2, speedPlayerAttack, attackPlayerRange, attackPlayerSpeed, &player));
	//player.setMaxFrames(4, 4);
	funRandomizer(25, player);

	map.setMap(level, 25, 40);
	map.setPosBG(verticalHeight, horizontalHeight);

	//start(window,hero);
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;

		mainTime = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		//time /= 800;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.setView(*camera);
		//player.MoveHero();
		player.update(event);

		window.clear();
		map.updateMap(&window);
		window.draw(map.getSprite());
		window.draw(player.getSprite());

		updateIntersects(player);
		updateShells(event, window);
		updateEnemies(event, window);
		updateIntersectsWalls(player);
		updateIntersectsHeroes(player);

		window.display();
	}

	return 0;
}

void updateShells(const sf::Event& event, sf::RenderWindow& window)
{
	for (int i = 0; i < shells.size(); ++i)
	{
		if (shells.at(i)->update(event) == -1)
		{
			delete shells[i];
			shells.erase(shells.begin() + i);
			--i;
			continue;
		}
		window.draw(shells.at(i)->getSprite());
	}
}

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
	sf::IntRect rect(player.getSprite().getPosition().x, player.getSprite().getPosition().y, player.getSprite().getLocalBounds().width, player.getSprite().getLocalBounds().height);//пока отключил
	sf::IntRect rect2;
	sf::IntRect rect3;
	for (int i = 0; i < enemies.size(); ++i) // O(n^2) Можно оптимизировать в будущем
	{
		rect2.left = enemies[i]->getSprite().getPosition().x;
		rect2.top = enemies[i]->getSprite().getPosition().y;
		rect2.width = enemies[i]->getSprite().getLocalBounds().width;
		rect2.height = enemies[i]->getSprite().getLocalBounds().height;
		for (int j = 0; j < shells.size(); ++j)
		{
			rect3.left = shells[j]->getSprite().getPosition().x;
			rect3.top = shells[j]->getSprite().getPosition().y;
			rect3.width = shells[j]->getSprite().getLocalBounds().width;
			rect3.height = shells[j]->getSprite().getLocalBounds().height;
			if (rect3.intersects(rect2) && shells[j]->enemyKill)// Есть куча способов и идей по оптимизации всего этого и того, что выше
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				break;
			}
		}

	}
	//std::cout << "intersects: " << rect.intersects(rect2) << std::endl;
}

int updateIntersectsWalls(Player& player)
{
	/*std::vector<Object*> vect;
	vect.push_back(&player);
	Object::IntersectsWalls(vect);
	vect.clear();

	for (Object *var : shells)
		vect.push_back(var);
	Object::IntersectsWalls(vect);
	vect.clear();

	for (Object* var : enemies)
		vect.push_back(var);
	Object::IntersectsWalls(vect);
	vect.clear();*/

	sf::IntRect rect(player.getSprite().getPosition().x, player.getSprite().getPosition().y, player.getSprite().getLocalBounds().width, player.getSprite().getLocalBounds().height);
	sf::IntRect rect2;
	sf::IntRect rect3;

	for (sf::Sprite var : map.magicTieldsVector)
	{
		rect3.left = var.getPosition().x;
		rect3.top = var.getPosition().y;
		rect3.width = var.getLocalBounds().width;
		rect3.height = var.getLocalBounds().height;
		if (rect3.intersects(rect))
		{
			player.move(-(player.dx * repulsiveForce), -(player.dy * repulsiveForce));
			break;
		}
	}

	for (int i = 0; i < enemies.size(); ++i) // O(n^2) Можно оптимизировать в будущем
	{
		rect2.left = enemies[i]->getSprite().getPosition().x;
		rect2.top = enemies[i]->getSprite().getPosition().y;
		rect2.width = enemies[i]->getSprite().getLocalBounds().width;
		rect2.height = enemies[i]->getSprite().getLocalBounds().height;

		for (sf::Sprite var : map.magicTieldsVector)
		{
			rect3.left = var.getPosition().x;
			rect3.top = var.getPosition().y;
			rect3.width = var.getLocalBounds().width;
			rect3.height = var.getLocalBounds().height;
			if (rect3.intersects(rect2))
			{
				enemies[i]->move(-(enemies[i]->dx * repulsiveForce), -(enemies[i]->dy * repulsiveForce));
				break;
			}
		}
	}

	for (int i = 0; i < shells.size(); ++i) // O(n^2) Можно оптимизировать в будущем
	{
		rect2.left = shells[i]->getSprite().getPosition().x;
		rect2.top = shells[i]->getSprite().getPosition().y;
		rect2.width = shells[i]->getSprite().getLocalBounds().width;
		rect2.height = shells[i]->getSprite().getLocalBounds().height;

		for (sf::Sprite var : map.magicTieldsVector)
		{
			rect3.left = var.getPosition().x;
			rect3.top = var.getPosition().y;
			rect3.width = var.getLocalBounds().width;
			rect3.height = var.getLocalBounds().height;
			if (rect3.intersects(rect2))
			{
				delete shells[i];
				shells.erase(shells.begin() + i);
				--i;
				break;
			}
		}
	}

	return 0;
	//std::cout << "intersects: " << rect.intersects(rect2) << std::endl;
}

int updateIntersectsHeroes(Player& player)
{
	sf::IntRect rect(player.getSprite().getPosition().x, player.getSprite().getPosition().y, player.getSprite().getLocalBounds().width, player.getSprite().getLocalBounds().height);
	sf::IntRect rect2;
	sf::IntRect rect3;

	for (int i = 0; i < enemies.size(); ++i) // O(n) Можно оптимизировать в будущем
	{
		rect2.left = enemies[i]->getSprite().getPosition().x;
		rect2.top = enemies[i]->getSprite().getPosition().y;
		rect2.width = enemies[i]->getSprite().getLocalBounds().width;
		rect2.height = enemies[i]->getSprite().getLocalBounds().height;

		if (rect.intersects(rect2))
		{
			enemies[i]->move(-enemies[i]->dx, -enemies[i]->dy);
			player.move(-(player.dx * repulsiveForce), -(player.dy * repulsiveForce));
			break;// не уверен в этом немного
		}
	}

	for (int i = 0; i < enemies.size(); ++i) // O(n^2) Можно оптимизировать в будущем
	{
		rect2.left = enemies[i]->getSprite().getPosition().x;
		rect2.top = enemies[i]->getSprite().getPosition().y;
		rect2.width = enemies[i]->getSprite().getLocalBounds().width;
		rect2.height = enemies[i]->getSprite().getLocalBounds().height;

		for (int j = 0; j < enemies.size(); ++j)
		{
			if (j == i)
				continue;
			rect3.left = enemies[j]->getSprite().getPosition().x;
			rect3.top = enemies[j]->getSprite().getPosition().y;
			rect3.width = enemies[j]->getSprite().getLocalBounds().width;
			rect3.height = enemies[j]->getSprite().getLocalBounds().height;

			if (rect3.intersects(rect2))
			{
				enemies[i]->move(-(enemies[i]->dx * repulsiveForce), -(enemies[i]->dy * repulsiveForce));
				enemies[j]->move(-(enemies[j]->dx * repulsiveForce), -(enemies[j]->dy * repulsiveForce));
				break;// не уверен в этом немного
			}
		}
	}
	return 0;
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
		enemies.push_back(new Enemy("resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, positionX, positionY, speedPlayer / 2, speedPlayerAttack, attackPlayerRange, attackPlayerSpeed * 2, &player));

	}
}



/*void start(sf::RenderWindow &window, Hero &hero)
{
	//hero.setPos(100, 100);
}*/