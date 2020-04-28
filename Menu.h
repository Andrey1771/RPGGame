#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Header.h"
#include "Camera.h"
#include <windows.h>
#include <winuser.h>

using namespace sf;
constexpr auto numOfMenuButtons = 17;
constexpr auto keyDelay = 1;
constexpr auto numOfMonstres = 4;
constexpr auto numOfButton = 3;
constexpr auto numOfDisplay = 7;

class Menu
{
	double cameraOffsetX, cameraOffsetY;
	double kX, kY;
	double resizeMistakeX, resizeMistakeY;
	bool isNewDisplay;
	int whatDisplay;
	std::vector<std::pair< Text, std::pair<int, int>>>displayVector;
	std::pair< String, std::pair<int, int>> displayArray[numOfDisplay]
	{
		std::pair < String, std::pair<int, int>>("1920x1080",std::pair<int,int>(1920, 1080)),
		std::pair < String, std::pair<int, int>>("1366x768",std::pair<int,int>(1366, 768)),
		std::pair < String, std::pair<int, int>>("1280x1024",std::pair<int,int>(1280, 1024)),
		std::pair < String, std::pair<int, int>>("1024x768",std::pair<int,int>(1024, 768)),
		std::pair < String, std::pair<int, int>>("640x480",std::pair<int,int>(640, 480)),
		std::pair < String, std::pair<int, int>>("",std::pair<int,int>(0, 0)),
		std::pair < String, std::pair<int, int>>("",std::pair<int,int>(0, 0))
	};

	Font font;  // �����
	std::vector<std::pair<Text, String>> textVector;  // ������ <����� ����� ���� (Text), � ������ ���� ���������> 
	std::pair<String, String> nameArray[numOfMenuButtons] =  // ������ <����� ������ ���� (String), � ������ ���� ���������>
	{
		std::pair < String, String>(L"����� ����", L"mainMenu"),
		std::pair < String, String>(L"���������", L"mainMenu"),
		std::pair < String, String>(L"����� �� ����" , L"mainMenu"),
		std::pair < String, String>(L"����������", L"pauseMenu"),
		std::pair < String, String>(L"���������", L"pauseMenu"),
		std::pair < String, String>(L"������� ����", L"pauseMenu"),
		std::pair < String, String>(L"�����:", L"settingsMenu"),
		std::pair < String, String>(L"�������", L"settingsMenu"),
		std::pair < String, String>(L"�������������", L"settingsMenu"),
		std::pair < String, String>(L"����: ���", L"settingsMenu"),
		std::pair < String, String>(L"����: ����", L"settingsMenu"),
		std::pair < String, String>(L"���������", L"settingsMenu"),
		std::pair < String, String>(L"�����", L"settingsMenu"),
		std::pair < String, String>(L"���������� ������:", L"settingsMenu"),
		std::pair < String, String>(L"����������", L"mainMenu"),
		std::pair < String, String>(L"���������", L"mainMenu"),
		std::pair < String, String>(L"������", L"mainMenu")
	};

	SoundBuffer buttonBuffer;
	Sound buttonSound;
	Music bestiaryMusic;
	Font bestiaryFont;
	std::pair<String, String> bestiaryArray[numOfMonstres] =
	{
		std::pair < String, String>(L"���", L"����� ������������ ���������\n�����������. ������ ����������"),
		std::pair < String, String>(L"���", L"����� ��������� ����������\n���. �����: �� ����������� ���\n������"),
		std::pair < String, String>(L"�����", L"���������� ������� �������.\n����� ������ ����"),
		std::pair < String, String>(L"������", L"������� �����������\n(����� ��� �����)")
	};
	std::vector<std::pair<Text, Text>> bestiaryVector;
	String buttonArray[numOfButton] =
	{
		L"���������",
		L"�����",
		L"�����"
	};
	std::vector<Text> buttonVector;

	std::vector<Texture> bestiaryTextureVec;
	std::vector<Sprite> bestiarySpriteVec;

	int whatMonster;

	Texture bestiaryBgTexture;
	Sprite bestiaryBg;
	Window window;  // ����

	Music mainMenuMusic; // ������ �������� ����
	Event event;  // �������
	std::vector<Texture> textureVec;  // ������ ������� ���������� �������� ����
	std::vector<Sprite> spriteVec;  // ������ �������� ���������� �������� ����

	std::vector<Texture> texPauseVec;  // ������ ������� ���������� ���� �����
	std::vector<Sprite> sprPauseVec;  // ������ �������� ���������� ���� �����

	Texture arrow;  // �������� ������� � ����������
	Sprite volArrows;  // ������ ������� � ����������

	bool isMenu;  // ��������� ������ ���� (��/���)
	int key;  // ����� ������� ������
	Clock clock2;  // ����
	float CurrentFrame;  // ������ ��� �������� ���������� 
	float menuTimer;  // ������ ��� ������� ������

	bool isDisp = 1;  // ��������� �������������� ������ (��/���)
	bool isVol = 1;  // ��������� ������ ����� (��/���)
	int volValue = 4;  // ������� �������� ��������� (0 - 0%, 1 - 25%, 2 - 50%, 3 - 75%, 4 - 100%)
	
	Camera* camera{ nullptr };
	void closeMainMenu(Music& musicToStop);
	void openBestiary(RenderWindow& window, Music& musicToStop);
	void closeGame(RenderWindow& window);
	void chooseMonster(bool leftArrow);
	void closeBestiary(RenderWindow& window, Music& musicToStop);
	void openMainMenu(RenderWindow& window, Music& musicToStop);
	void openSettingsMenu(RenderWindow& window, Music& musicToStop);
	void closePauseMenu();
	void screenModes(RenderWindow& window);
	void screenResolutions(RenderWindow& window, bool leftArrow);
	void onOffMusic(Music& music);
	void closeSettingsMenu(RenderWindow& window, Music& music);
	void frameCreator(RenderWindow& window);
	void chooseVolume(Music& music, bool leftArrow);
	void createKeys(int numOfKeys);
	void usersResolution(RenderWindow& window);
	void playSound(Sound& sound);

public:
	Menu(RenderWindow& window, Music& music, Camera* camera);  // ����������� - �����: ��������� ��� ����������� ����� � ����������
	~Menu();  // ����������
	void mainMenu(RenderWindow& window, Music& musicToStop);  // ������� ����
	void pauseMenu(RenderWindow& window, Music& music);  // ���� �����
	void settingsMenu(RenderWindow& window, Music& music);  // ���� ���������
	void bestiary(RenderWindow& window, Music& musicToStop);  // ���������
	void updateSize();
	void setCamera(Camera* camera) { this->camera = camera; };
	bool isMenuOn() { return isMenu; };
};

