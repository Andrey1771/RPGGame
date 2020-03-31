#include "Menu.h"
#include "Header.h"

extern int verticalHeight;
extern int horizontalHeight;
extern sf::View* camera;

Menu::Menu(sf::RenderWindow& window, Music& music)
{
	//camera->getCenter().x;
	kX = double(verticalHeight) / double(1920);
	kY = double(horizontalHeight) / double(1080);
	font.loadFromFile("resource\\Fonts\\mainFonts\\18959.ttf");
	whatDisplay = 5;
	isDisp = 1;
	for (size_t i = 0; i < numOfDisplay; i++)  
	{
		displayVector.push_back(std::pair< Text, std::pair<int, int>>(Text(), std::pair<int,int>(0,0)));
		displayVector.back().first.setFont(font);
		displayVector.back().first.setCharacterSize(int(horizontalHeight/27));  //+++++++++++++++++++++++++++
		displayVector.back().first.setString(displayArray[i].first);
		displayVector.back().second.first = displayArray[i].second.first;
		displayVector.back().second.second = displayArray[i].second.second;
		displayVector.back().first.setPosition(360*kX, 600*kY);  //+++++++++++++++++++++++++++
	}
	displayVector.at(5).second.first = verticalHeight;
	displayVector.at(5).second.second = horizontalHeight;
	displayVector.at(5).first.setString(std::to_string(verticalHeight) + "x" + std::to_string(horizontalHeight));

	bestiaryMusic.openFromFile("resource\\Audio\\bestiaryMusic.ogg");
	for (size_t i = 0; i < C; i++)
	{
		textVector.push_back(std::pair<sf::Text, sf::String>(Text(), "Categories"));
		textVector.back().first.setFont(font);
		textVector.back().first.setCharacterSize(int(horizontalHeight / 27));  //+++++++++++++++++++++++++++
		textVector.back().first.setString(nameArray[i].first);
		textVector.back().second = nameArray[i].second;
	}

	bestiaryFont.loadFromFile("resource\\Fonts\\bestiaryFonts\\19108.otf");
	bestiaryFont_1.loadFromFile("resource\\Fonts\\bestiaryFonts\\13859.ttf");
	for (size_t i = 0; i < numOfMonstres; i++)
	{
		bestiaryVector.push_back(std::pair<Text, Text>(Text(), Text()));
		bestiaryVector.back().first.setFont(bestiaryFont_1);
		bestiaryVector.back().first.setCharacterSize(int(horizontalHeight/10.8));  //+++++++++++++++++++++++++++
		bestiaryVector.back().first.setString(bestiaryArray[i].first);
		bestiaryVector.back().first.setPosition(400 * kX, 250 * kY);  //+++++++++++++++++++++++++++
		//bestiaryVector.back().first.setStyle(Text::Bold);
		bestiaryVector.back().second.setFont(bestiaryFont_1);
		bestiaryVector.back().second.setCharacterSize(int(horizontalHeight/21.6));  //+++++++++++++++++++++++++++
		bestiaryVector.back().second.setString(bestiaryArray[i].second);
		bestiaryVector.back().second.setPosition(400 * kX, 400 * kY);  //+++++++++++++++++++++++++++
		//bestiaryVector.back().second.setStyle(Text::Bold);
		bestiaryVector.back().second.setLineSpacing(0.6);
	}
	for (size_t i = 0; i < numOfButton; i++)
	{
		buttonVector.push_back(Text());
		buttonVector.back().setFont(bestiaryFont);
		buttonVector.back().setCharacterSize(int(horizontalHeight / 10.8));  //+++++++++++++++++++++++++++
		buttonVector.back().setString(buttonArray[i]);
		buttonVector.back().setPosition(600 * kX, 600 * kY);  //+++++++++++++++++++++++++++
		buttonVector.back().setStyle(Text::Bold);
	}
	buttonVector.at(0).setPosition(650 * kX, 0 * kY);  // Бестиарий  //+++++++++++++++++++++++++++
	buttonVector.at(0).setCharacterSize(int(horizontalHeight/5.4));  //+++++++++++++++++++++++++++
	buttonVector.at(1).setPosition(300 * kX, 700 * kY);  // Выбор  //+++++++++++++++++++++++++++
	buttonVector.at(2).setPosition(300 * kX, 800 * kY);  // Назад  //+++++++++++++++++++++++++++

	for (size_t i = 0; i < numOfMonstres; i++)  // Вектор текстур существ Бестиария
	{
		bestiaryTextureVec.push_back(Texture());
		bestiaryTextureVec.back().loadFromFile("resource\\Menu\\mainMenu\\Bestiary\\sprite_" + std::to_string(i) + ".png");
	}

	for (size_t i = 0; i < numOfMonstres; i++)  // Вектор спрайтов существ Бестриария
	{
		bestiarySpriteVec.push_back(Sprite());
		bestiarySpriteVec.back().setTexture(bestiaryTextureVec.at(i));
		bestiarySpriteVec.back().setTextureRect(IntRect(0, 0, 256, 256));
		bestiarySpriteVec.back().setPosition(1150 * kX, 400 * kY);  //+++++++++++++++++++++++++++
	}

	textVector.at(0).first.setPosition(40*verticalHeight/1920, 440*horizontalHeight/1080);  // Новая игра 
	textVector.at(1).first.setPosition(40 * kX, 520 * kY);  // Авторы
	textVector.at(2).first.setPosition(40 * kX, 600 * kY);  // Выход из игры

	textVector.at(3).first.setPosition(360 * kX, 590 * kY);  // Продолжить
	textVector.at(4).first.setPosition(360 * kX, 670 * kY);  // Настройки
	textVector.at(5).first.setPosition(360 * kX, 750 * kY);  // Главное меню

	textVector.at(6).first.setPosition(360 * kX, 455 * kY);  // Режим:
	textVector.at(7).first.setPosition(360 * kX, 495 * kY);  // Оконный
	textVector.at(8).first.setPosition(360 * kX, 495 * kY);  // Полноэкранный
	textVector.at(9).first.setPosition(360 * kX, 655 * kY);  // Звук: Вкл
	textVector.at(10).first.setPosition(360 * kX, 655 * kY);  // Звук: Выкл
	textVector.at(11).first.setPosition(360 * kX, 715 * kY);  // Громкость
	textVector.at(12).first.setPosition(360 * kX, 819 * kY);  // Назад
	textVector.at(13).first.setPosition(360 * kX, 550 * kY);  // Разрешение

	aboutTexture.loadFromFile("resource\\Menu\\mainMenu\\Bestiary\\backGround.png");
	about.setTexture(aboutTexture);
	about.setPosition(0, 0);
	about.setScale(kX, kY);
 
	for (size_t i = 0; i < 8; i++)  // Вектор текстур бэкграунда Главного Меню
	{
		textureVec.push_back(Texture());
		textureVec.back().loadFromFile("resource\\Menu\\mainMenu\\backGround_" + std::to_string(i) + ".png");
	}

	for (size_t i = 0; i < 8; i++)  // Вектор спрайтов бэкграунда Главного Меню
	{
		spriteVec.push_back(Sprite());
		spriteVec.back().setTexture(textureVec.at(i));
		spriteVec.back().setTextureRect(IntRect(0, 0, 1920, 1080));
		spriteVec.back().setPosition(0, 0);
	}
	
	for (size_t i = 0; i < 4; i++)  // Вектор текстур бэкграунда Меню Паузы
	{
		texPauseVec.push_back(Texture());
		texPauseVec.back().loadFromFile("resource\\Menu\\pauseMenu\\backGround_" + std::to_string(i) + ".png");
	}

	for (int i = 0; i < 4; i++)  // Вектор спрайтов бэкграунда Меню Паузы
	{
		sprPauseVec.push_back(Sprite());
		sprPauseVec.back().setTexture(texPauseVec.at(i));
		sprPauseVec.back().setTextureRect(IntRect(0, 0, 1280, 720));
		sprPauseVec.back().setPosition(int(verticalHeight/2)*(1-double(1280)/double(1920)), int(horizontalHeight / 2) * (1 - double(720) / double(1080)));
		sprPauseVec.back().setScale(kX, kY);
	}

	mainMenuMusic.openFromFile("resource\\Audio\\mainMenuMusic.ogg");

	arrow.loadFromFile("resource\\Menu\\settingsMenu\\volumeArrows.png");
	volArrows.setTexture(arrow);
	volArrows.setTextureRect(IntRect(0, 144, 252, 36));
	volArrows.setPosition(360 * kX, 773 * kY);  //+++++++++++++++++++++++++++
	volArrows.setScale(kX, kY);
	
	Menu::mainMenu(window, music);
}
Menu::~Menu()
{
}
void Menu::mainMenu(RenderWindow& window, Music &musicToStop)
{
	isMenu = true;
	key = 1; // Номер текущей кнопки
	CurrentFrame = 0; // Таймер для анимации бэкграунда 
	menuTimer = 0; // Таймер для нажатия клавиш

	musicToStop.stop();
	mainMenuMusic.play();
	mainMenuMusic.setLoop(true);
	
	while (isMenu)
	{
		for (int i = 0; i < C; i++)
		{
			if (textVector.at(i).second == "mainMenu")
			{
				textVector.at(i).first.setFillColor(Color::White);
			}
		}
		
		window.clear();

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		menuTimer += 0.005 * time;

		switch (key) 
		{
			case 1:
			{
				textVector.at(0).first.setFillColor(Color(176, 227, 23, 255));
				if (menuTimer > keyDelay)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						//settingsMenu(window, musicToStop);
						isMenu = false;
						//musicToStop.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						key = 2;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						key = 3;
						menuTimer = 0;
					}
				}
				break;
			}
			case 2:
			{
				textVector.at(1).first.setFillColor(Color(176, 227, 23, 255));
				if (menuTimer > keyDelay)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						isMenu = false;
						bestiary(window, mainMenuMusic);
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						key = 3;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						key = 1;
						menuTimer = 0;
					}
				}
				break;
			}
			case 3:
			{
				textVector.at(2).first.setFillColor(Color(176, 227, 23, 255));
				if (menuTimer > keyDelay)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						window.close();
						isMenu = false;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						key = 1;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						key = 2;
						menuTimer = 0;
					}
				}
				break;
			}
		}

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		CurrentFrame += 0.005 * time;

		if (Keyboard::isKeyPressed(Keyboard::M)) isMenu = 0;  // Кнопка для разработчиков

		if (CurrentFrame > 16) CurrentFrame = 0;
		spriteVec.at(int(CurrentFrame) / 2).setTextureRect(IntRect(1920 * (int(CurrentFrame) % 2), 0, 1920, 1080));
		spriteVec.at(int(CurrentFrame) / 2).setScale(kX, kY);
		window.draw(spriteVec.at(int(CurrentFrame) / 2));

		if (isMenu)
		{
			for (std::pair<Text, String> var : textVector)
			{
				if (var.second == "mainMenu")
				{
					window.draw(var.first);
				}
			}
			window.display();
		}
	}
	mainMenuMusic.stop();
}


void Menu::pauseMenu(RenderWindow& window, Music& music)
{
	isMenu = true;
	menuTimer = 0;
	key = 1;
	CurrentFrame = 0;

	while (isMenu)
	{
		//window.clear();

		for (int i = 0; i < C; i++)
		{
			if (textVector.at(i).second == "pauseMenu")
			{
				textVector.at(i).first.setFillColor(Color::Black);
			}
		}

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		menuTimer += 0.005 * time;

		switch (key) 
		{
			case 1:
			{
				textVector.at(3).first.setFillColor(Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						isMenu = false;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						key = 2;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						key = 3;
						menuTimer = 0;
					}
				}
				break;
			}
			case 2:
			{
				textVector.at(4).first.setFillColor(Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						isMenu = false;
						Menu::settingsMenu(window, music);
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						key = 3;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						key = 1;
						menuTimer = 0;
					}
				}
				break;
			}
			case 3:
			{
				textVector.at(5).first.setFillColor(Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						isMenu = false;
						Menu::mainMenu(window, music);
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						key = 1;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						key = 2;
						menuTimer = 0;
					}
				}
				break;
			}
		}


		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		CurrentFrame += 0.005 * time;

		if (CurrentFrame > 8) CurrentFrame = 0;
		sprPauseVec.at(int(CurrentFrame) / 2).setTextureRect(IntRect(1280 * (int(CurrentFrame) % 2), 0, 1280, 720));
		sprPauseVec.at(int(CurrentFrame) / 2).setScale(double(verticalHeight) / double(1920), double(horizontalHeight) / double(1080));
		window.draw(sprPauseVec.at(int(CurrentFrame) / 2));

		if (isMenu)
		{
			for (std::pair<Text, String> var : textVector)
			{
				if (var.second == "pauseMenu")
				{
					window.draw(var.first);
				}
			}
			window.display();
		}
	}
}


void Menu::settingsMenu(RenderWindow& window, Music& music)
{
	isMenu = 1;
	menuTimer = 0;
	key = 1;
	CurrentFrame = 0;

	while (isMenu)
	{
		//window.clear();
		volArrows.setColor(Color::Black);

		for (int i = 0; i < C; i++)
		{
			if (textVector.at(i).second == "settingsMenu")
			{
				textVector.at(i).first.setFillColor(Color::Black);
			}
		}
		for (int i = 0; i < numOfDisplay; i++)
		{
			displayVector.at(i).first.setFillColor(Color::Black);
		}

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		menuTimer += 0.005 * time;

		switch (key)
		{
			case 1:
			{
				textVector.at(6).first.setFillColor(Color(67, 0, 229, 255));
				textVector.at(7).first.setFillColor(Color(67, 0, 229, 255));
				textVector.at(8).first.setFillColor(Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if ((Keyboard::isKeyPressed(Keyboard::Enter)) || Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right))
					{
						isDisp = !isDisp;
						if (isDisp == 1)
						{
							//sf::Vector2< int >::Vector2(1500, 1000);
							//window.setSize(Vector2u(840,620));
							/*Vector2u a(0,0);
							a = window.getSize();*/
							window.create(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork", sf::Style::Fullscreen);
							window.setVerticalSyncEnabled(true);
						}
						else window.create(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork", sf::Style::Default);
						updateSize();
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						key = 2;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						key = 5;
						menuTimer = 0;
					}
					break;
				}
			}
			case 2:
			{
				textVector.at(13).first.setFillColor(Color(67, 0, 229, 255));
				displayVector.at(whatDisplay).first.setFillColor(Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (Keyboard::isKeyPressed(Keyboard::Right))
					{
						whatDisplay++;
						if (whatDisplay > numOfDisplay - 1)
						{
							whatDisplay = 0;
						}
						verticalHeight = displayVector.at(whatDisplay).second.first;
						horizontalHeight = displayVector.at(whatDisplay).second.second;
						if (isDisp == 1)
						{
							window.create(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork", sf::Style::Fullscreen);
						}
						else
						{
							window.create(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork");
						}
						updateSize();
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						whatDisplay--;
						if (whatDisplay < 0)
						{
							whatDisplay = numOfDisplay - 1;
						}
						verticalHeight = displayVector.at(whatDisplay).second.first;
						horizontalHeight = displayVector.at(whatDisplay).second.second;
						if (isDisp == 1)
						{
							window.create(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork", sf::Style::Fullscreen);
						}
						else
						{
							window.create(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork");
						}
						updateSize();
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						key = 3;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						key = 1;
						menuTimer = 0;
					}
				}
				break;
			}
			case 3:
			{
				textVector.at(10).first.setFillColor(Color(67, 0, 229, 255));
				textVector.at(9).first.setFillColor(Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if ((Keyboard::isKeyPressed(Keyboard::Enter)) || (Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::Right)))
					{
						isVol = !isVol;
						if (isVol == 1)
						{
							oldValue = volValue;
							volValue = 0;
							volArrows.setTextureRect(IntRect(0, volValue * 36, 252, 36));
						}
						else
						{
							if (oldValue == 0) volValue = 4;
							else volValue = oldValue;
							volArrows.setTextureRect(IntRect(0, volValue * 36, 252, 36));
						}
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						key = 4;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						key = 2;
						menuTimer = 0;
					}
				}
				if (volValue == 0)
				{
					music.stop();
					musicFlag = 1;
				}
				else
				{
					if (musicFlag == 1)
					{
						music.play();
						music.setVolume(25 * volValue);
						//mainMenuMusic.setVolume(25 * volValue);
						//bestiaryMusic.setVolume(25 * volValue);
						musicFlag = 0;
					}
					else
					{
						music.setVolume(25 * volValue);
						/*mainMenuMusic.setVolume(25 * volValue);
						bestiaryMusic.setVolume(25 * volValue);*/
					}
				}
				break;
			}
			case 4:
			{
				textVector.at(11).first.setFillColor(Color(67, 0, 229, 255));
				volArrows.setColor(Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (Keyboard::isKeyPressed(Keyboard::Right))
					{
						if (isVol == 0)
						{
							volValue += 1;
							if (volValue == 5) volValue = 0;
							volArrows.setTextureRect(IntRect(0, volValue * 36, 252, 36));
							if (volValue == 0)
							{
								oldValue = 0;
								isVol = 1;
							}
						}
						else
						{
							volValue = 1;
							volArrows.setTextureRect(IntRect(0, volValue * 36, 252, 36));
							isVol = 0;
						}
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						if (isVol == 0)
						{
							volValue -= 1;
							if (volValue == -1) volValue = 4;

							volArrows.setTextureRect(IntRect(0, volValue * 36, 252, 36));

							if (volValue == 0)
							{
								oldValue = 0;
								isVol = 1;
							}
						}
						else
						{
							volValue = 4;
							volArrows.setTextureRect(IntRect(0, volValue * 36, 252, 36));
							isVol = 0;
						}
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						key = 5;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						key = 3;
						menuTimer = 0;
					}
				}
				if (volValue == 0) { music.stop(); musicFlag = 1; }
				else
				{
					if (musicFlag == 1) { music.play(); music.setVolume(25 * volValue); musicFlag = 0; }
					else music.setVolume(25 * volValue);
				}
				break;
			}
			case 5:
			{
				textVector.at(12).first.setFillColor(Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						isMenu = false;
						Menu::pauseMenu(window, music);
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						key = 1;
						menuTimer = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						key = 4;
						menuTimer = 0;
					}
				}
				break;
			}
			default:
			{

			}
		}

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		CurrentFrame += 0.005 * time;

		if (CurrentFrame > 8) CurrentFrame = 0;
		sprPauseVec.at(int(CurrentFrame) / 2).setTextureRect(IntRect(1280 * (int(CurrentFrame) % 2), 0, 1280, 720));
		sprPauseVec.at(int(CurrentFrame) / 2).setScale(double(verticalHeight) / double(1920), double(horizontalHeight) / double(1080));
		window.draw(sprPauseVec.at(int(CurrentFrame) / 2));

		volArrows.setScale(kX, kY);

		if (isMenu)
		{
			window.draw(textVector.at(6).first);
			window.draw(textVector.at(13).first);
			window.draw(textVector.at(8-int(!isDisp)).first);
			window.draw(displayVector.at(whatDisplay).first);
			window.draw(volArrows);
			window.draw(textVector.at(10-int(!isVol)).first);
			window.draw(textVector.at(11).first);
			window.draw(textVector.at(12).first);
			window.display();
		}
	}
}

void Menu::bestiary(RenderWindow& window, Music& musicToStop)
{
	isMenu = 1;
	menuTimer = 0;
	key = 1;
	CurrentFrame = 0;
	whatMonster = 0;
	
	mainMenuMusic.stop();
	bestiaryMusic.play();
	bestiaryMusic.setLoop(true);

	while (isMenu)
	{
		for (int i = 0; i < numOfMonstres; i++)
		{
			bestiaryVector.at(i).first.setFillColor(Color(85, 54, 18, 255));
			bestiaryVector.at(i).second.setFillColor(Color(85, 54, 18, 255));
		}
		for (int i = 0; i < numOfButton; i++)
		{
			buttonVector.at(i).setFillColor(Color(85, 54, 18, 255));
		}
		window.clear();

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		menuTimer += 0.005 * time;

		switch (key)
		{
		case 1:
		{
			buttonVector.at(1).setFillColor(Color(21, 56, 104, 255));
			if (menuTimer > keyDelay)
			{
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					whatMonster--;
					if (whatMonster < 0)
					{
						whatMonster = numOfMonstres - 1;
					}
					CurrentFrame = 0;
					menuTimer = 0;
				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					whatMonster++;
					if (whatMonster > numOfMonstres - 1)
					{
						whatMonster = 0;
					}
					CurrentFrame = 0;
					menuTimer = 0;
				}
				if ((Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::Up)))
				{
					key = 2;
					menuTimer = 0;
				}
			}
			break;
		}
		case 2:
		{
			buttonVector.at(2).setFillColor(Color(21, 56, 104, 255));
			if (menuTimer > keyDelay)
			{
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					bestiaryMusic.stop();
					mainMenu(window, musicToStop);
					isMenu = false;
					
				}
				if ((Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::Up)))
				{
					key = 1;
					menuTimer = 0;

				}
			}
			break;
		}
		}


		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		CurrentFrame += 0.005 * time;

		about.setScale(double(verticalHeight) / double(1920), double(horizontalHeight) / double(1080));

		if (isMenu)
		{
			window.draw(about);
			if (CurrentFrame > 12) CurrentFrame = 0;
			bestiarySpriteVec.at(whatMonster).setTextureRect(IntRect(256 * int(CurrentFrame), 0, 256, 256));
			bestiarySpriteVec.at(whatMonster).setScale(double(verticalHeight) / double(1920), double(horizontalHeight) / double(1080));
			window.draw(bestiarySpriteVec.at(whatMonster));
			window.draw(bestiaryVector.at(whatMonster).first);
			window.draw(bestiaryVector.at(whatMonster).second);
			for (Text var : buttonVector)
			{
				window.draw(var);
			}
			window.display();
		}	
	}
}

void Menu::updateSize()
{
	kX = double(verticalHeight) / double(1920);
	kY = double(horizontalHeight) / double(1080);
	for (int i = 0; i < numOfDisplay; i++)
	{
		displayVector.at(i).first.setPosition(360 * kX, 597 * kY);
		displayVector.at(i).first.setCharacterSize(int(horizontalHeight / 27));
	}
	for (int i = 0; i < C; i++)
	{
		textVector.at(i).first.setCharacterSize(int(horizontalHeight / 27));
	}
	textVector.at(0).first.setPosition(40 * kX, 440 * kY);  // Новая игра 
	textVector.at(1).first.setPosition(40 * kX, 520 * kY);  // Авторы
	textVector.at(2).first.setPosition(40 * kX, 600 * kY);  // Выход из игры

	textVector.at(3).first.setPosition(360 * kX, 590 * kY);  // Продолжить
	textVector.at(4).first.setPosition(360 * kX, 670 * kY);  // Настройки
	textVector.at(5).first.setPosition(360 * kX, 750 * kY);  // Главное меню

	textVector.at(6).first.setPosition(360 * kX, 455 * kY);  // Режим:
	textVector.at(7).first.setPosition(360 * kX, 495 * kY);  // Оконный
	textVector.at(8).first.setPosition(360 * kX, 495 * kY);  // Полноэкранный
	textVector.at(9).first.setPosition(360 * kX, 655 * kY);  // Звук: Вкл
	textVector.at(10).first.setPosition(360 * kX, 655 * kY);  // Звук: Выкл
	textVector.at(11).first.setPosition(360 * kX, 715 * kY);  // Громкость
	textVector.at(12).first.setPosition(360 * kX, 819 * kY);  // Назад
	textVector.at(13).first.setPosition(360 * kX, 550 * kY);  // Разрешение
	for (int i = 0; i < 4; i++)  // Вектор спрайтов бэкграунда Меню Паузы
	{
		sprPauseVec.at(i).setPosition(int(verticalHeight / 2) * (1 - double(1280) / double(1920)), int(horizontalHeight / 2) * (1 - double(720) / double(1080)));
	}
	for (size_t i = 0; i < numOfMonstres; i++)
	{
		bestiaryVector.at(i).first.setCharacterSize(int(horizontalHeight / 10.8));  //+++++++++++++++++++++++++++
		bestiaryVector.at(i).first.setPosition(400 * kX, 250 * kY);  //+++++++++++++++++++++++++++
		bestiaryVector.at(i).second.setCharacterSize(int(horizontalHeight / 21.6));  //+++++++++++++++++++++++++++
		bestiaryVector.at(i).second.setPosition(400 * kX, 400 * kY);  //+++++++++++++++++++++++++++
	}
	for (size_t i = 0; i < numOfButton; i++)
	{
		buttonVector.at(i).setCharacterSize(int(horizontalHeight / 10.8));  //+++++++++++++++++++++++++++
		buttonVector.at(i).setPosition(600 * kX, 600 * kY);  //+++++++++++++++++++++++++++
	}
	buttonVector.at(0).setPosition(650 * kX, 0 * kY);  // Бестиарий  //+++++++++++++++++++++++++++
	buttonVector.at(1).setPosition(300 * kX, 700 * kY);  // Выбор  //+++++++++++++++++++++++++++
	buttonVector.at(2).setPosition(300 * kX, 800 * kY);  // Назад  //+++++++++++++++++++++++++++
	buttonVector.at(0).setCharacterSize(int(horizontalHeight / 5.4));  //+++++++++++++++++++++++++++

	for (size_t i = 0; i < numOfMonstres; i++)  // Вектор спрайтов существ Бестриария
	{
		bestiarySpriteVec.at(i).setPosition(1150 * kX, 400 * kY);  //+++++++++++++++++++++++++++
	}
	volArrows.setPosition(360 * kX, 773 * kY);  //+++++++++++++++++++++++++++
}