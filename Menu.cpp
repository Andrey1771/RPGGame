#include "Menu.h"
#include "Camera.h"
#include <iostream>
extern int verticalHeight;
extern int horizontalHeight;
extern sf::Clock clock3;

Menu::Menu(sf::RenderWindow& window, Music& music, sf::View* camera)
{
	this->camera = camera;
	kX = double(camera->getSize().x) / double(1920);
	kY = double(camera->getSize().y) / double(1080);
	resizeMistakeX = 1920.0 / 1280.0;
	resizeMistakeY = 1080.0 / 720.0;

	whatDisplay = 5;
	isDisp = 0;

	font.loadFromFile("resource\\Fonts\\mainFonts\\18959.ttf");
	for (size_t i = 0; i < numOfDisplay; i++)
	{
		displayVector.push_back(std::pair< Text, std::pair<int, int>>(Text(), std::pair<int, int>(0, 0)));
		displayVector.back().first.setFont(font);
		displayVector.back().first.setString(displayArray[i].first);
		displayVector.back().second.first = displayArray[i].second.first;
		displayVector.back().second.second = displayArray[i].second.second;
	}
	displayVector.at(5).second.first = verticalHeight;
	displayVector.at(5).second.second = horizontalHeight;
	displayVector.at(5).first.setString(std::to_string(verticalHeight) + "x" + std::to_string(horizontalHeight) + L" - пользовательское");

	for (size_t i = 0; i < numOfMenuButtons; i++)
	{
		textVector.push_back(std::pair<sf::Text, sf::String>(Text(), "Categories"));
		textVector.back().first.setFont(font);
		textVector.back().first.setString(nameArray[i].first);
		textVector.back().second = nameArray[i].second;
	}

	bestiaryFont.loadFromFile("resource\\Fonts\\bestiaryFonts\\13859.ttf");
	for (size_t i = 0; i < numOfMonstres; i++)
	{
		bestiaryVector.push_back(std::pair<Text, Text>(Text(), Text()));
		bestiaryVector.back().first.setFont(bestiaryFont);
		bestiaryVector.back().first.setString(bestiaryArray[i].first);
		bestiaryVector.back().second.setFont(bestiaryFont);
		bestiaryVector.back().second.setString(bestiaryArray[i].second);
		bestiaryVector.back().second.setLineSpacing(0.6);
	}
	
	for (size_t i = 0; i < numOfButton; i++)
	{
		buttonVector.push_back(Text());
		buttonVector.back().setFont(bestiaryFont);
		buttonVector.back().setString(buttonArray[i]);
		buttonVector.back().setStyle(Text::Bold);
	}

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
		bestiarySpriteVec.back().setScale(kX, kY);
	}

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
		spriteVec.back().setScale(kX, kY);
	}

	for (size_t i = 0; i < 4; i++)  // Вектор текстур бэкграунда Меню Паузы
	{
		texPauseVec.push_back(Texture());
		texPauseVec.back().loadFromFile("resource\\Menu\\pauseMenu\\backGround_" + std::to_string(i) + ".png");
	}

	for (size_t i = 0; i < 4; i++)  // Вектор спрайтов бэкграунда Меню Паузы
	{
		sprPauseVec.push_back(Sprite());
		sprPauseVec.back().setTexture(texPauseVec.at(i));
		sprPauseVec.back().setTextureRect(IntRect(0, 0, 1280, 720));
		sprPauseVec.back().setScale(kX * resizeMistakeX, kY * resizeMistakeY);
	}

	bestiaryMusic.openFromFile("resource\\Audio\\bestiaryMusic.ogg");
	mainMenuMusic.openFromFile("resource\\Audio\\mainMenuMusic.ogg");

	arrow.loadFromFile("resource\\Menu\\settingsMenu\\volumeArrows.png");
	volArrows.setTexture(arrow);
	volArrows.setTextureRect(IntRect(0, 144, 252, 36));
	volArrows.setScale(kX * resizeMistakeX, kY * resizeMistakeY);

	Menu::updateSize();
	Menu:mainMenu(window, music);
}

Menu::~Menu()
{
}

void Menu::mainMenu(RenderWindow& window, Music& musicToStop)
{
	Menu::updateSize();

	if (camera == nullptr)
	{
		std::cout << "Camera not found!" << std::endl;
		return;
	}

	isMenu = true;
	key = 1; // Номер текущей кнопки
	CurrentFrame = 0; // Таймер для анимации бэкграунда 
	menuTimer = 0; // Таймер для нажатия клавиш

	musicToStop.stop();
	mainMenuMusic.play();
	mainMenuMusic.setLoop(true);
	mainMenuMusic.setVolume(25 * volValue);

	while (isMenu)
	{
		for (int i = 0; i < numOfMenuButtons; i++)
		{
			if (textVector.at(i).second == "mainMenu")
			{
				textVector.at(i).first.setFillColor(Color::White);
			}
		}

		window.clear();
		
		Menu::frameCreator(window);
		Menu::createKeys(6);
		switch (key)
		{
		case 1:
		{
			textVector.at(14).first.setFillColor(Color(176, 227, 23, 255));  // Продолжить
			if (menuTimer > keyDelay)
			{
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					Menu::closeMainMenu(musicToStop);
				}
			}
			break;
		}
		case 2:
		{
			textVector.at(0).first.setFillColor(Color(176, 227, 23, 255));  // Новая игра (пока что тоже самое, что и продолжить)
			if (menuTimer > keyDelay)
			{
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					Menu::closeMainMenu(musicToStop);
				}
			}
			break;
		}
		case 3:
		{
			textVector.at(15).first.setFillColor(Color(176, 227, 23, 255));  // Настройки 
			if (menuTimer > keyDelay)
			{
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					Menu::openSettingsMenu(window, mainMenuMusic);
					isMenu = true;
					key = 1;
				}
			}
			break;
		}
		case 4:
		{
			textVector.at(1).first.setFillColor(Color(176, 227, 23, 255));  // Бестиарий
			if (menuTimer > keyDelay)
			{
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					Menu::openBestiary(window, musicToStop);
				}
			}
			break;
		}
		case 5:
		{
			textVector.at(16).first.setFillColor(Color(176, 227, 23, 255));  // Авторы
			if (menuTimer > keyDelay)
			{
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
				}
			}
			break;
		}
		case 6:
		{
			textVector.at(2).first.setFillColor(Color(176, 227, 23, 255));  // Выход
			if (menuTimer > keyDelay)
			{
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					Menu::closeGame(window);
				}
			}
			break;
		}
		}


		if (CurrentFrame > 16) CurrentFrame = 0;
		spriteVec.at(int(CurrentFrame) / 2).setTextureRect(IntRect(1920 * (int(CurrentFrame) % 2), 0, 1920, 1080));

		if (isMenu)
		{
			window.draw(spriteVec.at(int(CurrentFrame) / 2));
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
	Menu::updateSize();
	if (camera == nullptr)
	{
		std::cout << "Camera not found!" << std::endl;
		return;
	}
	isMenu = true;
	menuTimer = 0;
	key = 1;
	CurrentFrame = 0;

	while (isMenu)
	{
		//window.clear();

		for (int i = 0; i < numOfMenuButtons; i++)
		{
			if (textVector.at(i).second == "pauseMenu")
			{
				textVector.at(i).first.setFillColor(Color::Black);
			}
		}

		Menu::frameCreator(window);
		Menu::createKeys(3);
		textVector.at(key + 2).first.setFillColor(Color(67, 0, 229, 255));
		if (menuTimer > keyDelay)
		{
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				switch (key)
				{
				case 1:
				{
					Menu::closePauseMenu();
					break;
				}
				case 2:
				{
					Menu::openSettingsMenu(window, music);
					isMenu = true;
					key = 1;
					break;
				}
				case 3:
				{
					Menu::openMainMenu(window, music);
					break;
				}
				}
			}
		}

		if (CurrentFrame > 8) CurrentFrame = 0;
		sprPauseVec.at(int(CurrentFrame) / 2).setTextureRect(IntRect(1280 * (int(CurrentFrame) % 2), 0, 1280, 720));
		
		if (isMenu)
		{
			window.draw(sprPauseVec.at(int(CurrentFrame) / 2));
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
	Menu::updateSize();
	if (camera == nullptr)
	{
		std::cout << "Camera not found!" << std::endl;
		return;
	}
	isMenu = 1;
	menuTimer = 0;
	key = 1;
	CurrentFrame = 0;

	while (isMenu)
	{
		isNewDisplay = false;
		volArrows.setColor(Color::Black);

		for (int i = 0; i < numOfMenuButtons; i++)
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

		verticalHeight = window.getSize().x;
		horizontalHeight = window.getSize().y;
		for (size_t i = 0; i < numOfDisplay; i++)
		{
			if ((verticalHeight == displayVector.at(i).second.first) && (horizontalHeight == displayVector.at(i).second.second)) { isNewDisplay = true; }
		}
		if (isNewDisplay == false)
		{
			displayVector.at(5).second.first = verticalHeight;
			displayVector.at(5).second.second = horizontalHeight;
			displayVector.at(5).first.setString(std::to_string(verticalHeight) + "x" + std::to_string(horizontalHeight) + L" - пользовательское");
			whatDisplay = 5;
		}
		
		Menu::frameCreator(window);
		Menu::createKeys(5);
		switch (key)
		{
		case 1:  // Режимы экрана: Полноэкранный/оконный
		{
			textVector.at(6).first.setFillColor(Color(67, 0, 229, 255));
			textVector.at(7).first.setFillColor(Color(67, 0, 229, 255));
			textVector.at(8).first.setFillColor(Color(67, 0, 229, 255));
			if (menuTimer > keyDelay)
			{
				if ((Keyboard::isKeyPressed(Keyboard::Enter)) || Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right))
				{
					Menu::screenModes(window);
				}	
			}
			break;
		}
		case 2:  // Разрешение экрана
		{
			textVector.at(13).first.setFillColor(Color(67, 0, 229, 255));
			displayVector.at(whatDisplay).first.setFillColor(Color(67, 0, 229, 255));
			if (menuTimer > keyDelay)
			{
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					Menu::screenResolutions(window, false);
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					Menu::screenResolutions(window, true);
				}
				//window.clear();
			}
			break;
		}
		case 3:  // Вкл/Выкл звук
		{
			textVector.at(10).first.setFillColor(Color(67, 0, 229, 255));
			textVector.at(9).first.setFillColor(Color(67, 0, 229, 255));
			if (menuTimer > keyDelay)
			{
				if ((Keyboard::isKeyPressed(Keyboard::Enter)) || (Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::Right)))
				{
					Menu::onOffMusic(music);
				}
			}
			break;
		}
		case 4:  // Ползунок звука
		{
			textVector.at(11).first.setFillColor(Color(67, 0, 229, 255));
			volArrows.setColor(Color(67, 0, 229, 255));
			if (menuTimer > keyDelay)
			{
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					Menu::chooseVolume(music, false);
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					Menu::chooseVolume(music, true);
				}
			}
			break;
		}
		case 5:  // Выход в меню паузы
		{
			textVector.at(12).first.setFillColor(Color(67, 0, 229, 255));
			if (menuTimer > keyDelay)
			{
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					Menu::closeSettingsMenu(window, music);
				}
			}
			break;
		}
		}
		Menu::updateSize();
		if (CurrentFrame > 8) CurrentFrame = 0;
		sprPauseVec.at(int(CurrentFrame) / 2).setTextureRect(IntRect(1280 * (int(CurrentFrame) % 2), 0, 1280, 720));

		if (isMenu)
		{
			window.draw(sprPauseVec.at(int(CurrentFrame) / 2));
			window.draw(textVector.at(6).first);
			window.draw(textVector.at(13).first);
			window.draw(textVector.at(8 - int(!isDisp)).first);
			window.draw(displayVector.at(whatDisplay).first);
			window.draw(volArrows);
			window.draw(textVector.at(10 - int(isVol)).first);
			window.draw(textVector.at(11).first);
			window.draw(textVector.at(12).first);
			window.display();
		}
	}
}

void Menu::bestiary(RenderWindow& window, Music& musicToStop)
{
	Menu::updateSize();
	if (camera == nullptr)
	{
		std::cout << "Camera not found!" << std::endl;
		return;
	}
	isMenu = 1;
	menuTimer = 0;
	key = 1;
	CurrentFrame = 0;
	whatMonster = 0;

	mainMenuMusic.stop();
	bestiaryMusic.play();
	bestiaryMusic.setLoop(true);
	bestiaryMusic.setVolume(25 * volValue);

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

		Menu::frameCreator(window);
		Menu::createKeys(2);
		buttonVector.at(key).setFillColor(Color(21, 56, 104, 255));
		if (menuTimer > keyDelay)
		{
            switch (key)
            {
            case 1:
            {
				if ((Keyboard::isKeyPressed(Keyboard::Enter)) || (Keyboard::isKeyPressed(Keyboard::Right)))
				{
					Menu::chooseMonster(false);
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					Menu::chooseMonster(true);
				}
                break;
            }
            case 2:
            {
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					Menu::closeBestiary(window, musicToStop);
				}
                break;
            }
            }
		}
		
		if (CurrentFrame > 12) CurrentFrame = 0;
		bestiarySpriteVec.at(whatMonster).setTextureRect(IntRect(256 * int(CurrentFrame), 0, 256, 256));

		if (isMenu)
		{
			window.draw(about);
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
	if (camera == nullptr)
	{
		std::cout << "Camera not found!" << std::endl;
		return;
	}
	cameraOffsetX = camera->getCenter().x - camera->getSize().x / 2;
	cameraOffsetY = camera->getCenter().y - camera->getSize().y / 2;
	kX = double(camera->getSize().x) / double(1920);
	kY = double(camera->getSize().y) / double(1080);
	resizeMistakeX = 1920.0 / 1280.0;
	resizeMistakeY = 1080.0 / 720.0;
	
	for (int i = 0; i < numOfDisplay; i++)
	{
		displayVector.at(i).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (597 - 180) * kY * resizeMistakeY + cameraOffsetY);
		displayVector.at(i).first.setCharacterSize(int(camera->getSize().y * resizeMistakeY / 27));
	}
	
	for (int i = 0; i < numOfMenuButtons; i++)
	{
		if (textVector.at(i).second == "mainMenu")
		{
			textVector.at(i).first.setCharacterSize(int(camera->getSize().y / 27));
		}
		else
		{
			textVector.at(i).first.setCharacterSize(int(camera->getSize().y * resizeMistakeY / 27));
		}
	}
	
	textVector.at(14).first.setPosition(40 * kX + cameraOffsetX, 350 * kY + cameraOffsetY);  // Продолжить
	textVector.at(0).first.setPosition(40 * kX + cameraOffsetX, 410 * kY + cameraOffsetY);  // Новая игра 
	textVector.at(15).first.setPosition(40 * kX + cameraOffsetX, 470 * kY + cameraOffsetY);  // Настройки
	textVector.at(1).first.setPosition(40 * kX + cameraOffsetX, 530 * kY + cameraOffsetY);  // Бестиарий
	textVector.at(16).first.setPosition(40 * kX + cameraOffsetX, 590 * kY + cameraOffsetY);  // Авторы
	textVector.at(2).first.setPosition(40 * kX + cameraOffsetX, 650 * kY + cameraOffsetY);  // Выход из игры

	textVector.at(3).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (590 - 180) * kY * resizeMistakeY + cameraOffsetY);  // Продолжить
	textVector.at(4).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (670 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Настройки
	textVector.at(5).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (750 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Главное меню

	textVector.at(6).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (455 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Режим:
	textVector.at(7).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (495 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Оконный
	textVector.at(8).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (495 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Полноэкранный
	textVector.at(9).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (655 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Звук: Вкл
	textVector.at(10).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (655 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Звук: Выкл
	textVector.at(11).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (715 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Громкость
	textVector.at(12).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (819 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Назад
	textVector.at(13).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (550 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Разрешение
	
	for (int i = 0; i < 4; i++)  // Вектор спрайтов бэкграунда Меню Паузы
	{
		sprPauseVec.at(i).setPosition(camera->getCenter().x - kX * resizeMistakeX * sprPauseVec.at(i).getTexture()->getSize().x / 4,
			camera->getCenter().y - kY * resizeMistakeY * sprPauseVec.at(i).getTexture()->getSize().y / 2);
	}
	
	for (int i = 0; i < 8; i++)
	{
		spriteVec.at(i).setPosition(camera->getCenter().x - kX * spriteVec.at(i).getTexture()->getSize().x / 4,
			camera->getCenter().y - kY * spriteVec.at(i).getTexture()->getSize().y / 2);
	}
	
	for (size_t i = 0; i < numOfMonstres; i++)
	{
		bestiaryVector.at(i).first.setCharacterSize(int(camera->getSize().y / 10.8));
		bestiaryVector.at(i).first.setPosition(400 * kX + cameraOffsetX, 350 * kY + cameraOffsetY);
		bestiaryVector.at(i).second.setCharacterSize(int(camera->getSize().y / 21.6));
		bestiaryVector.at(i).second.setPosition(400 * kX + cameraOffsetX, 475 * kY + cameraOffsetY);
	}
	
	for (size_t i = 0; i < numOfButton; i++)
	{
		buttonVector.at(i).setCharacterSize(int(camera->getSize().y / 20));
		buttonVector.at(i).setPosition(600 * kX + cameraOffsetX, 600 * kY + cameraOffsetY);
	}
	
	buttonVector.at(0).setPosition(400 * kX + cameraOffsetX, 0 * kY + cameraOffsetY);  // Бестиарий
	buttonVector.at(1).setPosition(400 * kX + cameraOffsetX, 700 * kY + cameraOffsetY);  // Выбор
	buttonVector.at(2).setPosition(400 * kX + cameraOffsetX, 750 * kY + cameraOffsetY);  // Назад
	buttonVector.at(0).setCharacterSize(int(camera->getSize().y / 5.4));

	for (size_t i = 0; i < numOfMonstres; i++)  // Вектор спрайтов существ Бестриария
	{
		bestiarySpriteVec.at(i).setPosition(1300 * kX + cameraOffsetX, 400 * kY + cameraOffsetY);
	}

	volArrows.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (773 - 180) * kY * resizeMistakeY + cameraOffsetY);

	about.setPosition(camera->getCenter().x - kX * about.getTexture()->getSize().x / 2,
		camera->getCenter().y - kY * about.getTexture()->getSize().y / 2);
}

void Menu::createKeys(int numOfKeys)
{
	if (menuTimer > keyDelay)
	{
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			key++;
			if (key > numOfKeys)
			{
				key = 1;
			}
			menuTimer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			key--;
			if (key < 1)
			{
				key = numOfKeys;
			}
			menuTimer = 0;
		}
	}
}

void Menu::closeMainMenu(Music& musicToStop)
{
	clock3.restart();
	isMenu = false;
	musicToStop.play();
	musicToStop.setVolume(25 * volValue);
	menuTimer = 0;
}

void Menu::openBestiary(RenderWindow& window, Music& musicToStop)
{
	isMenu = false;
	Menu::bestiary(window, musicToStop);
	menuTimer = 0;
}

void Menu::closeGame(RenderWindow& window)
{
	window.close();
	isMenu = false;
	menuTimer = 0;
}

void Menu::chooseMonster(bool leftArrow)
{
	if (leftArrow)
	{
		whatMonster--;
		if (whatMonster < 0)
		{
			whatMonster = numOfMonstres - 1;
		}
	}
	else
	{
		whatMonster++;
		if (whatMonster > numOfMonstres - 1)
		{
			whatMonster = 0;
		}
	}
	CurrentFrame = 0;
	menuTimer = 0;
}

void Menu::closeBestiary(RenderWindow& window, Music& musicToStop)
{
	clock3.restart();
	bestiaryMusic.stop();
	mainMenu(window, musicToStop);
	isMenu = false;
}

void Menu::closePauseMenu()
{
	isMenu = false;
	clock3.restart();
	menuTimer = 0;
}

void Menu::openSettingsMenu(RenderWindow& window, Music& music)
{
	isMenu = false;
	Menu::settingsMenu(window, music);
	menuTimer = 0;
}

void Menu::openMainMenu(RenderWindow& window, Music& music)
{
	isMenu = false;
	Menu::mainMenu(window, music);
	menuTimer = 0;
}

void Menu::screenModes(RenderWindow& window)
{
	isDisp = !isDisp;
	if (isDisp == 1)
	{
		window.create(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork", sf::Style::Fullscreen);
		window.setVerticalSyncEnabled(true);
	}
	else
	{
		window.create(sf::VideoMode(verticalHeight, horizontalHeight), "SFMLwork", sf::Style::Default);
		window.setVerticalSyncEnabled(true);
		//isMenu = false;
	}
	Menu::updateSize();
	menuTimer = 0;
}

void Menu::screenResolutions(RenderWindow& window, bool leftArrow)
{
	if (leftArrow)
	{
		whatDisplay--;
		if (whatDisplay < 0)
		{
			whatDisplay = numOfDisplay - 1;
		}
	}
	else
	{
		whatDisplay++;
		if (whatDisplay > numOfDisplay - 1)
		{
			whatDisplay = 0;
		}
	}
	verticalHeight = displayVector.at(whatDisplay).second.first;
	horizontalHeight = displayVector.at(whatDisplay).second.second;
	if (isDisp == 1)
	{
		window.setSize(sf::Vector2u(verticalHeight, horizontalHeight));
	}
	else
	{
		window.setSize(sf::Vector2u(verticalHeight, horizontalHeight));
	}
	Menu::updateSize();
	menuTimer = 0;
}

void Menu::onOffMusic(Music& music)
{
	isVol = !isVol;
	if (isVol)
	{
		music.play();
		if (!volValue)
		{
			volValue = 4;
		}
		music.setVolume(25 * volValue);
	}
	else
	{
		music.stop();
	}
	volArrows.setTextureRect(IntRect(0, isVol * volValue * 36, 252, 36));
	menuTimer = 0;
}

void Menu::closeSettingsMenu(RenderWindow& window, Music& music)
{
	clock3.restart();
	isMenu = false;
	//Menu::pauseMenu(window, music);
	menuTimer = 0;
}

void Menu::frameCreator(RenderWindow& window)
{
	float time = clock2.getElapsedTime().asMicroseconds();
	clock2.restart();
	time = time / 800;
	menuTimer += 0.005 * time;
	CurrentFrame += 0.005 * time;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
}

void Menu::chooseVolume(Music& music, bool leftArrow)
{
	if (leftArrow)
	{
		if (!isVol)
		{
			volValue = 4;
			isVol = 1;
		}
		else
		{
			volValue -= 1;
			isVol = 1;
		}
		if (volValue == 0)
		{
			isVol = 0;
			music.stop();
		}
		if (volValue == 4)
		{
			music.play();
		}
	}
	else
	{
		if (!isVol)
		{
			volValue = 1;
			isVol = 1;
		}
		else
		{
			volValue += 1;
			isVol = 1;
		}
		if (volValue > 4)
		{
			volValue = 0;
			isVol = 0;
			music.stop();
		}
		if (volValue == 1)
		{
			music.play();
		}
	}
	music.setVolume(25 * volValue);
	volArrows.setTextureRect(IntRect(0, volValue * 36, 252, 36));
	menuTimer = 0;
}