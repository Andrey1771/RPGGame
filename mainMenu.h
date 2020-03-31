#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
using namespace sf;

class mainMenu
{
	bool isMainMenu;
	int key; // Номер текущей кнопки
	float CurrentFrame; // Таймер для анимации бэкграунда 
	float menuTimer; // Таймер для нажатия клавиш
	Sprite key1, key2, key3, about;
	std::vector<Sprite> spriteVector;
	Clock clock;
	Event event;
public:
	mainMenu(Sprite startGame, Sprite authors, Sprite exit, Sprite authorsPicture, std::vector<Sprite> SpriteVector);
	~mainMenu();
	void show(RenderWindow& window, Music& musicToStop, Music& mainMenuMusic);
};