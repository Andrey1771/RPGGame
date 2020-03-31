#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
using namespace sf;

class mainMenu
{
	bool isMainMenu;
	int key; // ����� ������� ������
	float CurrentFrame; // ������ ��� �������� ���������� 
	float menuTimer; // ������ ��� ������� ������
	Sprite key1, key2, key3, about;
	std::vector<Sprite> spriteVector;
	Clock clock;
	Event event;
public:
	mainMenu(Sprite startGame, Sprite authors, Sprite exit, Sprite authorsPicture, std::vector<Sprite> SpriteVector);
	~mainMenu();
	void show(RenderWindow& window, Music& musicToStop, Music& mainMenuMusic);
};