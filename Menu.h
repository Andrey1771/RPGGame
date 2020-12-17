#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Header.h"
#include "Camera.h"
#include <windows.h>
#include <winuser.h>

namespace Menu
{
	constexpr auto numOfMenuButtons = 20;  // ���������� ������ �������� ����
	constexpr auto keyDelay = 1;  // �������� ������� ������ � ����
	constexpr auto numOfMonstres = 4;  // ���������� �������� � ���������
	constexpr auto numOfButton = 3;  // ���������� ������ ���������
	constexpr auto numOfDisplay = 7;  // ���������� ���������� ���������� ������
	constexpr auto numOfAuthors = 8;  // ���������� ������ ���� "������"
	constexpr auto numOfAuthorsTexture = 19;  // ���������� ������� ���� "������"

	class Menu
	{
		double cameraOffsetX, cameraOffsetY;  // �������� ������
		double kX, kY;  // ��������� �����������
		double resizeMistakeX, resizeMistakeY;  // �����������, ������������� �������� pauseMenu ��� �������������� ������

		sf::Font font;  // �������� �����
		std::vector<std::pair<sf::Text, sf::String>> textVector;  // ������ <����� ������ ���� (Text), � ������ ���� ���������> 
		std::pair<sf::String, sf::String> nameArray[numOfMenuButtons] =  // ������ <����� ������ ���� (sf::String), � ������ ���� ���������>
		{
			std::pair < sf::String, sf::String>(L"����� ����", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"���������", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"����� �� ����" , L"mainMenu"),
			std::pair < sf::String, sf::String>(L"����������", L"pauseMenu"),
			std::pair < sf::String, sf::String>(L"���������", L"pauseMenu"),
			std::pair < sf::String, sf::String>(L"������� ����", L"pauseMenu"),
			std::pair < sf::String, sf::String>(L"�����:", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"�������", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"�������������", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"����: ���", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"����: ����", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"���������", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"�����", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"���������� ������:", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"����������", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"���������", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"������", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"��������", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"����������", L"pauseMenu"),
			std::pair < sf::String, sf::String>(L"��������", L"pauseMenu")
		};

		std::vector<sf::Texture> textureVec;  // ������ ������� ���������� �������� ����
		std::vector<sf::Sprite> spriteVec;  // ������ �������� ���������� �������� ����

		sf::Music mainMenuMusic; // ������ �������� ����

		std::vector<sf::Texture> texPauseVec;  // ������ ������� ���������� ���� �����
		std::vector<sf::Sprite> sprPauseVec;  // ������ �������� ���������� ���� �����

		bool isNewDisplay;  // ���� ������� ������ ����������������� ���������� ������
		int whatDisplay;  // ��������� �������� ���������� ������
		std::vector<std::pair< sf::Text, std::pair<int, int>>>displayVector;  // ������ ���������� ���������� ������
		std::pair< sf::String, std::pair<int, int>> displayArray[numOfDisplay]  // ������ ���������� ���������� ������
		{
			std::pair < sf::String, std::pair<int, int>>("1920x1080",std::pair<int,int>(1920, 1080)),
			std::pair < sf::String, std::pair<int, int>>("1366x768",std::pair<int,int>(1366, 768)),
			std::pair < sf::String, std::pair<int, int>>("1280x1024",std::pair<int,int>(1280, 1024)),
			std::pair < sf::String, std::pair<int, int>>("1024x768",std::pair<int,int>(1024, 768)),
			std::pair < sf::String, std::pair<int, int>>("640x480",std::pair<int,int>(640, 480)),
			std::pair < sf::String, std::pair<int, int>>("",std::pair<int,int>(0, 0)),
			std::pair < sf::String, std::pair<int, int>>("",std::pair<int,int>(0, 0))
		};

		sf::Texture arrow;  // �������� ������� � ����������
		sf::Sprite volArrows;  // ������ ������� � ����������

		bool isDisp = 1;  // ��������� �������������� ������ (��/���)
		bool isVol = 1;  // ��������� ������ ����� (��/���)
		int volValue = 4;  // ������� �������� ��������� (0 - 0%, 1 - 25%, 2 - 50%, 3 - 75%, 4 - 100%)

		sf::Music bestiaryMusic;  // ������ ���������
		sf::Font bestiaryFont;  // ����� ���������
		std::pair<sf::String, sf::String> bestiaryArray[numOfMonstres] =  // ������ ������ ���������
		{
			std::pair < sf::String, sf::String>(L"���", L"����� ������������ ���������\n�����������. ������ ����������"),
			std::pair < sf::String, sf::String>(L"���", L"����� ��������� ����������\n���. �����: �� ����������� ���\n������"),
			std::pair < sf::String, sf::String>(L"�����", L"���������� ������� �������.\n����� ������ ����"),
			std::pair < sf::String, sf::String>(L"������", L"������� �����������\n(����� ��� �����)")
		};
		std::vector<std::pair<sf::Text, sf::Text>> bestiaryVector;  // ������ ������ ���������

		sf::String buttonArray[numOfButton] =  // ������ ������ ���������
		{
			L"���������",
			L"�����",
			L"�����"
		};
		std::vector<sf::Text> buttonVector;  // ������ ������ ���������

		std::vector<sf::Texture> bestiaryTextureVec;  // ������ ������� ���������
		std::vector<sf::Sprite> bestiarySpriteVec;  // ������ �������� ���������

		sf::Texture bestiaryBgTexture;  // �������� ���������� ���������
		sf::Sprite bestiaryBg;  // ������ ���������� ����������

		int whatMonster;  // ��������� ����������� �������� ������� � ����������

		sf::RectangleShape authorsBg;  // ��������� ���� "������"
		sf::String authorsTextArray[numOfAuthors] =  // ������ ������ ���� "������"
		{
			L"���������� ��� �� ����������� ������� � ����� ����",
			L"������ ������",
			L"GitHub - Andrey1771",
			L"����� �������",
			L"GitHub - pavelgrafit",
			L"������ ������������� ������ ��������",
			L"�� ��������������� ������",
			L"��� ������ ������� Enter"
		};

		std::vector<sf::Text> authorsTextVec;  // ������ ������ ���� "������"
		sf::Music authorsMusic;  // ������ ���� "������"

		std::vector<sf::Texture> authorsTextureVec;  // ������ ������� ���� "������"
		std::vector<sf::Sprite> authorsSpriteVec;  // ������ �������� ���� "������"

		sf::SoundBuffer buttonBuffer;  // ����� ����� ������� ������
		sf::Sound buttonSound;  // ���� ������� ������

		sf::Window window;  // ����
		sf::Event event;  // �������
		bool isMenu;  // ��������� ������ ���� (��/���)
		int key;  // ����� ������� ������
		sf::Clock* clock;
		sf::Clock clock2;  // ����
		float CurrentFrame;  // ������ ��� �������� ���������� 
		float menuTimer;  // ������ ��� ������� ������
		sf::Image* windowIcon{ nullptr };
		Camera* camera{ nullptr };
		void closeMainMenu(sf::Music& musicToStop);  // �������� �������� ����
		void openBestiary(sf::RenderWindow& window, sf::Music& musicToStop);  // �������� ���������
		void closeGame(sf::RenderWindow& window);  // �������� ����
		void chooseMonster(bool leftArrow);  // ������������ �������� � ���������
		void closeBestiary(sf::RenderWindow& window, sf::Music& musicToStop);  // �������� ���������
		void openMainMenu(sf::RenderWindow& window, sf::Music& musicToStop);  // �������� �������� ����
		void openSettingsMenu(sf::RenderWindow& window, sf::Music& musicToStop);  // �������� ���� ��������
		void closePauseMenu();  // �������� ���� �����
		void screenModes(sf::RenderWindow& window);  // ������������ ����� ������������� � ������� ��������
		void screenResolutions(sf::RenderWindow& window, bool leftArrow);  // ������������ ���������� ������
		void onOffMusic(sf::Music& music);  // ���������/���������� ������ � ������
		void closeSettingsMenu(sf::RenderWindow& window, sf::Music& music);  // �������� ���� ��������
		void frameCreator(sf::RenderWindow& window);  // �������� �������� ����� � ��������� ������� �������� ����
		void chooseVolume(sf::Music& music, bool leftArrow);  // ������������ ��������� ������ � ������
		void createKeys(int numOfKeys);  // �������� ������
		void usersResolution(sf::RenderWindow& window);  // ��������� ����������������� ���������� ������
		void playSound(sf::Sound& sound);  // �������� ���� � ������� ������� ���������
		void authors(sf::RenderWindow& window, sf::Music& musicToStop);  // ���� "������"
		void drawAuthorsText(sf::RenderWindow& window, int numOfElem, int startFrame, int duration);  // ��������� ������ ���� "������"
		void closeAuthors();  // �������� ���� "������"
		void playMusic(sf::Music& music);  // �������� ������ � ������� ������� ���������
		void drawAuthorsSprites(sf::RenderWindow& window);  // ��������� �������� ���� "������"
		void updateSize();  // ���������� �������� ���� ������� ��� ������� ���������� ����

	public:
		Menu(sf::RenderWindow& window, sf::Music& music, Camera* camera, sf::Clock& clock);  // ����������� - �����: ��������� ��� ����������� ����� � ����������
		~Menu();  // ����������
		void mainMenu(sf::RenderWindow& window, sf::Music& musicToStop);  // ������� ����
		void pauseMenu(sf::RenderWindow& window, sf::Music& music);  // ���� �����
		void settingsMenu(sf::RenderWindow& window, sf::Music& music);  // ���� ���������
		void bestiary(sf::RenderWindow& window, sf::Music& musicToStop);  // ���������
		void setCamera(Camera* camera) { this->camera = camera; };  // �� ��� ��� �����, �� �� �����)
		bool isMenuOn() { return isMenu; };  // ��������� ������ ����, ����� ��� �����
	};

}