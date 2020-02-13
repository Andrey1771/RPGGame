//#include <SFML/Graphics.hpp>
#include "Header.h"
#include "Player.h"
#include "Map.h"

//void start(sf::RenderWindow& window, Hero& hero);
int verticalHeight = 1200;
int horizontalHeight = 800;
float mainTime;
double speedAnimation = 9 * pow(10, -6);//Реализовать зависимость скоросити анимации от скорости
double speedPlayer = 0.00033;//

int main()
{
	sf::RenderWindow window(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork");
	window.setVerticalSyncEnabled(true); // запустите это один раз, после создания окна

	Player player("resource\\devil.png", 2, 4, 100, 100, speedPlayer);
	//player.setMaxFrames(4, 4);
	Map map("resource\\8k_stars_milky_way.jpg");
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
		player.MoveHero();
		window.clear();
		window.draw(map.getSprite());
		window.draw(player.getSprite());
		window.display();
	}

	return 0;
}



/*void start(sf::RenderWindow &window, Hero &hero)
{
	//hero.setPos(100, 100);
}*/