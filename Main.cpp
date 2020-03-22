//#include <SFML/Graphics.hpp>
#include "Header.h"
#include "Player.h"
#include "Map.h"
#include "Shell.h"
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

int main()
{
	sf::RenderWindow window(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork");
	window.setVerticalSyncEnabled(true); // запустите это один раз, после создания окна
	sf::View* camera = new sf::View;
	//camera->setSize(verticalHeight, horizontalHeight);

	//sf::View view = const_cast<sf::View&> (window.getView());
	Player player(*camera, "resource\\Enemy\\Dungeon\\Character\\devil.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 4, 11, 1, 1, 500, 500, speedPlayer, speedPlayerAttack, attackPlayerRange, attackPlayerSpeed);
	//player.setMaxFrames(4, 4);
	Map map("resource\\Map_Tileds\\Dungeon\\Hell.png", 25, 40, 9);//C:\Users\Andrey\Desktop\RPGGame\resource\Map_Tileds\Dungeon
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

		for (int i = 0; i < shells.size(); ++i)
		{
			if (shells.at(i)->update(event) == -1)
			{
				delete shells[i];
				shells.erase(shells.begin() + i);
				continue;
			}
			window.draw(shells.at(i)->getSprite());
		}
		window.display();
	}

	return 0;
}



/*void start(sf::RenderWindow &window, Hero &hero)
{
	//hero.setPos(100, 100);
}*/