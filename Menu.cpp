#include "Menu.h"
#include "Camera.h"
#include <iostream>


extern int verticalHeight;
extern int horizontalHeight;

namespace Menu
{
	Menu::Menu(sf::RenderWindow& window, sf::Music& music, Camera* camera, sf::Clock& clock)
	{
		this->clock = &clock;
		this->camera = camera;
		kX = double(camera->getView()->getSize().x) / double(1920);
		kY = double(camera->getView()->getSize().y) / double(1080);
		resizeMistakeX = 1920.0 / 1280.0;
		resizeMistakeY = 1080.0 / 720.0;

		font.loadFromFile("resource\\Fonts\\mainFonts\\18959.ttf");

		for (size_t i = 0; i < numOfMenuButtons; i++)
		{
			textVector.push_back(std::pair<sf::Text, sf::String>(sf::Text(), "Categories"));
			textVector.back().first.setFont(font);
			textVector.back().first.setString(nameArray[i].first);
			textVector.back().second = nameArray[i].second;
		}

		for (size_t i = 0; i < 8; i++)  // Вектор текстур бэкграунда Главного Меню
		{
			textureVec.push_back(sf::Texture());
			textureVec.back().loadFromFile("resource\\Menu\\mainMenu\\backGround_" + std::to_string(i) + ".png");
		}

		for (size_t i = 0; i < 8; i++)  // Вектор спрайтов бэкграунда Главного Меню
		{
			spriteVec.push_back(sf::Sprite());
			spriteVec.back().setTexture(textureVec.at(i));
			spriteVec.back().setTextureRect(sf::IntRect(0, 0, 1920, 1080));
			spriteVec.back().setScale(kX, kY);
		}

		for (size_t i = 0; i < 4; i++)  // Вектор текстур бэкграунда Меню Паузы
		{
			texPauseVec.push_back(sf::Texture());
			texPauseVec.back().loadFromFile("resource\\Menu\\pauseMenu\\backGround_" + std::to_string(i) + ".png");
		}

		for (size_t i = 0; i < 4; i++)  // Вектор спрайтов бэкграунда Меню Паузы
		{
			sprPauseVec.push_back(sf::Sprite());
			sprPauseVec.back().setTexture(texPauseVec.at(i));
			sprPauseVec.back().setTextureRect(sf::IntRect(0, 0, 1280, 720));
			sprPauseVec.back().setScale(kX * resizeMistakeX, kY * resizeMistakeY);
		}

		whatDisplay = 5;
		isDisp = 0;

		for (size_t i = 0; i < numOfDisplay; i++)
		{
			displayVector.push_back(std::pair< sf::Text, std::pair<int, int>>(sf::Text(), std::pair<int, int>(0, 0)));
			displayVector.back().first.setFont(font);
			displayVector.back().first.setString(displayArray[i].first);
			displayVector.back().second.first = displayArray[i].second.first;
			displayVector.back().second.second = displayArray[i].second.second;
		}
		displayVector.at(5).second.first = verticalHeight;  // Пользовательское разрешение
		displayVector.at(5).second.second = horizontalHeight;
		displayVector.at(5).first.setString(std::to_string(verticalHeight) + "x" + std::to_string(horizontalHeight) + " - пользовательское");

		displayVector.at(6).second.first = GetSystemMetrics(SM_CXSCREEN);  // Разрешение дисплея пользователя
		displayVector.at(6).second.second = GetSystemMetrics(SM_CYSCREEN);
		displayVector.at(6).first.setString(std::to_string(GetSystemMetrics(SM_CXSCREEN)) + "x" + std::to_string(GetSystemMetrics(SM_CYSCREEN)) + " - полный экран");

		arrow.loadFromFile("resource\\Menu\\settingsMenu\\volumeArrows.png");
		volArrows.setTexture(arrow);
		volArrows.setTextureRect(sf::IntRect(0, 144, 252, 36));
		volArrows.setScale(kX * resizeMistakeX, kY * resizeMistakeY);

		for (size_t i = 0; i < numOfMonstres; i++)  // Вектор текстур существ Бестиария
		{
			bestiaryTextureVec.push_back(sf::Texture());
			bestiaryTextureVec.back().loadFromFile("resource\\Menu\\mainMenu\\Bestiary\\sprite_" + std::to_string(i) + ".png");
		}

		for (size_t i = 0; i < numOfMonstres; i++)  // Вектор спрайтов существ Бестриария
		{
			bestiarySpriteVec.push_back(sf::Sprite());
			bestiarySpriteVec.back().setTexture(bestiaryTextureVec.at(i));
			bestiarySpriteVec.back().setTextureRect(sf::IntRect(0, 0, 256, 256));
			bestiarySpriteVec.back().setScale(kX, kY);
		}

		bestiaryFont.loadFromFile("resource\\Fonts\\bestiaryFonts\\13859.ttf");
		for (size_t i = 0; i < numOfMonstres; i++)
		{
			bestiaryVector.push_back(std::pair<sf::Text, sf::Text>(sf::Text(), sf::Text()));
			bestiaryVector.back().first.setFont(bestiaryFont);
			bestiaryVector.back().first.setString(bestiaryArray[i].first);
			bestiaryVector.back().second.setFont(bestiaryFont);
			bestiaryVector.back().second.setString(bestiaryArray[i].second);
			bestiaryVector.back().second.setLineSpacing(0.6);
		}

		for (size_t i = 0; i < numOfButton; i++)
		{
			buttonVector.push_back(sf::Text());
			buttonVector.back().setFont(bestiaryFont);
			buttonVector.back().setString(buttonArray[i]);
			buttonVector.back().setStyle(sf::Text::Bold);
		}

		bestiaryBgTexture.loadFromFile("resource\\Menu\\mainMenu\\Bestiary\\backGround.png");
		bestiaryBg.setTexture(bestiaryBgTexture);
		bestiaryBg.setPosition(0, 0);
		bestiaryBg.setScale(kX, kY);

		for (size_t i = 0; i < numOfAuthors; i++)
		{
			authorsTextVec.push_back(sf::Text());
			authorsTextVec.back().setString(authorsTextArray[i]);
			authorsTextVec.back().setFont(font);
		}

		for (size_t i = 0; i < numOfAuthorsTexture; i++)
		{
			authorsTextureVec.push_back(sf::Texture());
			authorsTextureVec.back().loadFromFile("resource\\Menu\\mainMenu\\Authors\\authors_" + std::to_string(i) + ".png");
		}

		for (size_t i = 0; i < numOfAuthorsTexture; i++)
		{
			authorsSpriteVec.push_back(sf::Sprite());
			authorsSpriteVec.back().setTexture(authorsTextureVec.at(i));
			authorsSpriteVec.back().setTextureRect(sf::IntRect(0, 0, 1920, 1080));
			if (i < 9)
			{
				authorsSpriteVec.back().setTextureRect(sf::IntRect(0, 0, 200, 200));
				if (i > 3)
				{
					authorsSpriteVec.back().setScale(kX, kY);
				}
				else
				{
					authorsSpriteVec.back().setScale(2 * kX, 2 * kY);
				}
			}
			else
			{
				authorsSpriteVec.back().setTextureRect(sf::IntRect(0, 0, 1000, 1000));
				authorsSpriteVec.back().setScale(kX, kY);
			}

		}

		mainMenuMusic.openFromFile("resource\\Audio\\mainMenuMusic.ogg");
		bestiaryMusic.openFromFile("resource\\Audio\\bestiaryMusic.ogg");
		authorsMusic.openFromFile("resource\\Audio\\authorsMusic.ogg");
		buttonBuffer.loadFromFile("resource\\Audio\\buttonSound.ogg");
		buttonSound.setBuffer(buttonBuffer);

		Menu::updateSize();
	Menu:mainMenu(window, music);
	}

	Menu::~Menu()
	{
	}

	void Menu::mainMenu(sf::RenderWindow& window, sf::Music& musicToStop)
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
		Menu::playMusic(mainMenuMusic);
		mainMenuMusic.setLoop(true);

		while (isMenu)
		{
			for (int i = 0; i < numOfMenuButtons; i++)
			{
				if (textVector.at(i).second == "mainMenu")
				{
					textVector.at(i).first.setFillColor(sf::Color::White);
				}
			}

			window.clear();

			Menu::frameCreator(window);
			Menu::createKeys(7);
			switch (key)
			{
			case 1:
			{
				textVector.at(14).first.setFillColor(sf::Color(176, 227, 23, 255));  // Продолжить
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{

						Menu::closeMainMenu(musicToStop);
					}
				}
				break;
			}
			case 2:
			{
				textVector.at(0).first.setFillColor(sf::Color(176, 227, 23, 255));  // Новая игра (пока что тоже самое, что и продолжить)
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						Menu::closeMainMenu(musicToStop);
					}
				}
				break;
			}
			case 3:
			{
				textVector.at(17).first.setFillColor(sf::Color(176, 227, 23, 255));  // Загрузка
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{

					}
				}
				break;
			}
			case 4:
			{
				textVector.at(15).first.setFillColor(sf::Color(176, 227, 23, 255));  // Настройки 
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						Menu::openSettingsMenu(window, mainMenuMusic);
						isMenu = true;
						key = 1;
					}
				}
				break;
			}
			case 5:
			{
				textVector.at(1).first.setFillColor(sf::Color(176, 227, 23, 255));  // Бестиарий
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						Menu::openBestiary(window, musicToStop);
					}
				}
				break;
			}
			case 6:
			{
				textVector.at(16).first.setFillColor(sf::Color(176, 227, 23, 255));  // Авторы
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						Menu::authors(window, musicToStop);
						Menu::playMusic(mainMenuMusic);
						isMenu = true;
						key = 1;
					}
				}
				break;
			}
			case 7:
			{
				textVector.at(2).first.setFillColor(sf::Color(176, 227, 23, 255));  // Выход
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						Menu::closeGame(window);
					}
				}
				break;
			}
			}


			if (CurrentFrame > 16) CurrentFrame = 0;
			spriteVec.at(int(CurrentFrame) / 2).setTextureRect(sf::IntRect(1920 * (int(CurrentFrame) % 2), 0, 1920, 1080));

			if (isMenu)
			{
				window.draw(spriteVec.at(int(CurrentFrame) / 2));
				for (std::pair<sf::Text, sf::String> var : textVector)
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


	void Menu::pauseMenu(sf::RenderWindow& window, sf::Music& music)
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
					textVector.at(i).first.setFillColor(sf::Color::Black);
				}
			}

			Menu::frameCreator(window);
			Menu::createKeys(5);
			switch (key)
			{
			case 1:
			{
				textVector.at(3).first.setFillColor(sf::Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						Menu::closePauseMenu();
					}
				}
				break;
			}
			case 2:
			{
				textVector.at(18).first.setFillColor(sf::Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{

					}
				}
				break;
			}
			case 3:
			{
				textVector.at(19).first.setFillColor(sf::Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{

					}
				}
				break;
			}
			case 4:
			{
				textVector.at(4).first.setFillColor(sf::Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						Menu::openSettingsMenu(window, music);
						isMenu = true;
						key = 1;
					}
				}
				break;
			}
			case 5:
			{
				textVector.at(5).first.setFillColor(sf::Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						Menu::openMainMenu(window, music);
					}
				}
				break;
			}
			}

			if (CurrentFrame > 8) CurrentFrame = 0;
			sprPauseVec.at(int(CurrentFrame) / 2).setTextureRect(sf::IntRect(1280 * (int(CurrentFrame) % 2), 0, 1280, 720));

			if (isMenu)
			{
				window.draw(sprPauseVec.at(int(CurrentFrame) / 2));
				for (std::pair<sf::Text, sf::String> var : textVector)
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

	void Menu::settingsMenu(sf::RenderWindow& window, sf::Music& music)
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
			volArrows.setColor(sf::Color::Black);

			for (int i = 0; i < numOfMenuButtons; i++)
			{
				if (textVector.at(i).second == "settingsMenu")
				{
					textVector.at(i).first.setFillColor(sf::Color::Black);
				}
			}
			for (int i = 0; i < numOfDisplay; i++)
			{
				displayVector.at(i).first.setFillColor(sf::Color::Black);
			}

			Menu::usersResolution(window);

			if (isDisp)
			{
				textVector.at(13).first.setFillColor(sf::Color(150, 150, 150, 255));
				displayVector.at(6).first.setFillColor(sf::Color(150, 150, 150, 255));
			}

			Menu::frameCreator(window);
			Menu::createKeys(5);
			switch (key)
			{
			case 1:  // Режимы экрана: Полноэкранный/оконный
			{
				textVector.at(6).first.setFillColor(sf::Color(67, 0, 229, 255));
				textVector.at(7).first.setFillColor(sf::Color(67, 0, 229, 255));
				textVector.at(8).first.setFillColor(sf::Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						Menu::screenModes(window);
					}
				}
				break;
			}
			case 2:  // Разрешение экрана
			{
				if (!isDisp)
				{
					textVector.at(13).first.setFillColor(sf::Color(67, 0, 229, 255));
					displayVector.at(whatDisplay).first.setFillColor(sf::Color(67, 0, 229, 255));
					if (menuTimer > keyDelay)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						{
							Menu::screenResolutions(window, false);
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						{
							Menu::screenResolutions(window, true);
						}
					}
				}
				else
				{
					textVector.at(13).first.setFillColor(sf::Color(152, 122, 225, 255));
					displayVector.at(6).first.setFillColor(sf::Color(152, 122, 225, 255));
				}
				break;
			}
			case 3:  // Вкл/Выкл звук
			{
				textVector.at(10).first.setFillColor(sf::Color(67, 0, 229, 255));
				textVector.at(9).first.setFillColor(sf::Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
					{
						Menu::onOffMusic(music);
					}
				}
				break;
			}
			case 4:  // Ползунок звука
			{
				textVector.at(11).first.setFillColor(sf::Color(67, 0, 229, 255));
				volArrows.setColor(sf::Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						Menu::chooseVolume(music, false);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						Menu::chooseVolume(music, true);
					}
				}
				break;
			}
			case 5:  // Выход в меню паузы
			{
				textVector.at(12).first.setFillColor(sf::Color(67, 0, 229, 255));
				if (menuTimer > keyDelay)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						Menu::closeSettingsMenu(window, music);
					}
				}
				break;
			}
			}
			Menu::updateSize();
			if (CurrentFrame > 8) CurrentFrame = 0;
			sprPauseVec.at(int(CurrentFrame) / 2).setTextureRect(sf::IntRect(1280 * (int(CurrentFrame) % 2), 0, 1280, 720));

			if (isMenu)
			{
				window.draw(sprPauseVec.at(int(CurrentFrame) / 2));
				window.draw(textVector.at(6).first);
				window.draw(textVector.at(13).first);
				window.draw(textVector.at(8 - int(!isDisp)).first);
				if (!isDisp)
				{
					window.draw(displayVector.at(whatDisplay).first);
				}
				else
				{
					window.draw(displayVector.at(6).first);
				}
				window.draw(volArrows);
				window.draw(textVector.at(10 - int(isVol)).first);
				window.draw(textVector.at(11).first);
				window.draw(textVector.at(12).first);
				window.display();
			}
		}
	}

	void Menu::bestiary(sf::RenderWindow& window, sf::Music& musicToStop)
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
		Menu::playMusic(bestiaryMusic);
		bestiaryMusic.setLoop(true);

		while (isMenu)
		{
			for (int i = 0; i < numOfMonstres; i++)
			{
				bestiaryVector.at(i).first.setFillColor(sf::Color(85, 54, 18, 255));
				bestiaryVector.at(i).second.setFillColor(sf::Color(85, 54, 18, 255));
			}
			for (int i = 0; i < numOfButton; i++)
			{
				buttonVector.at(i).setFillColor(sf::Color(85, 54, 18, 255));
			}
			window.clear();

			Menu::frameCreator(window);
			Menu::createKeys(2);
			buttonVector.at(key).setFillColor(sf::Color(21, 56, 104, 255));
			if (menuTimer > keyDelay)
			{
				switch (key)
				{
				case 1:
				{
					if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
					{
						Menu::chooseMonster(false);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						Menu::chooseMonster(true);
					}
					break;
				}
				case 2:
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						Menu::closeBestiary(window, musicToStop);
					}
					break;
				}
				}
			}

			if (CurrentFrame > 12) CurrentFrame = 0;
			bestiarySpriteVec.at(whatMonster).setTextureRect(sf::IntRect(256 * int(CurrentFrame), 0, 256, 256));

			if (isMenu)
			{
				window.draw(bestiaryBg);
				window.draw(bestiarySpriteVec.at(whatMonster));
				window.draw(bestiaryVector.at(whatMonster).first);
				window.draw(bestiaryVector.at(whatMonster).second);
				for (sf::Text var : buttonVector)
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

		cameraOffsetX = camera->getView()->getCenter().x - camera->getView()->getSize().x / 2;
		cameraOffsetY = camera->getView()->getCenter().y - camera->getView()->getSize().y / 2;
		kX = double(camera->getView()->getSize().x) / double(1920);
		kY = double(camera->getView()->getSize().y) / double(1080);
		resizeMistakeX = 1920.0 / 1280.0;
		resizeMistakeY = 1080.0 / 720.0;

		for (int i = 0; i < numOfMenuButtons; i++)
		{
			if (textVector.at(i).second == "mainMenu")
			{
				textVector.at(i).first.setCharacterSize(int(camera->getView()->getSize().y / 27));
			}
			else
			{
				textVector.at(i).first.setCharacterSize(int(camera->getView()->getSize().y * resizeMistakeY / 27));
			}
		}

		textVector.at(14).first.setPosition(40 * kX + cameraOffsetX, 380 * kY + cameraOffsetY);  // Продолжить
		textVector.at(0).first.setPosition(40 * kX + cameraOffsetX, 440 * kY + cameraOffsetY);  // Новая игра 
		textVector.at(17).first.setPosition(40 * kX + cameraOffsetX, 500 * kY + cameraOffsetY);  // Загрузка
		textVector.at(15).first.setPosition(40 * kX + cameraOffsetX, 560 * kY + cameraOffsetY);  // Настройки
		textVector.at(1).first.setPosition(40 * kX + cameraOffsetX, 620 * kY + cameraOffsetY);  // Бестиарий
		textVector.at(16).first.setPosition(40 * kX + cameraOffsetX, 680 * kY + cameraOffsetY);  // Авторы
		textVector.at(2).first.setPosition(40 * kX + cameraOffsetX, 740 * kY + cameraOffsetY);  // Выход из игры

		textVector.at(3).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (560 - 180) * kY * resizeMistakeY + cameraOffsetY);  // Продолжить
		textVector.at(18).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (620 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Сохранение
		textVector.at(19).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (680 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Загрузка
		textVector.at(4).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (740 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Настройки
		textVector.at(5).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (800 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Главное меню

		textVector.at(6).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (455 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Режим:
		textVector.at(7).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (495 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Оконный
		textVector.at(8).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (495 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Полноэкранный
		textVector.at(9).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (655 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Звук: Вкл
		textVector.at(10).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (655 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Звук: Выкл
		textVector.at(11).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (715 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Громкость
		textVector.at(12).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (819 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Назад
		textVector.at(13).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (550 - 180) * kY * resizeMistakeX + cameraOffsetY);  // Разрешение

		for (int i = 0; i < 8; i++)  // Вектор спрайтов бэкграунда главного меню
		{
			spriteVec.at(i).setPosition(camera->getView()->getCenter().x - kX * spriteVec.at(i).getTexture()->getSize().x / 4,
				camera->getView()->getCenter().y - kY * spriteVec.at(i).getTexture()->getSize().y / 2);
		}

		for (int i = 0; i < 4; i++)  // Вектор спрайтов бэкграунда меню паузы
		{
			sprPauseVec.at(i).setPosition(camera->getView()->getCenter().x - kX * resizeMistakeX * sprPauseVec.at(i).getTexture()->getSize().x / 4,
				camera->getView()->getCenter().y - kY * resizeMistakeY * sprPauseVec.at(i).getTexture()->getSize().y / 2);
		}

		for (int i = 0; i < numOfDisplay; i++)  // Вектор параметров разрешения экрана
		{
			displayVector.at(i).first.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (597 - 180) * kY * resizeMistakeY + cameraOffsetY);
			displayVector.at(i).first.setCharacterSize(int(camera->getView()->getSize().y * resizeMistakeY / 27));
		}

		volArrows.setPosition((360 - 320) * kX * resizeMistakeX + cameraOffsetX, (773 - 180) * kY * resizeMistakeY + cameraOffsetY);  // Стрелки громкости

		for (size_t i = 0; i < numOfMonstres; i++)  // Вектор текста бестиария
		{
			bestiaryVector.at(i).first.setCharacterSize(int(camera->getView()->getSize().y / 10.8));
			bestiaryVector.at(i).first.setPosition(400 * kX + cameraOffsetX, 350 * kY + cameraOffsetY);
			bestiaryVector.at(i).second.setCharacterSize(int(camera->getView()->getSize().y / 21.6));
			bestiaryVector.at(i).second.setPosition(400 * kX + cameraOffsetX, 475 * kY + cameraOffsetY);
		}

		for (size_t i = 0; i < numOfButton; i++)  // Вектор кнопок бестиария
		{
			buttonVector.at(i).setCharacterSize(int(camera->getView()->getSize().y / 20));
			buttonVector.at(i).setPosition(600 * kX + cameraOffsetX, 600 * kY + cameraOffsetY);
		}

		buttonVector.at(0).setPosition(400 * kX + cameraOffsetX, 0 * kY + cameraOffsetY);  // Бестиарий
		buttonVector.at(1).setPosition(400 * kX + cameraOffsetX, 700 * kY + cameraOffsetY);  // Выбор
		buttonVector.at(2).setPosition(400 * kX + cameraOffsetX, 750 * kY + cameraOffsetY);  // Назад
		buttonVector.at(0).setCharacterSize(int(camera->getView()->getSize().y / 5.4));

		for (size_t i = 0; i < numOfMonstres; i++)  // Вектор спрайтов существ Бестриария
		{
			bestiarySpriteVec.at(i).setPosition(1300 * kX + cameraOffsetX, 400 * kY + cameraOffsetY);
		}

		bestiaryBg.setPosition(camera->getView()->getCenter().x - kX * bestiaryBg.getTexture()->getSize().x / 2,  // Вектор бэкграунда бестиария
			camera->getView()->getCenter().y - kY * bestiaryBg.getTexture()->getSize().y / 2);

		for (size_t i = 0; i < numOfAuthors; i++)  // Вектор текста меню "Авторы"
		{
			authorsTextVec.at(i).setCharacterSize(int(camera->getView()->getSize().y / 27));
		}

		authorsBg.setFillColor(sf::Color(50, 50, 50, 255));
		authorsBg.setSize(sf::Vector2f(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));  // Бэкграунд меню "Авторы"
		authorsBg.setPosition(cameraOffsetX, cameraOffsetY);

		authorsTextVec.at(0).setPosition(170 * kX + cameraOffsetX, 800 * kY + cameraOffsetY);  // Текст меню "Авторы"
		authorsTextVec.at(1).setPosition(240 * kX + cameraOffsetX, 800 * kY + cameraOffsetY);
		authorsTextVec.at(2).setPosition(240 * kX + cameraOffsetX, 850 * kY + cameraOffsetY);
		authorsTextVec.at(3).setPosition(1200 * kX + cameraOffsetX, 800 * kY + cameraOffsetY);
		authorsTextVec.at(4).setPosition(1200 * kX + cameraOffsetX, 850 * kY + cameraOffsetY);
		authorsTextVec.at(5).setPosition(380 * kX + cameraOffsetX, 800 * kY + cameraOffsetY);
		authorsTextVec.at(6).setPosition(530 * kX + cameraOffsetX, 850 * kY + cameraOffsetY);
		authorsTextVec.at(7).setPosition(570 * kX + cameraOffsetX, 1000 * kY + cameraOffsetY);

		authorsSpriteVec.at(1).setPosition(280 * kX + cameraOffsetX, 300 * kY + cameraOffsetY);  // Спрайты меню "Авторы"
		authorsSpriteVec.at(2).setPosition(1240 * kX + cameraOffsetX, 300 * kY + cameraOffsetY);
		authorsSpriteVec.at(0).setPosition(760 * kX + cameraOffsetX, 300 * kY + cameraOffsetY);
		authorsSpriteVec.at(3).setPosition(760 * kX + cameraOffsetX, 300 * kY + cameraOffsetY);

		for (size_t i = 9; i < numOfAuthorsTexture; i++)  // Вектор спрайтов кадров меню "Авторы"
		{
			authorsSpriteVec.at(i).setPosition(460 * kX + cameraOffsetX, cameraOffsetY);
		}
		for (size_t i = 4; i < 9; i++)
		{
			authorsSpriteVec.at(i).setPosition((400 + 460) * kX + cameraOffsetX, 500 * kY + cameraOffsetY);
		}
	}

	void Menu::frameCreator(sf::RenderWindow& window)
	{
		float time = clock2.getElapsedTime().asMicroseconds();
		clock2.restart();
		time = time / 800;
		menuTimer += 0.005 * time;
		CurrentFrame += 0.005 * time;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isMenu = false;
				window.close();
			}
		}
	}

	void Menu::createKeys(int numOfKeys)
	{
		if (menuTimer > keyDelay)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				Menu::playSound(buttonSound);
				key++;
				if (key > numOfKeys)
				{
					key = 1;
				}
				menuTimer = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				Menu::playSound(buttonSound);
				key--;
				if (key < 1)
				{
					key = numOfKeys;
				}
				menuTimer = 0;
			}
		}
	}

	void Menu::closeMainMenu(sf::Music& musicToStop)
	{
		Menu::playSound(buttonSound);
		clock->restart();
		isMenu = false;
		Menu::playMusic(musicToStop);
		menuTimer = 0;
	}

	void Menu::openBestiary(sf::RenderWindow& window, sf::Music& musicToStop)
	{
		Menu::playSound(buttonSound);
		isMenu = false;
		Menu::bestiary(window, musicToStop);
		menuTimer = 0;
	}

	void Menu::closeGame(sf::RenderWindow& window)
	{
		Menu::playSound(buttonSound);
		isMenu = false;
		menuTimer = 0;
		window.close();
	}

	void Menu::chooseMonster(bool leftArrow)
	{
		Menu::playSound(buttonSound);
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

	void Menu::closeBestiary(sf::RenderWindow& window, sf::Music& musicToStop)
	{
		Menu::playSound(buttonSound);
		clock->restart();
		bestiaryMusic.stop();
		mainMenu(window, musicToStop);
		isMenu = false;
	}

	void Menu::closePauseMenu()
	{
		Menu::playSound(buttonSound);
		isMenu = false;
		clock->restart();
		menuTimer = 0;
	}

	void Menu::openSettingsMenu(sf::RenderWindow& window, sf::Music& music)
	{
		Menu::playSound(buttonSound);
		isMenu = false;
		Menu::settingsMenu(window, music);
		menuTimer = 0;
	}

	void Menu::openMainMenu(sf::RenderWindow& window, sf::Music& music)
	{
		Menu::playSound(buttonSound);
		isMenu = false;
		Menu::mainMenu(window, music);
		menuTimer = 0;
	}

	void Menu::screenModes(sf::RenderWindow& window)
	{
		Menu::playSound(buttonSound);
		isDisp = !isDisp;
		if (isDisp == 1)
		{
			window.create(sf::VideoMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), "The Darkest Shadow", sf::Style::Fullscreen);
			if (windowIcon == nullptr)
				windowIcon = new sf::Image;
			windowIcon->loadFromFile("resource\\Window\\WindowIcon.png");

			window.setIcon(windowIcon->getSize().x, windowIcon->getSize().y, windowIcon->getPixelsPtr());
			window.setVerticalSyncEnabled(true);
		}
		else
		{
			window.create(sf::VideoMode(displayVector.at(whatDisplay).second.first, displayVector.at(whatDisplay).second.second), "The Darkest Shadow", sf::Style::Default);
			if (windowIcon == nullptr)
				windowIcon = new sf::Image;
			windowIcon->loadFromFile("resource\\Window\\WindowIcon.png");

			window.setIcon(windowIcon->getSize().x, windowIcon->getSize().y, windowIcon->getPixelsPtr());
			window.setVerticalSyncEnabled(true);
		}

		window.setView(*(camera->getView()));
		Menu::updateSize();
		menuTimer = 0;
	}

	void Menu::screenResolutions(sf::RenderWindow& window, bool leftArrow)
	{
		Menu::playSound(buttonSound);
		if (leftArrow)
		{
			whatDisplay--;
			if (whatDisplay < 0)
			{
				whatDisplay = numOfDisplay - 2;
			}
		}
		else
		{
			whatDisplay++;
			if (whatDisplay > numOfDisplay - 2)
			{
				whatDisplay = 0;
			}
		}
		verticalHeight = displayVector.at(whatDisplay).second.first;
		horizontalHeight = displayVector.at(whatDisplay).second.second;

		window.setSize(sf::Vector2u(verticalHeight, horizontalHeight));

		Menu::updateSize();
		menuTimer = 0;
	}

	void Menu::onOffMusic(sf::Music& music)
	{
		isVol = !isVol;
		if (isVol)
		{
			music.play();
			if (!volValue)
			{
				volValue = 4;
			}
			music.setVolume(25 * volValue * isVol);
		}
		else
		{
			music.stop();
		}
		volArrows.setTextureRect(sf::IntRect(0, isVol * volValue * 36, 252, 36));
		menuTimer = 0;
		Menu::playSound(buttonSound);
	}

	void Menu::closeSettingsMenu(sf::RenderWindow& window, sf::Music& music)
	{
		Menu::playSound(buttonSound);
		clock->restart();
		isMenu = false;
		//Menu::pauseMenu(window, music);
		menuTimer = 0;
	}

	void Menu::chooseVolume(sf::Music& music, bool leftArrow)
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
		music.setVolume(25 * volValue * isVol);
		volArrows.setTextureRect(sf::IntRect(0, volValue * 36, 252, 36));
		menuTimer = 0;
		Menu::playSound(buttonSound);
	}

	void Menu::usersResolution(sf::RenderWindow& window)
	{
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
			displayVector.at(5).first.setString(std::to_string(verticalHeight) + "x" + std::to_string(horizontalHeight) + " - пользовательское");
			whatDisplay = 5;
		}
	}

	void Menu::playSound(sf::Sound& sound)
	{
		sound.play();
		sound.setVolume(isVol * 25 * volValue);
	}

	void Menu::authors(sf::RenderWindow& window, sf::Music& musicToStop)
	{
		Menu::updateSize();
		Menu::playSound(buttonSound);

		isMenu = true;
		menuTimer = 0;
		CurrentFrame = 0;

		mainMenuMusic.stop();
		Menu::playMusic(authorsMusic);

		while (isMenu)
		{
			window.clear();
			Menu::frameCreator(window);
			if (menuTimer > keyDelay)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					Menu::closeAuthors();
				}
			}
			if (!authorsMusic.getStatus())
			{
				Menu::closeAuthors();
			}

			if (isMenu)
			{
				window.draw(authorsBg);
				Menu::drawAuthorsSprites(window);
				window.display();
			}
		}
	}

	void Menu::drawAuthorsText(sf::RenderWindow& window, int numOfElem, int startFrame, int duration)
	{
		authorsTextVec.at(numOfElem).setFillColor(sf::Color(
			50 * 255 / (abs(-205 + 410 * abs((CurrentFrame - startFrame) - duration * (int((CurrentFrame - startFrame) / duration) + 1)) / duration) + 50),
			50 * 255 / (abs(-205 + 410 * abs((CurrentFrame - startFrame) - duration * (int((CurrentFrame - startFrame) / duration) + 1)) / duration) + 50),
			50 * 255 / (abs(-205 + 410 * abs((CurrentFrame - startFrame) - duration * (int((CurrentFrame - startFrame) / duration) + 1)) / duration) + 50),
			255));
		window.draw(authorsTextVec.at(numOfElem));
	}

	void Menu::closeAuthors()
	{
		authorsMusic.stop();
		isMenu = false;
		clock->restart();
		menuTimer = 0;
	}

	void Menu::playMusic(sf::Music& music)
	{
		music.play();
		music.setVolume(isVol * 25 * volValue);
	}

	void Menu::drawAuthorsSprites(sf::RenderWindow& window)
	{
		if ((CurrentFrame >= 0) && (CurrentFrame < 50))
		{
			window.draw(authorsSpriteVec.at(0));
			Menu::drawAuthorsText(window, 0, 0, 50);
		}

		if ((CurrentFrame >= 50) && (CurrentFrame < 100))
		{
			window.draw(authorsSpriteVec.at(1));
			window.draw(authorsSpriteVec.at(2));
			Menu::drawAuthorsText(window, 1, 50, 50);
			Menu::drawAuthorsText(window, 2, 50, 50);
			Menu::drawAuthorsText(window, 3, 50, 50);
			Menu::drawAuthorsText(window, 4, 50, 50);
		}

		if ((CurrentFrame >= 100) && (CurrentFrame < 150))
		{
			window.draw(authorsSpriteVec.at(3));
			Menu::drawAuthorsText(window, 5, 100, 50);
			Menu::drawAuthorsText(window, 6, 100, 50);
		}

		if ((CurrentFrame >= 150) && (CurrentFrame <= 270))
		{
			if (CurrentFrame < 230)
			{
				if (int(int((CurrentFrame - 150) - 16 * int((CurrentFrame - 150) / 16)) / (16 / 16.0)) < 8)
				{
					authorsSpriteVec.at(4 + int((CurrentFrame - 150) / 16)).setTextureRect(sf::IntRect(200 * int(int((CurrentFrame - 150) - 16 * int((CurrentFrame - 150) / 16)) / (16 / 16.0)), 0, 200, 200));
				}
				else
				{
					authorsSpriteVec.at(4 + int((CurrentFrame - 150) / 16)).setTextureRect(sf::IntRect(200 * (15 - int(int((CurrentFrame - 150) - 16 * int((CurrentFrame - 150) / 16)) / (16 / 16.0))), 0, 200, 200));
				}
				window.draw(authorsSpriteVec.at(4 + int((CurrentFrame - 150) / 16)));
			}
			else
			{
				authorsSpriteVec.at(9 + int(int((CurrentFrame - 230)) / 4)).setTextureRect(sf::IntRect(1000 * int((CurrentFrame - 230) - 4 * int((CurrentFrame - 230) / 4)), 0, 1000, 1000));
				window.draw(authorsSpriteVec.at(9 + int(int((CurrentFrame - 230)) / 4)));
			}
			Menu::drawAuthorsText(window, 7, 150, 120);
		}

		if (CurrentFrame >= 270)
		{
			CurrentFrame = 150;
			authorsSpriteVec.at(4).setTextureRect(sf::IntRect(0, 0, 200, 200));
			window.draw(authorsSpriteVec.at(4));
		}
	}
}