#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
constexpr auto C=14;
constexpr auto keyDelay = 1;
constexpr auto numOfMonstres = 4;
constexpr auto numOfButton = 3;
constexpr auto numOfDisplay = 6;

class Menu 
{
	double kX, kY;
	Vector2u startDisplay;
	int whatDisplay;
	std::vector<std::pair< Text, std::pair<int, int>>>displayVector;
	std::pair< String, std::pair<int, int>> displayArray[numOfDisplay]
	{
		std::pair < String, std::pair<int, int>>("1920x1080",std::pair<int,int>(1920, 1080)),
		std::pair < String, std::pair<int, int>>("1366x768",std::pair<int,int>(1366, 768)),
		std::pair < String, std::pair<int, int>>("1280x1024",std::pair<int,int>(1280, 1024)),
		std::pair < String, std::pair<int, int>>("1024x768",std::pair<int,int>(1024, 768)),
		std::pair < String, std::pair<int, int>>("640x480",std::pair<int,int>(640, 480)),
		std::pair < String, std::pair<int, int>>("",std::pair<int,int>(0, 0))
	};

	Font font;  // �����
	std::vector<std::pair<Text, String>> textVector;  // ������ <����� ����� ���� (Text), � ������ ���� ���������> 
	std::pair<String, String> nameArray[C] =  // ������ <����� ������ ���� (String), � ������ ���� ���������>
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
		std::pair < String, String>(L"���������� ������:", L"settingsMenu")
	};

	Music bestiaryMusic;
	Font bestiaryFont;
	Font bestiaryFont_1;
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

	struct textureData
	{
		sf::Image* image;
		sf::Texture* texture;
		sf::Sprite* sprite;
		int maxFrameX{ 1 };
		int maxFrameY{ 1 };
	}movementTexture;

	Texture aboutTexture;
	Sprite about;
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
	Clock clock;  // ����
	float CurrentFrame;  // ������ ��� �������� ���������� 
	float menuTimer;  // ������ ��� ������� ������

	bool isDisp = 1;  // ��������� �������������� ������ (��/���)
	bool isVol = 0;  // ��������� ������ ����� (��/���)
	int volValue = 4;  // ������� �������� ��������� (0 - 0%, 1 - 25%, 2 - 50%, 3 - 75%, 4 - 100%)
	int oldValue = 0;  // ������ �������� ����� (��� ���������� ��� ���������� �����/������ � ����)
	bool musicFlag = 0;  // ��������� ������ ������ (��/���)

public:
	Menu(RenderWindow& window, Music& music);  // ����������� - �����: ��������� ��� ����������� ����� � ����������
	~Menu();  // ����������
	void mainMenu(RenderWindow& window, Music& musicToStop);  // ������� ����
	void pauseMenu(RenderWindow& window, Music& music);  // ���� �����
	void settingsMenu(RenderWindow& window, Music& music);  // ���� ���������
	void bestiary(RenderWindow& window, Music& musicToStop);  // ���������
	void updateSize();
};

