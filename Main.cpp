//#include <SFML/Graphics.hpp>
#include "Header.h"
#include "Player.h"
#include "Map.h"
#include "Menu.h"
#include <iostream>

//void start(sf::RenderWindow& window, Hero& hero);
int verticalHeight = 1920;
int horizontalHeight = 1080;
float mainTime;
double speedAnimation = 9 * pow(10, -6);//Реализовать зависимость скоросити анимации от скорости
double speedPlayer = 0.00033;
double speedPlayerAttack = 0.00033;
sf::View* camera = new sf::View;
sf::String level[] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0     4                                0",
	"0             51                       0",
	"0             23                       0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                      7               0",
	"0                                      0",
	"0                                      0",
	"0                            8         0",
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


int main()
{
	//setlocale(LC_ALL, "Russian");
	sf::RenderWindow window(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork");// , sf::Style::Fullscreen);

	//mainMenu m(menu1, menu2, menu3, about, spriteVec);
	//m.show(window, mainMenuMusic, mainMenuMusic);

	Music music;//создаем объект музыки
	srand(time(0));
	int i = rand() % 2;
	music.openFromFile("resource\\Audio\\" + std::to_string(i) + ".ogg");//загружаем файл
	
	Menu menu(window, music);
	//men.mainMenu(window, music);
	//menu(window, music);//вызов меню
	
	window.setVerticalSyncEnabled(true); // запустите это один раз, после создания окна
	
	camera->setSize(verticalHeight, horizontalHeight);
	
	//sf::View view = const_cast<sf::View&> (window.getView());
	Player player(*camera, "resource\\Enemy\\Dungeon\\Character\\shadowhero.png", "resource\\Enemy\\Dungeon\\Projectile\\devilAttack.png", 8, 11, 1, 1, 500, 500, speedPlayer, speedPlayerAttack);
	//player.setMaxFrames(4, 4);
	Map map("resource\\Map_Tileds\\Dungeon\\Hell.png", 25, 40, 9);//C:\Users\Andrey\Desktop\RPGGame\resource\Map_Tileds\Dungeon
	map.setMap(level, 25, 40);
	map.setPosBG(verticalHeight, horizontalHeight);
	
	//start(window,hero);
	sf::Clock clock;

	music.play();//воспроизводим музыку
	bool ifmus = 0;
	
	while (window.isOpen())
	{
		sf::Event event;


		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			menu.pauseMenu(window, music);
		}

		/*if (ifmus == 1)
		{
			ifmus = 0;
			music.play();
		}*/
		//if (music.Stopped==1) ifmus = 1;
		//if (ifmus == 1)
		//{
		//	int i = rand() % 2;
		//	music.openFromFile("resource\\Audio\\" + std::to_string(i) + ".wav");//загружаем файл
		//	music.play();
		//	ifmus = 0;
		//}


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
		//camera->getCenter().x-sizeMenuX/2;
		//camera->getCenter().y - sizeMenuY / 2;
		
		//player.MoveHero();
		player.update(event);
		window.clear();
		map.updateMap(&window);
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